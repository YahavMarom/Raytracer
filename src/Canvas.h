#ifndef CANVAS_H
#define CANVAS_H


#include "Color.h"
#include <vector>
#include <iostream>


class Canvas {
private:
    int m_width {};
    int m_height {};
    std::vector<Color> m_pixels {};
    

public:
    Canvas(int width, int height);

    int getWidth() const {return m_width; }
    int getHeight() const {return m_height; }

    void writePixel(int x, int y, const Color& color);
    Color pixelAt(int x, int y) const;


};

#endif