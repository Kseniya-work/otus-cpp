/*! \file
    \brief SparseMatrix.
*/

#pragma once

#include <map>
#include <numeric>
#include <tuple>

/*! \class SparseMatrix.
    \brief Sparse matrix.
*/
template<typename T, T DefaultValue = 0>
class SparseMatrix
{
    /*! Sparse row in sparse matrix. */
    class Row
    {
        using col_iterator = typename std::map<std::size_t, T>::iterator;
        std::map<std::size_t, T> cols_;

    public:
        Row() : cols_() {}
        col_iterator begin() { return cols_.begin(); }
        col_iterator   end() { return cols_.end(); }
        std::size_t   size() const { return cols_.size(); }

        /*! Proxy class for returning the default value 
            for an unoccupied element whose value has never been assigned.
        */
        class RowProxy
        {
            Row& row_;
            std::size_t index_;

        public:
            RowProxy(Row& row, const std::size_t index)
            : row_(row), index_(index)
            {}

            T& operator=(T value) // in cases as: matrix[i][j] = value;
            {
                return row_.cols_[index_] = value;
            }

            operator T() const // in cases as: auto val = matrix[i][j];
            {
                return row_.cols_.find(index_) != row_.end() ? row_.cols_[index_] : DefaultValue;
            }
        };

        RowProxy operator[](const std::size_t j)
        {
            return RowProxy(*this, j);
        }
    };

    using row_iterator = typename std::map<std::size_t, Row>::iterator;
    std::map<std::size_t, Row> rows_;

    /*! Matrix proxy class for acsess to rows. */
    class MatrixProxy
    {
        SparseMatrix& matrix_;
        std::size_t i_;

    public:
        MatrixProxy(SparseMatrix& matrix, const std::size_t i)
        : matrix_(matrix), i_(i)
        {}

        auto operator[](const std::size_t j)->decltype(matrix_.rows_[i_][j])
        {
            return matrix_.rows_[i_][j];
        }
    };

    class iterator : public std::iterator<
                                std::bidirectional_iterator_tag, // iterator_category
                                T,                               // value_type
                                std::ptrdiff_t,                  // difference_type
                                T*,                              // pointer
                                T&                               // reference
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

        bool operator==(const iterator other) const
        {
            return (rowIt_ == other.rowIt_) && (colIt_ == other.colIt_);
        }
        bool operator!=(const iterator other) const { return !(*this == other); }
        std::tuple<std::size_t, std::size_t, T> operator*() const
        {
            return std::make_tuple(rowIt_->first, colIt_->first, colIt_->second);
        }
    };

public:
    SparseMatrix() : rows_() {}

    iterator begin() { return iterator(rows_.begin(), rows_.end()); }
    iterator   end() { return iterator(rows_.end(), rows_.end()); }

    MatrixProxy operator[](const std::size_t i)
    {
        return MatrixProxy(*this, i);
    }

    std::size_t size() const
    {
        return std::accumulate(rows_.cbegin(), rows_.cend(), 0, [](int count, const auto row) {
                return count + row.second.size();
            }
        );
    }
};

