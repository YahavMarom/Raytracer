#include "Camera.h"
#include "Canvas.h"

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

Canvas Camera::render(const World& world) const {
    Canvas canvas(m_hsize, m_vsize); 

    for (int y = 0; y < m_vsize; y++) {
        for (int x = 0; x < m_hsize; x++) {
            const Ray r {rayForPixel(x, y)};
            Color c {color_at(world, r)};
            canvas.writePixel(x, y, c);
        }
    }

    return canvas;

}