#ifndef LAB3_MATR_H
#define LAB3_MATR_H

#include <cstring>

namespace OOP {
    class Matrix {
    private:
        class Row {
        private:
            unsigned m_width;
            double *m_data;
        public:
            Row(unsigned width, double* data);

            double operator[](unsigned idx) const;
            double& operator[](unsigned idx);
        };

    protected:
        unsigned width;
        unsigned height;
        double* data;
        int id;
        static int counter;

    public:
                 Matrix(unsigned mwidth, unsigned mheight, double* mdata = nullptr);
        explicit Matrix(unsigned wh = 0,                   double* mdata = nullptr);

        Matrix(unsigned mwidth, unsigned mheight, double (*func)(unsigned r));
        Matrix(unsigned wh,                       double (*func)(unsigned r));

        ~Matrix();

        Matrix(const Matrix& A);
        Matrix& operator =(const Matrix& B);

        Matrix(Matrix&& A);
        Matrix& operator =(Matrix&& B);

        unsigned get_size() const;
        unsigned get_width() const;
        unsigned get_height() const;
        int get_id() const;

        double min() const;
        double max() const;

        bool isOK(const Matrix& B) const;
        bool same_size(const Matrix& B) const;

        void show();

        virtual Matrix& operator *=(const Matrix& B);

        virtual Matrix& operator *=(double B);
        Matrix& operator +=(const Matrix& B);
        Matrix& operator -=(const Matrix& B);

        const Row operator[] (unsigned index_h) const;
        Row operator[] (unsigned index_h);

        friend Matrix operator +(const Matrix& A, const Matrix& B);
        friend Matrix operator -(const Matrix& A, const Matrix& B);
        friend Matrix operator *(const Matrix& A, const Matrix& B);
    };


}

#endif //LAB3_MATR_H