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

template <>
class OperOrganizer<TernaryOpTags::NegativeLogLikelihoodDerivative,
                    CategoryTags::Matrix> {
  public:
    template <typename TD1, typename TD2, typename TD3>
    OperOrganizer(const TD1& data1, const TD2& data2, const TD3& data3)
        : m_rowNum(data2.RowNum()), m_colNum(data2.ColNum()) {
        assert(data2.RowNum() == data3.RowNum());
        assert(data2.ColNum() == data3.ColNum());
    }

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
};

template <>
class OperOrganizer<TernaryOpTags::NegativeLogLikelihoodDerivative,
                    CategoryTags::BatchMatrix> {
  public:
    template <typename TD1, typename TD2, typename TD3>
    OperOrganizer(const TD1& data1, const TD2& data2, const TD3& data3)
        : m_rowNum(data2.RowNum()), m_colNum(data2.ColNum()),
          m_batchNum(data2.BatchNum()) {
        assert(data2.RowNum() == data3.RowNum());
        assert(data2.ColNum() == data3.ColNum());
        assert(data2.BatchNum() == data3.BatchNum());
    }

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }
    [[nodiscard]] size_t BatchNum() const noexcept { return m_batchNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
    size_t m_batchNum;
};

template <typename TOp1, typename TOp2, typename TOp3>
struct OperElementType_<TernaryOpTags::NegativeLogLikelihoodDerivative, TOp1,
                        TOp2, TOp3> {
    using type = typename TOp2::ElementType;
};

template <typename TOp1, typename TOp2, typename TOp3>
struct OperDeviceType_<TernaryOpTags::NegativeLogLikelihoodDerivative, TOp1,
                       TOp2, TOp3> {
    using type = typename TOp2::DeviceType;
};

template <typename TGrad, typename TP1, typename TP2>
struct OperNegativeLogLikelihoodDerivative_ {
    // valid check
  private:
    using rawGrad = std::decay_t<TGrad>;
    using rawM1 = std::decay_t<TP1>;
    using rawM2 = std::decay_t<TP2>;

  public:
    static constexpr bool valid =
        (IsScalar<rawGrad> && IsMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsBatchScalar<rawGrad> && IsBatchMatrix<rawM1> &&
         IsBatchMatrix<rawM2>);

  public:
    static auto Eval(TGrad&& p_grad, TP1&& p_m1, TP2&& p_m2) {
        static_assert(std::is_same_v<typename rawM1::ElementType,
                                     typename rawM2::ElementType>,
                      "Matrices with different element types cannot do "
                      "NegativeLogLikelihood derivative directly");
        static_assert(std::is_same_v<typename rawM1::DeviceType,
                                     typename rawM2::DeviceType>,
                      "Matrices with different device types cannot do "
                      "NegativeLogLikelihood derivative directly");

        using ResType =
            TernaryOp<TernaryOpTags::NegativeLogLikelihoodDerivative, rawGrad,
                      rawM1, rawM2>;
        return ResType(std::forward<TGrad>(p_grad), std::forward<TP1>(p_m1),
                       std::forward<TP2>(p_m2));
    }
};

template <typename TGrad, typename TP1, typename TP2,
          std::enable_if_t<
              OperNegativeLogLikelihoodDerivative_<TGrad, TP1, TP2>::valid,
              bool> = true>
auto NegativeLogLikelihoodDerivative(TGrad&& p_grad, TP1&& p_tar, TP2&& p_pre) {
    return OperNegativeLogLikelihoodDerivative_<TGrad, TP1, TP2>::Eval(
        std::forward<TGrad>(p_grad), std::forward<TP1>(p_tar),
        std::forward<TP2>(p_pre));
}

} // namespace MetaNN

#endif