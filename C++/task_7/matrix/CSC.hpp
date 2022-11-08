#pragma once
#include "SparseMatrixAbstract.hpp"
#include <vector>
#include <istream>
#include <string>
#include <sstream>
#include <algorithm>

template <class DataType, class OffsetType = int, class IndexType = int>
class CSCMatrix : public SparseMatrixAbstract<DataType, OffsetType, IndexType>
{
private:
    IndexType m_rows_number;

    struct Element
    {
        IndexType index;

        DataType value;

        inline bool operator<(const Element &e) const { return index < e.index; }

        inline bool operator==(const Element &e) const { return index == e.index; }
    };

    std::vector<OffsetType> m_offsets;

    std::vector<Element> m_elements;

public:
    CSCMatrix() = default;
    CSCMatrix(IndexType m, IndexType n, std::istream &is);
    void matvec(const DataType *x, DataType *y, bool Transpose) const override;
    ~CSCMatrix() = default;

    std::vector<OffsetType> read_offsets(IndexType m, std::istream &is) override;

    std::vector<Element> read_elements(OffsetType nz, std::istream &is);

    IndexType calc_max_index() const;

    void sort() override;

    inline IndexType column_number() const { return m_offsets.size() - 1; }

    inline IndexType row_number() const { return m_rows_number; }

    CSCMatrix operator+(CSCMatrix &o) const;
};

template <class DataType, class OffsetType, class IndexType>
CSCMatrix<DataType, OffsetType, IndexType>::CSCMatrix(IndexType m, IndexType n, std::istream &is) : m_offsets(read_offsets(m, is)),
                                                                                                    m_elements(read_elements(m_offsets[m], is))
{

    if (calc_max_index() >= n)
    {
        throw std::runtime_error("Matrix has columns with indexes larger than number of columns");
    }
    m_rows_number = n;
    sort();
}

template <class DataType, class OffsetType, class IndexType>
std::vector<OffsetType> CSCMatrix<DataType, OffsetType, IndexType>::read_offsets(IndexType m, std::istream &is)
{
    std::string line;
    std::getline(is, line);
    std::istringstream line_stream(std::move(line));
    std::vector<OffsetType> offsets(m + 1);
    for (auto &offset : offsets)
    {
        line_stream >> offset;
        if (line_stream.fail())
        {
            throw std::runtime_error("Cannot read enough offsets");
        }
    }
    if (OffsetType tmp; (line_stream >> tmp, !line_stream.fail()))
    {
        throw std::runtime_error("To much offsets");
    }
    if (!(line_stream.eof()))
    {
        throw std::runtime_error("Offsets string has some other info");
    }
    if (offsets[0] != 0)
    {
        throw std::runtime_error("First offset is not zero");
    }
    if (!std::is_sorted(offsets.begin(), offsets.end()))
    {
        throw std::runtime_error("Offsets are not sorted");
    }
    return offsets;
}

template <class DataType, class OffsetType, class IndexType>
std::vector<typename CSCMatrix<DataType, OffsetType, IndexType>::Element> CSCMatrix<DataType, OffsetType, IndexType>::read_elements(OffsetType nz, std::istream &is)
{
    std::vector<Element> elements(nz);
    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream(std::move(line));
        for (auto &element : elements)
        {
            line_stream >> element.index;
            if (line_stream.fail())
            {
                throw std::runtime_error("Cannot read enough indexes");
            }
            if (element.index < 0)
            {
                throw std::runtime_error("Negative column number");
            }
        }
        if (IndexType tmp; (line_stream >> tmp, !line_stream.fail()))
        {
            throw std::runtime_error("To much indexes");
        }
        if (!(line_stream.eof()))
        {
            throw std::runtime_error("Indexes string has some other info");
        }
    }
    {
        std::string line;
        std::getline(is, line);
        std::istringstream line_stream(std::move(line));
        for (auto &element : elements)
        {
            line_stream >> element.value;
            if (line_stream.fail())
            {
                throw std::runtime_error("Cannot read enough values");
            }
        }
        if (IndexType tmp; (line_stream >> tmp, !line_stream.fail()))
        {
            throw std::runtime_error("To much values");
        }
        if (!(line_stream.eof()))
        {
            throw std::runtime_error("Values string has some other info");
        }
    }
    return elements;
}

template <class DataType, class OffsetType, class IndexType>
IndexType CSCMatrix<DataType, OffsetType, IndexType>::calc_max_index() const
{
    IndexType max = 0;
    for (auto &element : m_elements)
    {
        max = std::max(element.index, max);
    }
    return max;
}

template <class DataType, class OffsetType, class IndexType>
void CSCMatrix<DataType, OffsetType, IndexType>::sort()
{
    for (IndexType i = 0; i < column_number(); i++)
    {
        auto start = m_elements.begin() + m_offsets[i];
        auto end = m_elements.begin() + m_offsets[i + 1];
        if (!std::is_sorted(start, end))
        {
            std::sort(start, end);
        }
        if (std::unique(start, end) != end)
        {
            throw std::runtime_error("Two elements with the same index in same vector");
        }
    }
}

template <class DataType, class OffsetType, class IndexType>
void CSCMatrix<DataType, OffsetType, IndexType>::matvec(const DataType *x, DataType *y, bool Transpose) const
{
    for (IndexType i = 0; i < column_number(); i++)
    {
        auto start = m_elements.begin() + m_offsets[i];
        auto end = m_elements.begin() + m_offsets[i + 1];
        for (; start < end; ++start)
        {
            const IndexType &j = start->index;
            const DataType &a = start->value;
            if (Transpose)
            {
                y[i] += a * x[j];
            }
            else
            {
                y[j] += a * x[i];
            }
        }
    }
}

template <class DataType, class OffsetType, class IndexType>
CSCMatrix<DataType, OffsetType, IndexType> CSCMatrix<DataType, OffsetType, IndexType>::operator+(CSCMatrix<DataType, OffsetType, IndexType> &o) const
{
    if (column_number() != o.column_number() || row_number() != o.row_number())
    {
        throw std::runtime_error("Can not sum matrices of different sizes");
    }
    CSCMatrix<DataType, OffsetType, IndexType> S;
    S.m_rows_number = m_rows_number;
    S.m_offsets.resize(o.m_offsets.size(), 0);
    for (IndexType i = 0; i < column_number(); i++)
    {
        auto start_t = m_elements.begin() + m_offsets[i];
        auto end_t = m_elements.begin() + m_offsets[i + 1];
        auto start_o = o.m_elements.begin() + o.m_offsets[i];
        auto end_o = o.m_elements.begin() + o.m_offsets[i + 1];
        while (start_t < end_t && start_o < end_o)
        {
            while (start_t < end_t && *start_t < *start_o)
            {
                S.m_elements.push_back(*start_t);
                S.m_offsets[i + 1]++;
                ++start_t;
            }
            while (start_t < end_t && start_o < end_o && *start_t == *start_o)
            {
                Element t = *start_t;
                t.value += start_o->value;
                S.m_elements.push_back(t);
                S.m_offsets[i + 1]++;
                ++start_t;
                ++start_o;
            }
            if (start_t == end_t)
                break;
            while (start_o < end_o && *start_o < *start_t)
            {
                S.m_elements.push_back(*start_o);
                S.m_offsets[i + 1]++;
                ++start_o;
            }
        }
        while (start_t < end_t)
        {
            S.m_elements.push_back(*start_t);
            S.m_offsets[i + 1]++;
            ++start_t;
        }
        while (start_o < end_o)
        {
            S.m_elements.push_back(*start_o);
            S.m_offsets[i + 1]++;
            ++start_o;
        }
        S.m_offsets[i + 1] += S.m_offsets[i];
    }
    return S;
}