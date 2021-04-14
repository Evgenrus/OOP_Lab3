//
// Created by EVGEN on 05.04.2021.
//

#include "Vect.h"
#include <iostream>

namespace OOP {

    Vect::Vect(unsigned int size, double *data, bool horizontal) {
        if (horizontal) {
            Matrix(size, 1, data);
            size = width;
        } else {
            Matrix(1, size, data);
            size = height;
        }
    }

    Vect::~Vect() {
        delete[] data;
    }


    Vect::Vect(const Vect &A) : Matrix(A) {
        m_size = A.m_size;
    }

    Vect::Vect(Vect &&A)  noexcept : Matrix(A) {
        m_size = A.m_size;
    }

    Vect &Vect::operator=(const Vect &B){
        Matrix::operator=(B);
        m_size = B.m_size;
        return *this;
    }

    Vect &Vect::operator=(Vect &&B) {
        Matrix::operator=(B);
        m_size = B.m_size;
        return *this;
    }


    unsigned Vect::getSize() const {
        return m_size;
    }


    Vect &Vect::operator*=(double B) {
        Matrix::operator*=(B);
        return *this;
    }

    Vect &Vect::operator+=(const Vect &B) {
        Matrix::operator+=(B);
        return *this;
    }

    Vect &Vect::operator-=(const Vect &B) {
        Matrix::operator-=(B);
        return *this;
    }

    Vect operator+(const Vect &A, const Vect &B) {
        return std::move(Vect(A) += B);
    }

    Vect operator-(const Vect &A, const Vect &B) {
        return std::move(Vect(A) -= B);
    }

    Vect operator*(const Vect &A, double B) {
        return std::move(Vect(A) *= B);
    }
}
