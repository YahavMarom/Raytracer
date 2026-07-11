#include <iostream>
#include "Canvas.h"


Canvas::Canvas(int width, int height)
    : m_width {width}
    , m_height {height}
    , m_pixels {static_cast<std::vector<Color>::size_type>(width * height), Color(0,0,0) }
    {}

void Canvas::writePixel(int row, int col, const Color& color) {
    m_pixels[row * m_width + col] = color;
}

Color Canvas::pixelAt(int row, int col) const{
    return m_pixels[row * m_width + col];
}

