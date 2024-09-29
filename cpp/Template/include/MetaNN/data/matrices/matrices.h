#ifndef METANN_DATA_MATRICES_MATRICES_H
#define METANN_DATA_MATRICES_MATRICES_H

#include <MetaNN/data/facilities/traits.h>

namespace MetaNN {

// matrices
template <typename TElement, typename TDevice> class Matrix;

template <typename TElement, typename TDevice>
constexpr static bool IsMatrix<Matrix<TElement, TDevice>> = true;

} // namespace MetaNN

#endif // METANN_DATA_MATRICES_MATRICES_H