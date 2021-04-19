//
// Created by EVGEN on 05.04.2021.
//

#include "Vect.h"
#include <iostream>

namespace OOP {

    Vect::Vect(unsigned int size, double *data, bool horizontal) : Matrix(size, 1, data) {
        std::cout << " + Vect " << get_id() << std::endl;

        if (!horizontal) {
           std::swap(width, height);
        }

        m_size = width * height;
    }

    Vect::~Vect() {
        std::cout << " - Vect " << get_id() << std::endl;
    }


    Vect::Vect(const Vect &A) : Matrix(A) {
        m_size = A.m_size;
    }

    Vect &Vect::operator=(const Vect &B){
        Matrix::operator=(B);
        m_size = B.m_size;
        return *this;
    }



    Vect::Vect(Vect &&A) noexcept : Matrix(std::move(A)) {
        m_size = A.m_size;
    }

    Vect &Vect::operator=(Vect &&B) noexcept {
        Matrix::operator=(std::move(B));
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

    Vect &Vect::operator*=(const Matrix &B) {
        Matrix::operator*=(B);
        if (width != 1 && height != 1)
            throw std::invalid_argument("Method must return only Vect");
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
