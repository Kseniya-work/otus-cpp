/*! \file
    \brief Matrix.
*/

#pragma once

#include <memory>
#include "sparse_matrix.h"

/*! \class Matrix.
    \brief Matrix with defaul values based on sparse matrix.
*/
template<typename T>
class Matrix
{
    std::unique_ptr<SparseMatrix<T>> sparseMatrix_;

public:
    Matrix() { sparseMatrix_ = std::make_unique<SparseMatrix<T>>(); }

    SparseMatrix<T>::iterator begin() { return sparseMatrix_->begin(); }
    SparseMatrix<T>::iterator   end() { return sparseMatrix_->end(); }

    std::size_t size() const
    {
        return sparseMatrix_->size();
    }

    SparseMatrix<T>::Row& operator[](const std::size_t i)
    {
        return (*sparseMatrix_)[i];
    }
};
