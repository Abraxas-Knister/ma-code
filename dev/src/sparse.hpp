#ifndef SPARSE_HPP
#define SPARSE_HPP
#include "config.hpp"

#include <vector>

template <typename T>
struct Sparse_t
{
    std::vector<int> colInd;
    std::vector<int> rowPtr;
    std::vector<T> data;
    template <typename S>
    void xx(const std::vector<S> &vec, std::vector<S> &ret) const;
};

#endif // guard
