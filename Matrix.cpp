#include <iostream>
#include "Matrix.h"

namespace OOP
{

    Matrix::Matrix(unsigned mwidth, unsigned mheight, double* mdata)
            : width(mwidth), height(mheight)
    {
        height = mheight;
        width = mwidth;
        //std::cout << "Matrix(unsigned mwidth = 0, unsigned mheight = 0, double* mdata = nullptr)" << std::endl;
        id = ++counter;
        std::cout << "Matrix " << get_id() << " was created" << std::endl;

        auto size = height * width;

        if (size == 0)
        {
            height = width = 0;
            data = nullptr;
            return;
        }

        if(mdata == nullptr)
        {
            data = new double[mwidth*mheight]();
        } else
        {
            data = new double[mwidth*mheight];
            std::copy(mdata, mdata + (height*width), data);
        }
    }

    Matrix::Matrix(unsigned mwidth, unsigned mheight, double (*func)(unsigned))
            : Matrix(mwidth, mheight)
    {
        std::cout << "Matrix(unsigned mwidth, unsigned mheight, double* (*func)(unsigned, unsigned, unsigned))" << std::endl;
        if(data != nullptr)
        {
            data = new double[mwidth*mheight]();
            double r;
            std::cout << "Enter r";
            std::cin >> r;
            for(int i=0; i<mheight * mwidth; i++)
            {
                data[i] = (*func)(r);
            }
        }
        else
        {
            data = new double[mwidth*mheight]();
            for(int i=0; i<(mheight*mwidth); i++)
                data[i] = 0;
        }
    }

    Matrix::Matrix(unsigned wh, double *mdata)
            : Matrix(wh, wh, mdata)
    {
        std::cout << "Matrix(unsigned wh, double *mdata)" << std::endl;
    }

    Matrix::Matrix(unsigned wh, double (*func)(unsigned int))
            : Matrix(wh, wh, (*func))
    {
        std::cout << "Matrix(unsigned wh, double* (*func)(unsigned int, unsigned int, unsigned int))" << std::endl;
        if(wh > 0)
        {
            if(data != nullptr)
            {
                data = new double[wh * wh]();
                //std::copy(temp, temp + (wh * wh), data);
                double r;
                std::cout << "Enter r";
                std::cin >> r;
                for(int i=0; i<wh * wh; i++)
                {
                    data[i] = (*func)(r);
                }
            } else
            {
                data = new double[width*height]();
                for(int i=0; i<(height*width); i++)
                    data[i] = 0;
            }
        } else throw std::invalid_argument("Invalid argument");
    }

    Matrix::Matrix(const Matrix &A) {
        std::cout << "Constructor copy" << std::endl;
        height = A.height;
        width = A.width;
        if (width > 0 && height > 0)
        {
            std::copy(A.data, A.data + (width * height), data);
        } else throw "OOP::Matrix::Matrix(const OOP::Matrix *A); Matrix(" +
                     std::to_string(id) + "); Invalid height or width";
    }

    Matrix::Matrix(Matrix &&A)
            : width(A.width), height(A.height), data(A.data)
    {
        std::cout << "Constructor move" << std::endl;
        width = 0;
        height = 0;
        data = nullptr;
        id = ++counter;
    }

    Matrix::~Matrix()
    {
        std::cout << "Destructor" << std::endl;
        delete[] data;
    }

    int Matrix::get_id() const
    {
        return id;
    }

    unsigned Matrix::get_width() const
    {
        return width;
    }

    unsigned Matrix::get_height() const
    {
        return height;
    }

    double Matrix::min() const
    {
        if (data == nullptr) throw "OOP::Matrix::min(); Matrix(" + std::to_string(id) + "); Data is empty";

        double current, min;
        min = data[0];
        for(int i=0; i<(height*width); i++)
        {
            current = data[i];
            if(current < min)
                min = current;
        }
        return min;
    }

    double Matrix::max() const
    {
        if(height > 0 && width > 0)
        {
            double current, max;
            max = data[0];
            for(int i=0; i<(height*width); i++)
            {
                current = data[i];
                if(current > max)
                    max = current;
            }
            return max;
        }
        else
            throw "OOP::Matrix::min(); Matrix(" + std::to_string(id) + "); Data is empty";
    }

    bool Matrix::isOK(const Matrix& B) const
    {
        return (width == B.height);
    }

    bool Matrix::same_size(const Matrix& B) const
    {
        return height == B.height && width == B.width;
    }

    Matrix &Matrix::operator*=(const Matrix &B)
    {
        if(data == nullptr || B.data == nullptr)
            throw "OOP::Matrix &OOP::Matrix::operator*=(const OOP::Matrix *B)" +
                  std::to_string(id) + "); Data is empty";
        if(this->isOK(B))
        {
            double* new_data = new double [B.width * height];
            for (long unsigned int i = 0; i < height; i++)
                for (long unsigned int j = 0; j < B.width; j++)
                    for (long unsigned int r = 0; r < width; r++)
                        new_data[i * B.width + j] += data[i * width + r] * B.data[r * B.width + j];
            delete[] data;
            data = new_data;
            return *this;
        }
        else throw "OOP::Matrix &OOP::Matrix::operator*=(const OOP::Matrix *B); Matrix(" +
                   std::to_string(id) + "); Matrix multiply is impossible";
    }

    Matrix &Matrix::operator*=(double B)
    {
        if(data == nullptr)
            throw "OOP::Matrix &OOP::Matrix::operator*=(double B); Matrix(" +
                  std::to_string(id) + "); Data is empty";
        for(int i=0; i<(height*width); i++)
            data[i] *= B;
        return *this;
    }

    Matrix &Matrix::operator+=(const Matrix &B) {
        if(data == nullptr || B.data == nullptr)
            throw "OOP::Matrix &OOP::Matrix::operator+=(const OOP::Matrix *B); Matrix(" +
                  std::to_string(id) + "); Data is empty";
        if(this->same_size(B))
        {
            for(int i = 0; i<(height*width); i++)
                data[i] += B.data[i];
        } else throw "OOP::Matrix &OOP::Matrix::operator+=(const OOP::Matrix *B); Matrix(" +
                     std::to_string(id) + "); Matrix summarize is impossible";
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &B)
    {
        if(data == nullptr || B.data == nullptr)
            throw "OOP::Matrix &OOP::Matrix::operator-=(const OOP::Matrix *B); Matrix(" +
                  std::to_string(id) + "); Data is empty";
        if(this->same_size(B))
        {
            for(int i = 0; i < (height * width); i++)
                data[i] -= B.data[i];
        } else throw "OOP::Matrix &OOP::Matrix::operator+=(const OOP::Matrix *B); Matrix(" +
                     std::to_string(id) + "); Matrix summarize is impossible";
        return *this;
    }

    Matrix &Matrix::operator=(const Matrix &B) {
        delete[] data;
        width = B.width;
        height = B.height;
        data = new double[width*height];
        std::copy(B.data, B.data + (height*width), data);
        return *this;
    }

    Matrix &Matrix::operator=(Matrix &&B) {
        delete[] data;
        width = B.width;
        height = B.height;
        data = new double[height*width];
        std::copy(B.data, B.data + (height*width), data);
        delete[] B.data;
        B.height = 0;
        B.width = 0;
        B.data = nullptr;
        return *this;
    }

    Matrix::Row Matrix::operator[] (unsigned index_h) {
        if(index_h > height)
            throw "OOP::Vector &OOP::Matrix::operator[](unsigned index_h); Matrix(" + std::to_string(id) + "); Out of range;";

        return Row(width, data + width * index_h);
    }

    const Matrix::Row Matrix::operator[](unsigned int index_h) const {
        if(index_h > height)
            throw "OOP::Vector &OOP::Matrix::operator[](unsigned index_h); Matrix(" + std::to_string(id) + "); Out of range;";

        return Row(width, data + width * index_h);
    }

    void Matrix::show(){
        if (width < 0 || height < 0)
            throw "Wrong argument";
        if (data == nullptr)
        {
            std::cout << "{ }  Empty Matrix\n";
            return;
        }
        std::cout << "---------------------------------------"
                  << std::endl;
        for(int i=0; i<height*width; i++)
        {
            std::cout << data[i] << ", ";
            if((i+1)%width == 0)
                //std::cout << " }" << std::endl << "\t{";
                std::cout << std::endl;
        }
        std::cout << "---------------------------------------"
                  << std::endl;
    }

    Matrix::Row::Row(unsigned width, double *data) : m_width(width) {
        if(data == nullptr) {
            m_data = new double[width]();
        }
        else {
            m_data = new double[width]();
            std::copy(data, data+width, m_data);
        }
    }

    double Matrix::Row::operator[](unsigned idx) const {
        if(idx > m_width) throw std::invalid_argument("wrong argument 'idx'\n");
        return m_data[idx];
    }

    double &Matrix::Row::operator[](unsigned idx) {
        if(idx > m_width) throw std::invalid_argument("wrong argument 'idx'\n");
        return m_data[idx];
    }

    Matrix operator+(const Matrix &A, const Matrix &B) {
        return std::move(Matrix(A) += B);
    }

    Matrix operator*(const Matrix &A, const Matrix &B) {
        return std::move(Matrix(A) *= B);
    }

    Matrix operator-(const Matrix &A, const Matrix &B) {
        return std::move(Matrix(A) -= B);
    }

}