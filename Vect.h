#ifndef LAB3_VECT_H
#define LAB3_VECT_H

#include "Matrix.h"

namespace OOP {
    class Vect : public Matrix {

    private:
        unsigned m_size;

    public:
        explicit Vect(unsigned size = 0, double* data = nullptr, bool horizontal = true);
        //explicit Vect(unsigned size = 1, double (*func)(unsigned r) = nullptr, bool horizontal = true);

        ~Vect();

        Vect(const Vect& A);
        Vect& operator =(const Vect& B);

        Vect(Vect&& A) noexcept ;
        Vect& operator =(Vect&& B);

        unsigned getSize() const;

        Vect& operator *=(double B) override;
        Vect& operator +=(const Vect& B);
        Vect& operator -=(const Vect& B);

        friend Vect operator +(const Vect& A, const Vect& B);
        friend Vect operator -(const Vect& A, const Vect& B);
        friend Vect operator *(const Vect& A, double B);
    };
}


#endif //LAB3_VECT_H
