#pragma once
#include <vector>
#include <istream>
#include "MatrixAbstract.hpp"

template <class DataType, class OffsetType = int, class IndexType = int>
class SparseMatrixAbstract : public MatrixAbstract<DataType>
{
    public:
        virtual void matvec(const DataType *x, DataType *y, bool Transpose) const = 0;
        virtual ~SparseMatrixAbstract() = default;
        //virtual SparseMatrixAbstract() ?
    protected:

        virtual void sort() = 0;

        virtual std::vector<OffsetType> read_offsets(IndexType m, std::istream &is);

        //virtual std::vector<Element> read_elements(OffsetType nz, std::istream &is) = 0;

        virtual IndexType calc_max_index() const = 0;

        //SparseMatrixAbstract operator+(SparseMatrixAbstract &o) const; ?????
};
