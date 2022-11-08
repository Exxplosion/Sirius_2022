#pragma once
#include "MatrixAbstract.hpp"
#include <istream>
#include <string>
#include <sstream>
#include <iostream>

template <class DataType, class IndexType>
class DenseMatrix : public MatrixAbstract<DataType>
{
    private:
        IndexType rows_number = 0;
        IndexType cols_number = 0;
        DataType *data = nullptr;
        void allocate(IndexType rows_number, IndexType cols_number);
        void deallocate();

    public:

        IndexType get_rows_number() const {return rows_number;}
        IndexType get_cols_number() const { return cols_number; }

        virtual void matvec(const DataType *x, DataType *y, bool Transpose) const override;
        virtual ~DenseMatrix() override;

        DenseMatrix(IndexType rows_number, IndexType cols_number, std::istream &is);
        inline const DataType& operator()(IndexType i, IndexType j) const;

};



template<class DataType, class IndexType>
DenseMatrix<DataType, IndexType>::DenseMatrix(IndexType rows_number, IndexType cols_number, std::istream &is)
{
    allocate(rows_number, cols_number);

    for (IndexType i = 0; i < rows_number; i++)
    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream(std::move(line));

        if ((line_stream.eof()) || (line_stream.fail()))
        {
            throw std::runtime_error("Cannot read enough rows");
        }

        for (IndexType j = 0; j < cols_number; j++)
        {
            line_stream >> data[i * cols_number + j];
            if (line_stream.fail())
            {
                throw std::runtime_error("Cannot read enough cols");
            }
        }

        if (DataType tmp; (line_stream >> tmp, !line_stream.fail()))
        {
            throw std::runtime_error("To much cols");
        }
    }
    std::string line;
    std::getline(is, line);
    std::istringstream line_stream(std::move(line));

    DataType tmp;
    line_stream >> tmp;
    if (!line_stream.fail())
    {
        throw std::runtime_error("To much rows");
    }
}


template<class DataType, class IndexType>
void DenseMatrix<DataType, IndexType>::allocate(IndexType rows_number, IndexType cols_number)
{
    if (rows_number <= 0 || cols_number <= 0)
    {
        throw std::runtime_error("Cannot create matrix with nonpositive dimension");
    }
    this->rows_number = rows_number;
    this->cols_number = cols_number;

    data = new DataType[size_t(rows_number) * size_t(cols_number)];
}

template <class DataType, class IndexType>
void DenseMatrix<DataType, IndexType>::deallocate()
{
    delete[] data;
    data = nullptr;
    cols_number = 0;
    rows_number = 0;
}

template<class DataType, class IndexType>
inline const DataType& DenseMatrix<DataType, IndexType>::operator()(IndexType i, IndexType j) const
{
    if (i < 0 || i >= rows_number || j < 0 || j >= cols_number)
    {
        throw std::runtime_error("Index out of range");
    }
    return data[size_t(i) * size_t(cols_number) + j];
}

//0 1 2 3 
//4 5 6 7


template <class DataType, class IndexType>
DenseMatrix<DataType, IndexType>::~DenseMatrix()
{
    deallocate();
}

template<class DataType, class IndexType>
void DenseMatrix<DataType, IndexType>::matvec(const DataType *x, DataType *y, bool Transpose) const
{
    // demension x must be equal demension y must be equal second demension matrix

    for (IndexType i = 0; i < rows_number; i++)
    {
        for (IndexType j = 0; j < cols_number; j++)
        {
            if (Transpose)
            {
                y[i] += ((*this).operator()(j, i)) * x[j]; //FOR ONLY IN ROWS_MUNBER  = COLS_MUMBER
            }
            else
            {
                y[i] += ((*this).operator()(i, j)) * x[j];
            }
        }
    }
}
