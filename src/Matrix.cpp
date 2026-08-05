
#include "Matrix.h"
#include "Constants.h"
#include <cmath>
#include <stdexcept>



Matrix::Matrix()
    {
        m_data.fill(0.0);
    }

Matrix::Matrix(double m00, double m01, double m02, double m03,
               double m10, double m11, double m12, double m13,
               double m20, double m21, double m22, double m23,
               double m30, double m31, double m32, double m33)
    : m_data{m00, m01, m02, m03,
             m10, m11, m12, m13,
             m20, m21, m22, m23,
             m30, m31, m32, m33} 
{
}

Matrix Matrix::identity() {
    return Matrix(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}


double& Matrix::operator()(int row, int col) {
    return m_data[static_cast<std::size_t>(row * 4 + col)];
}

const double& Matrix::operator()(int row, int col) const
{
    return m_data[static_cast<std::size_t>(row * 4 + col)];
}



Matrix Matrix::transpose() const {
    return Matrix(
        (*this)(0, 0), (*this)(1, 0), (*this)(2, 0), (*this)(3, 0),
        (*this)(0, 1), (*this)(1, 1), (*this)(2, 1), (*this)(3, 1),
        (*this)(0, 2), (*this)(1, 2), (*this)(2, 2), (*this)(3, 2),
        (*this)(0, 3), (*this)(1, 3), (*this)(2, 3), (*this)(3, 3)
        
    );

}

double Matrix::minor_det(int withoutRow, int withoutCol) const{
    double M[3][3];
    int r_idx = 0;
    for (int i = 0; i < 4; i++) {
        if (i == withoutRow) {
            continue;
        }
        int c_idx = 0;
        for (int j = 0; j < 4; j++) {
            if (j == withoutCol) {
                continue;
            }
            M[r_idx][c_idx] = (*this)(i,j);
            c_idx++;
        }
        r_idx++;
        
    }
    return M[0][0] * (M[1][1] * M[2][2] - M[2][1] * M[1][2]) 
           -M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
           +M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
}

double Matrix::cofactor(int withoutRow, int withoutCol) const {
    double det = minor_det(withoutRow, withoutCol);
    return ((withoutRow + withoutCol) % 2 == 0) ? det : -det;   

}

 
double Matrix::determinant() const {
    double det = 0;
    for (int c = 0; c < 4; c++) {
        det += (*this)(0, c) * cofactor(0, c);
    }
    return det;



}
Matrix Matrix::inverse() const {
    double Det = determinant();
    if (std::abs(Det) < EPSILON) {
        throw std::invalid_argument("Matrix is not invertible");
    }
    Matrix inverted_matrix = Matrix();

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            inverted_matrix(c, r) = cofactor(r, c) / Det; 
        }

    }

    return inverted_matrix;
}














bool operator==(const Matrix& a, const Matrix& b) {

    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            if ( std::abs( a(row, col) - b(row, col) ) > EPSILON) {
                return false;
            }
        }
    }
    return true;

}


Matrix operator*(const Matrix& a, const Matrix& b){
   
    Matrix M = Matrix();

    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++) {
            for (int c = 0; c < 4; c++) {
                M(row, col) += a(row, c) * b(c, col);
            }
        }
    }
    return M;

}

Tuple operator*(const Matrix& a, const Tuple& t) {
    double x = a(0, 0) * t.getX() + a(0, 1) * t.getY() + a(0, 2) * t.getZ() + a(0, 3) * t.getW();
    double y = a(1, 0) * t.getX() + a(1, 1) * t.getY() + a(1, 2) * t.getZ() + a(1, 3) * t.getW();
    double z = a(2, 0) * t.getX() + a(2, 1) * t.getY() + a(2, 2) * t.getZ() + a(2, 3) * t.getW();
    double w = a(3, 0) * t.getX() + a(3, 1) * t.getY() + a(3, 2) * t.getZ() + a(3, 3) * t.getW();

    return Tuple(x, y, z, w);
}


std::ostream& operator<<(std::ostream& os, const Matrix& M) 
{   
    for (int i = 0; i < 4; i++){
        
        for (int j = 0; j < 4; j++) {
            os << "| " << M(i, j) << " ";
        }
        os << "|\n";

    }
    os << "\n";
    
    return os;
}

