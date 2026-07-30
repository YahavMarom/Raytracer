#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Ray.h"
#include "Canvas.h"
#include "World.h"

class Camera {
private:
    int m_hsize;
    int m_vsize;
    double m_fieldOfView;
    Matrix m_transform{Matrix::identity()}; 

    double m_halfWidth;
    double m_halfHeight;
    double m_pixelSize;

    void calculatePixelSize(); 

public:
    Camera(int hsize, int vsize, double fieldOfView);

    
    int getHSize() const { return m_hsize; }
    int getVSize() const { return m_vsize; }
    double getFieldOfView() const { return m_fieldOfView; }
    double getPixelSize() const { return m_pixelSize; }
    const Matrix& getTransform() const { return m_transform; }

    
    void setTransform(const Matrix& transform) { m_transform = transform; }

    
    Ray rayForPixel(int px, int py) const;
    Canvas render(const World& world) const;
};

#endif