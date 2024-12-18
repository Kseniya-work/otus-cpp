/*! \file
    \brief Matrix.

*/

#pragma once

#include <map>
#include <tuple>

int version();

/*! \class SparseMatrix.
    \brief Sparse matrix.
*/
template<typename T>
class SparseMatrix
{
public:
    class Row
    {
        using col_iterator = typename std::map<std::size_t, T>::iterator;
        std::map<std::size_t, T> row_;

    public:
        Row() : row_() {}
        T& operator[](const std::size_t j) { return row_[j];}

        col_iterator begin() { return row_.begin(); }
        col_iterator   end() { return row_.end(); }
    };

private:
    std::map<std::size_t, Row> rows_;

public:
    class iterator : public std::iterator<
                                std::bidirectional_iterator_tag, // iterator_category
                                T,               // value_type
                                std::ptrdiff_t,                  // difference_type
                                T*,        // pointer
                                T&               // reference
                            >
    {
        using row_iterator = typename std::map<std::size_t, Row>::iterator;
        using col_iterator = typename std::map<std::size_t, T>::iterator;

        row_iterator rowIt_;
        col_iterator colIt_;
        row_iterator rowEndIt_;

    public:
        explicit iterator(const row_iterator rowIt, const row_iterator rowEndIt)
        : rowIt_(rowIt)
        , colIt_(rowIt->second.begin())
        , rowEndIt_(rowEndIt)
        {}

        // Prefix increment
        iterator& operator++()
        {
            if (++colIt_ != rowIt_->second.end())
            {
                return *this;
            }
            else if (++rowIt_ != rowEndIt_)
            {
                colIt_ = rowIt_->second.begin();
                return *this;
            }
            rowIt_ = rowEndIt_;
            colIt_ = rowIt_->second.begin();
            return *this;
        }
        // Postfix increment
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(iterator other) const { return (rowIt_ == other.rowIt_) && (colIt_ == other.colIt_); }
        bool operator!=(iterator other) const { return !(*this == other); }
        std::tuple<std::size_t, std::size_t, T> operator*() const { return std::make_tuple(rowIt_->first, colIt_->first, colIt_->second); }
    };
    iterator begin() { return iterator(rows_.begin(), rows_.end()); }
    iterator   end() { return iterator(rows_.end(), rows_.end()); }

    SparseMatrix() : rows_() {}

    std::size_t size() const
    {
        return rows_.size();
    }

    Row& operator[](const std::size_t i)
    {
        return rows_[i];
    }
};

/*! \class InfiniteMatrix.
    \brief .
*/
class InfiniteMatrix
{

};
