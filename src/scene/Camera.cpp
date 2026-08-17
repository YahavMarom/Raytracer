#include "Camera.h"
#include <thread>
#include <atomic>
#include <algorithm>
#include <cmath>

Camera::Camera(int hsize, int vsize, double fieldOfView)
    : m_hsize {hsize}
    , m_vsize {vsize}
    , m_fieldOfView {fieldOfView}
{


    double half_view {tan(m_fieldOfView / 2.0)};
    double aspect { static_cast<double>(m_hsize) / static_cast<double>(m_vsize) };

    if (aspect >= 1.0) {
        m_halfWidth = half_view;
        m_halfHeight = half_view / aspect;
    }
    else {
        m_halfWidth = half_view * aspect;
        m_halfHeight = half_view;
    }
     m_pixelSize = (m_halfWidth * 2.0) / static_cast<double>(m_hsize);
}


Ray Camera::rayForPixel(int px, int py) const{
    double xoffset {(px + 0.5) * m_pixelSize};
    double yoffset {(py + 0.5) * m_pixelSize};

    double world_x {m_halfWidth - xoffset};
    double world_y {m_halfHeight - yoffset};

    Matrix invMatrix {m_transform.inverse()};
    Tuple pixel {invMatrix * point(world_x, world_y, -1) };
    Tuple origin {invMatrix * point(0, 0, 0)};
    Tuple direction {(pixel - origin).normalize()};

    return Ray(origin, direction);

}


// at colorAt, 5 is the recursion depth limit. 
Canvas Camera::render(const World& world) const {
    Canvas canvas(m_hsize, m_vsize); 

    for (int y = 0; y < m_vsize; y++) {
        for (int x = 0; x < m_hsize; x++) {
            const Ray r {rayForPixel(x, y)};
            Color c {colorAt(world, r, 5)};
            canvas.writePixel(x, y, c);
        }
    }

    return canvas;

}



Canvas Camera::renderMultiThreads(const World& world, int numThreads) const {
    Canvas canvas(m_hsize, m_vsize); 

    constexpr int tileSize = 32;
    const int numTilesX = (m_hsize + tileSize - 1) / tileSize;
    const int numTilesY = (m_vsize + tileSize - 1) / tileSize;
    const int totalTiles = numTilesX * numTilesY;

    std::atomic<int> nextTile{0};

    // Ensure at least 1 thread runs if hardware_concurrency() returns 0
    if (numThreads == 0) {
        numThreads = std::max(1u, std::thread::hardware_concurrency());
    }
    
    std::vector<std::thread> workers;
    workers.reserve(numThreads);

    for (int t = 0; t < numThreads; ++t) {
        workers.emplace_back([&]() {
            int tileIdx = 0;
            while ((tileIdx = nextTile.fetch_add(1, std::memory_order_relaxed)) < totalTiles) {
                const int tileY = (tileIdx / numTilesX) * tileSize;
                const int tileX = (tileIdx % numTilesX) * tileSize;

                const int startY = tileY;
                const int endY = std::min(tileY + tileSize, m_vsize);
                const int startX = tileX;
                const int endX = std::min(tileX + tileSize, m_hsize);

                for (int y = startY; y < endY; ++y) {
                    for (int x = startX; x < endX; ++x) {
                        const Ray r = rayForPixel(x, y);
                        const Color c = colorAt(world, r, 5);
                        canvas.writePixel(x, y, c);
                    }
                }
            }
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    return canvas;

}