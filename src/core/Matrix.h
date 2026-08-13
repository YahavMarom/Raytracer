#ifndef MATRIX_H
#define MATRIX_H


#include "Tuple.h"
#include <array>
#include <iostream>
#include <stdexcept>

class Matrix { 
private:
    std::array<double, 16> m_data;
    

public:
    Matrix();


    Matrix(double m00, double m01, double m02, double m03,
           double m10, double m11, double m12, double m13,
           double m20, double m21, double m22, double m23,
           double m30, double m31, double m32, double m33);
    
    static const Matrix Identity;

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;


    Matrix transpose() const;

    double minor_det(int withoutRow, int withoutCol) const;
    double cofactor(int withoutRow, int withoutCol) const;

    double determinant() const;
    Matrix inverse() const;

    


};

bool operator==(const Matrix& a, const Matrix& b);

Matrix operator*(const Matrix& a, const Matrix& b);
Tuple operator*(const Matrix& a, const Tuple& t);

std::ostream& operator<<(std::ostream& os, const Matrix& M);

#endif