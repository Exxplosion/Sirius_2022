#pragma once
#include "SparseMatrixAbstract.hpp"
#include <tuple>
#include <algorithm>
#include <iostream>

template<class DataType, class OffsetType, class IndexType>
class COOMatrix : public SparseMatrixAbstract<DataType, OffsetType, IndexType>
{
    private:
        std::vector<std::tuple<IndexType, IndexType, DataType>> m_element;
        IndexType m_rows_number;
        IndexType m_cols_number;
        size_t m_count_elements;

        std::vector<OffsetType> read_offsets(IndexType m, std::istream &is);

    public:
        void matvec(const DataType *x, DataType *y, bool Transpose) const override;

        //std::vector<OffsetType> read_offsets(IndexType m, std::istream &is) { std::vector<OffsetType> m; return m; }; //no comments pls.....;

        IndexType calc_max_index() const {return m_cols_number; } ;

        COOMatrix() = default;
        COOMatrix(IndexType rows_count, IndexType cols_count, std::istream &is);

        void print_matrix() const;

        void sort() {return; } ;

        //COOMatrix operator+(COOMatrix &o) const;
};

template <class DataType, class OffsetType, class IndexType>
COOMatrix<DataType, OffsetType, IndexType>::COOMatrix(IndexType rows_count, IndexType cols_count, std::istream &is)
{

    m_rows_number = rows_count;
    m_cols_number = cols_count;

    std::vector<IndexType> cols_indexes;
    std::vector<IndexType> rows_indexes;
    std::vector<DataType> elements;

    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream_first(std::move(line));

        //IndexType tmp;
        //line_stream_first >> tmp;
        //std::cout << "HEHE" << tmp << std::endl;
        while (!(line_stream_first.eof()))
        {
            IndexType tmp;
            line_stream_first >> tmp;

            if (!(line_stream_first.fail()))
            {
                //throw std::runtime_error("Indexes rows string has some other info"); DO NOT KNOW WHY
            }
            rows_indexes.push_back(tmp);
        }

        /* if (IndexType tmp; (line_stream_first >> tmp, !line_stream_first.fail()))
        {
            throw std::runtime_error("To much rows indexes");
        } */

    }

    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream_second(std::move(line));

        while (!(line_stream_second.eof()))
        {
            IndexType tmp;
            line_stream_second >> tmp;
            cols_indexes.push_back(tmp);
        }

    }

    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream_third(std::move(line));

        while (!(line_stream_third.eof()))
        {
            DataType tmp;
            line_stream_third >> tmp;
            elements.push_back(tmp);
        }
    }

    if ((cols_indexes.size() != rows_indexes.size()) || (cols_indexes.size() != elements.size()))
    {
        throw std::runtime_error("count cols or elements or rows do not equal");
    }

    for (size_t i = 0; i < rows_indexes.size(); i++)
    {
        m_element.push_back(std::make_tuple(rows_indexes[i], cols_indexes[i], elements[i]));
    }

    m_rows_number = *std::max_element(std::begin(rows_indexes), std::end(rows_indexes));

    m_cols_number = *std::max_element(std::begin(cols_indexes), std::end(cols_indexes));
    m_count_elements = elements.size();

    //здесь нужна сортировка tupla, но как сделать.... sort();
}





template <class DataType, class OffsetType, class IndexType>
void COOMatrix<DataType, OffsetType, IndexType>::print_matrix() const
{
    for (size_t i = 0; i < m_count_elements; i++)
    {
        std::cout << "i, j, a :" << std::get<0>(m_element[i]) << " " << std::get<1>(m_element[i]) << std::get<2>(m_element[i]) << std::endl;
    }
}



template <class DataType, class OffsetType, class IndexType>
void COOMatrix<DataType, OffsetType, IndexType>::matvec(const DataType *x, DataType *y, bool Transpose) const
{
    y[0] = x[0];
    if(Transpose) Transpose = false;
    return;
}

template <class DataType, class OffsetType, class IndexType>
std::vector<OffsetType> COOMatrix<DataType, OffsetType, IndexType>::read_offsets(IndexType m, std::istream &is)
{
    std::vector<OffsetType> h(m, 0);
    return h;
}
