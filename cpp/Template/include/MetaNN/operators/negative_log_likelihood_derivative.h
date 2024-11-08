#ifndef METANN_OPERATORS_NEGATIVE_LOG_LIKELIHOOD_DERIVATIVE_H
#define METANN_OPERATORS_NEGATIVE_LOG_LIKELIHOOD_DERIVATIVE_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <>
struct OperCategory_<TernaryOpTags::NegativeLogLikelihoodDerivative,
                     CategoryTags::Scalar, CategoryTags::Matrix,
                     CategoryTags::Matrix> {
    using type = CategoryTags::Matrix;
};

template <>
struct OperCategory_<TernaryOpTags::NegativeLogLikelihoodDerivative,
                     CategoryTags::BatchScalar, CategoryTags::BatchMatrix,
                     CategoryTags::BatchMatrix> {
    using type = CategoryTags::BatchMatrix;
};

} // namespace MetaNN

#endif