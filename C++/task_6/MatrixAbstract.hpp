#pragma once
#include <vector>
#include <istream>

template <class DataType>
class MatrixAbstract
{
public:
    virtual void matvec(const DataType *x, DataType *y, bool Transpose) const = 0;
    virtual ~MatrixAbstract() = default;

    // OPTIONAL:
    /* 
    virtual const double &operator()(int i, int j) const ;

    virtual double &operator()(int i, int j) ;
    */
};





