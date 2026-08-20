# 3D Raytracer

A multi-threaded 3D ray tracing engine built from scratch in modern C++.

## About The Project

I built this to go past just implementing ray-object intersection math and actually push it toward something closer to a real renderer: recursive reflection/refraction, procedural patterns, and a bounding-volume hierarchy so scenes with hundreds of objects don't grind to a halt. It renders scenes made of primitive shapes (spheres, cubes, planes, cylinders, cones) that can be grouped, transformed, textured, and lit, and outputs the result as a `.ppm` image.

The project also doubles as a small case study in multi-threading and spatial acceleration structures — see [Benchmarks](#benchmarks) below.

## Built With

- **C++ (C++17)** - Core engine, no external dependencies
- **`<thread>`** - Multi-threaded rendering across CPU cores
- **PPM** - Simple, dependency-free image output format

## How It Works

Every pixel on the `Camera`'s canvas casts a `Ray` into the `World`. The ray is tested against every top-level object (or, for a `Group`, against its cached `Bounds` first so whole subtrees can be skipped in one check). On a hit, the engine computes lighting (ambient/diffuse/specular), casts shadow rays toward each light, and recursively spawns reflection and refraction rays up to a configurable bounce limit, blending them together with a Schlick Fresnel approximation.

Rendering is parallelized by splitting the canvas's rows/pixels across a pool of `std::thread`s (`Camera::renderMultiThreads`), so on top of the algorithmic speedup from bounding volumes, you also get near-linear speedup from available CPU cores.

## Project Structure

```
Raytracer/
├── Makefile
├── src/
│   ├── core/       # Math primitives: Tuple, Matrix, Color, Ray, Transformations
│   ├── geometry/   # Shape, Sphere, Cube, Plane, Cylinder, Cone, Group, Bounds
│   ├── shading/     # Materials, Light, Pattern (Stripe/Gradient/Ring/Checker3D)
│   ├── scene/       # World, Camera
│   ├── io/          # Canvas, PPM writer
│   └── *.cpp        # main.cpp / benchmark entry point
└── build/           # Object files (generated)
```

### Prerequisites

- `clang++` with C++17 support
- `make`

### Building

```bash
git clone https://github.com/YahavMarom/Raytracer.git
cd Raytracer
make
```

This compiles every `.cpp` under `src/` (recursively) into `build/`, then links them into a `main` executable at the project root. Run `make clean` to remove `build/` and the binary.

### Running

```bash
./main
```

By default `main()` runs the benchmark suite (see below). To render your own scene instead, write a scene-building function like the ones described in [Usage](#usage) and call it from `main()`.

## Usage

There's no scene file format — scenes are built directly in C++ by constructing shapes, materials, lights, and a camera, then rendering. Everything below reflects patterns already used in the project's own scene-setup code.

### 1. Build a world and add lights

```cpp
World w;
w.addLight(pointLight(point(10.0, 20.0, -15.0), Color(1.0, 1.0, 1.0)));
```

`World` can hold multiple lights; each is a position (`point`) plus a `Color` intensity.

### 2. Create shapes

Every shape (`Sphere`, `Cube`, `Plane`, `Cylinder`, `Cone`) is created as a `std::shared_ptr` and added to the world with `addObject`:

```cpp
auto sphere = std::make_shared<Sphere>();
sphere->setTransform(translation(0.0, 1.0, 0.0) * scaling(0.7, 0.7, 0.7));
sphere->getMaterials().setColor(Color(0.2, 0.4, 0.8));
w.addObject(sphere);
```

Cylinders and cones are infinite by default — bound and cap them explicitly:

```cpp
auto cyl = std::make_shared<Cylinder>();
cyl->setMin(-1.0);
cyl->setMax(1.0);
cyl->setClosed(true);
cyl->setTransform(translation(2.0, 0.0, 0.0) * rotation_x(PI / 6.0) * scaling(0.4, 0.6, 0.4));
w.addObject(cyl);
```

### 3. Transform shapes

Transforms are 4x4 matrices, composed with `*` and applied via `setTransform`. Available building blocks:

```cpp
translation(x, y, z)
scaling(x, y, z)
rotation_x(radians)
rotation_y(radians)
rotation_z(radians)
shearing(xy, xz, yx, yz, zx, zy)
```

Matrices compose left-to-right the way you'd read them applied (rightmost applied first), e.g. `translation(...) * rotation_y(...) * scaling(...)` scales, then rotates, then translates.

### 4. Set materials & patterns

`Materials` controls shading and can be edited in place via `shape->getMaterials()`:

```cpp
auto& mat = shape->getMaterials();
mat.setColor(Color(0.8, 0.1, 0.1));
mat.setAmbient(0.1);
mat.setDiffuse(0.7);
mat.setSpecular(0.4);
mat.setShininess(50.0);
mat.setReflectivity(0.3);      // 0 = matte, 1 = mirror
mat.setTransparency(0.0);      // 0 = opaque, 1 = fully transparent
mat.setReflectiveIndex(1.5);   // index of refraction, used when transparency > 0
```

Procedural patterns (`StripePattern`, `GradientPattern`, `RingPattern`, `Checker3DPattern`) can replace a flat color, and have their own transform for scaling/orienting the pattern independently of the shape:

```cpp
auto pattern = std::make_shared<Checker3DPattern>(Color(0.25, 0.25, 0.25), Color(0.75, 0.75, 0.75));
pattern->setTransform(scaling(0.5, 0.5, 0.5));
shape->getMaterials().setPattern(pattern);
```

### 5. Group shapes for faster rendering

Shapes that sit near each other spatially can be batched into a `Group`. The group's `Bounds` are computed once and let the renderer reject an entire cluster with a single bounding-box test instead of testing every child individually:

```cpp
auto cluster = std::make_shared<Group>();
cluster->addChild(shapeA);
cluster->addChild(shapeB);
cluster->addChild(shapeC);
w.addObject(cluster);   // add the group itself, not the individual children
```

This is purely a performance optimization — a grouped scene renders identically to the same scene added flat, just faster (see [Benchmarks](#benchmarks)).

### 6. Set up the camera

```cpp
Camera camera(1200, 600, PI / 3.0);   // width, height, field of view (radians)
camera.setTransform(viewTransform(
    point(0.0, 2.0, -10.0),   // eye position
    point(0.0, 0.0, 0.0),     // look-at point
    vector(0.0, 1.0, 0.0)     // up direction
));
```

### 7. Render and save

```cpp
Canvas image = camera.render(w);                    // single-threaded
// or:
Canvas image = camera.renderMultiThreads(w, 0);      // 0 = auto-detect core count

writePPM(image, "scene.ppm");
```

Open the resulting `.ppm` with most image viewers, or convert it:

```bash
convert scene.ppm scene.png
```

## Benchmarks

The project includes a built-in benchmark comparing flat vs. grouped scene graphs, each single- and multi-threaded, across scenes of 50–500 mixed objects at 1200x600 resolution:

| Objects | Flat, 1 Thread | Flat, Multi-Thread | Group-Bounded, 1 Thread | Group-Bounded, Multi-Thread |
|---|---|---|---|---|
| 50  | 1840 ms | 285 ms (6.4x) | 1029 ms (1.8x) | 113 ms (16.3x) |
| 100 | 3716 ms | 711 ms (5.2x) | 1479 ms (2.5x) | 175 ms (21.2x) |
| 150 | 5347 ms | 651 ms (8.2x) | 1606 ms (3.3x) | 191 ms (27.9x) |
| 200 | 6556 ms | 1319 ms (5.0x) | 1652 ms (4.0x) | 194 ms (33.8x) |
| 250 | 7735 ms | 1548 ms (5.0x) | 1673 ms (4.6x) | 193 ms (40.0x) |
| 300 | 10699 ms | 2201 ms (4.9x) | 2417 ms (4.4x) | 393 ms (27.2x) |
| 500 | 17277 ms | 3654 ms (4.7x) | 3820 ms (4.5x) | 459 ms (37.6x) |

**Takeaway:** grouping and multi-threading compound — bounding boxes cut how many objects each ray needs to test, and threading spreads the remaining work across cores, together reaching up to ~40x over the naive single-threaded baseline.

## Future Improvements

- Replace the flat `Group` bounding check with a real BVH (median-split or SAH) for sub-linear scaling as object counts grow further
- Texture mapping / UV-based image patterns, beyond the current procedural ones
- Anti-aliasing via supersampling, and soft shadows from area lights
- A simple external scene description format (JSON/YAML) instead of hard-coding scenes in C++

## Lessons Learned

This project pushed me past "does the math work" into "does it perform," which turned out to be a different problem: adding bounding volumes and threading meant thinking about spatial locality and work distribution, not just intersection formulas. It was a good hands-on introduction to:
- Recursive algorithms with a bounded depth (reflection/refraction)
- Spatial acceleration structures and why they matter as scene complexity grows
- `std::thread`-based parallelism and measuring its real-world payoff
- Matrix-based transform composition for a full 3D scene graph

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
