#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <vector>
#include "Color.h"


class Canvas {
private:
    int m_width {};
    int m_height {};
    std::vector<Color> m_pixels {};
    

public:
    Canvas(int width, int height);

    int getWidth() const {return m_width; }
    int getHeight() const {return m_height; }

    void writePixel(int row, int col, const Color& color);
    Color pixelAt(int row, int col) const;


};

#endif