#include "Canvas.h"
#include <iostream>

Canvas::Canvas(int width, int height)
    : m_width {width}
    , m_height {height}
    , m_pixels {static_cast<std::vector<Color>::size_type>(width * height), Color(0,0,0) }
    {}

void Canvas::writePixel(int x, int y, const Color& color) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return;
    }
    m_pixels[y * m_width + x] = color;
}

Color Canvas::pixelAt(int x, int y) const{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return Color(0, 0, 0);
    }
    return m_pixels[y * m_width + x];
}

