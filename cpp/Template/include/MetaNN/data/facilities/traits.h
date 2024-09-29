#ifndef METANN_DATA_FACILITIES_TRAITS_H
#define METANN_DATA_FACILITIES_TRAITS_H

#include <MetaNN/data/facilities/tags.h>
#include <type_traits>

namespace MetaNN {

template <typename TElem, typename TDevice> class Matrix;
template <typename TElem, typename TDevice> class Scalar;
template <typename TElem, typename TDevice, typename TCategory> class Batch;

template <typename TCategory, typename TElem, typename TDevice>
struct PrincipalDataType_;

template <typename TElem, typename TDevice>
struct PrincipalDataType_<CategoryTags::Scalar, TElem, TDevice> {
    using type = Scalar<TElem, TDevice>;
};

template <typename TElem, typename TDevice>
struct PrincipalDataType_<CategoryTags::Matrix, TElem, TDevice> {
    using type = Matrix<TElem, TDevice>;
};

template <typename TElem, typename TDevice>
struct PrincipalDataType_<CategoryTags::BatchMatrix, TElem, TDevice> {
    using type = Batch<TElem, TDevice, CategoryTags::Matrix>;
};

template <typename TCategory, typename TElem, typename TDevice>
using PrincipalDataType =
    typename PrincipalDataType_<TCategory, TElem, TDevice>::type;

/// is scalar
template <typename T> static constexpr bool IsScalar = false;

template <typename T> static constexpr bool IsScalar<const T> = IsScalar<T>;

template <typename T> static constexpr bool IsScalar<T&> = IsScalar<T>;

template <typename T> static constexpr bool IsScalar<T&&> = IsScalar<T>;

/// is matrix
template <typename T> static constexpr bool IsMatrix = false;

template <typename T> static constexpr bool IsMatrix<const T> = IsMatrix<T>;

template <typename T> static constexpr bool IsMatrix<T&> = IsMatrix<T>;

template <typename T> static constexpr bool IsMatrix<T&&> = IsMatrix<T>;

/// is batch scalar
template <typename T> constexpr bool IsBatchScalar = false;

template <typename T>
static constexpr bool IsBatchScalar<const T> = IsBatchScalar<T>;

template <typename T>
static constexpr bool IsBatchScalar<T&> = IsBatchScalar<T>;

template <typename T>
constexpr static bool IsBatchScalar<const T&> = IsBatchScalar<T>;

template <typename T>
constexpr static bool IsBatchScalar<T&&> = IsBatchScalar<T>;

template <typename T>
constexpr static bool IsBatchScalar<const T&&> = IsBatchScalar<T>;

// is batch matrix
template <typename T> constexpr static bool IsBatchMatrix = false;

template <typename T>
constexpr static bool IsBatchMatrix<const T> = IsBatchMatrix<T>;

template <typename T>
constexpr static bool IsBatchMatrix<T&> = IsBatchMatrix<T>;

template <typename T>
constexpr static bool IsBatchMatrix<const T&> = IsBatchMatrix<T>;

template <typename T>
constexpr static bool IsBatchMatrix<T&&> = IsBatchMatrix<T>;

template <typename T>
constexpr bool static IsBatchMatrix<const T&&> = IsBatchMatrix<T>;

// full specialization is not allowed within a non-fully specialized outer
// template.
template <typename T> struct DataCategory_ {
  private:
    template <bool isScalar, bool isMatrix, bool isBatchScalar,
              bool isBatchMatrix, typename TDummy = void>
    struct helper;

    template <typename TDummy>
    struct helper<true, false, false, false, TDummy> {
        using type = CategoryTags::Scalar;
    };

    template <typename TDummy>
    struct helper<false, true, false, false, TDummy> {
        using type = CategoryTags::Matrix;
    };

    template <typename TDummy>
    struct helper<false, false, true, false, TDummy> {
        using type = CategoryTags::BatchScalar;
    };

    template <typename TDummy>
    struct helper<false, false, false, true, TDummy> {
        using type = CategoryTags::BatchMatrix;
    };

  public:
    using type = typename helper<IsScalar<T>, IsMatrix<T>, IsBatchScalar<T>,
                                 IsBatchMatrix<T>>::type;
};

template <typename T> using DataCategory = typename DataCategory_<T>::type;

template <typename T> struct IsIterator_ {
    // SFINAE test
    template <typename R>
    static std::true_type
    test(typename std::iterator_traits<R>::iterator_category*);

    // ... has lowest priority
    template <typename R> static std::false_type test(...);

    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T> static constexpr bool IsIterator = IsIterator_<T>::value;

} // namespace MetaNN

#endif // METANN_DATA_FACILITIES_TRAITS_H