#ifndef METANN_OPERATORS_FACILITIES_TRAITS_H
#define METANN_OPERATORS_FACILITIES_TRAITS_H

namespace MetaNN {

template <typename TOpTag, typename TOp1, typename... TOperands>
struct OperElementType_ {
    using type = typename TOp1::ElementType;
};

template <typename TOpTag, typename TOp1, typename... TOperands>
struct OperDeviceType_ {
    using type = typename TOp1::DeviceType;
};

} // namespace MetaNN

#endif // METANN_OPERATORS_FACILITIES_TRAITS_H