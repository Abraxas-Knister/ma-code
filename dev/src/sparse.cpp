#include "sparse.hpp"

template <typename T>
template <typename S>
void Sparse_t<T>::xx(const std::vector<S> &vec, std::vector<S> &ret) const
{
    const int dim = rowPtr.size() - 1;
    ret.assign(dim,0);
    for (int i=0; i<dim; i++)
    {
        for (int j= rowPtr[i]; j<rowPtr[i+1]; j++)
        {
            ret[i] += data[j]*vec[colInd[j]];
        }
    }
}
