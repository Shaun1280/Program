#include <bits/stdc++.h>

template <typename T> struct Fun_ {
    using type = T;
};

template <> struct Fun_<int> {
    using type = unsigned int;
};

template <> struct Fun_<long> {
    using type = unsigned long long;
};

template <typename T> using Fun = typename Fun_<T>::type;

Fun_<int>::type Fun_type = 0;

Fun<int> i = 0;

template <typename T> struct Fun_2 {};

Fun_2<int> f;

template <int a> constexpr int fun = a + 1;

auto fun3 = fun<3>;

// type traits
std::remove_reference<int&>::type h1 = 3;
std::remove_reference_t<int&> h2 = 3;

// 1.1.6
template <int a, int b> struct Add_ {
    constexpr static int value = a + b;
};

template <int a, int b> constexpr int Add = a + b;

constexpr int x1 = Add_<2, 3>::value;
constexpr int x2 = Add<2, 3>;

// 1.2.1
template <template <typename> class T1, typename T2> struct Fun1_2_1_ {
    using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun1_2_1 = typename Fun1_2_1_<T1, T2>::type;

Fun1_2_1<std::remove_reference, int&> h1_2_1 = 3;

// 1.2.2
template <bool AddOrRemoveRef> struct Fun1_2_2_;

template <> struct Fun1_2_2_<true> {
    template <typename T> using type = std::add_lvalue_reference<T>;
};

template <> struct Fun1_2_2_<false> {
    template <typename T> using type = std::remove_reference<T>;
};

// use 'template' keyword to treat 'type' as a dependent template name.
// template keyword before type<T> is used to inform the compiler that type is a
// template member of Fun1_2_2_. this is still a template, not a concrete type.
template <typename T, bool AddOrRemove>
using Fun1_2_2 = typename Fun1_2_2_<AddOrRemove>::template type<T>;
// Fun1_2_2 is not just a type, but rather a template that produces a type.

// When you use typename Fun1_2_2<T, false>::type,
// you're actually applying this template to the type T,
// which gives you the final, concrete type.
template <typename T> using Res = typename Fun1_2_2<T, false>::type;

Res<int&> h = 3;

// 1.2.3 declare is enough
template <int... Vals> struct IntContainer;
template <bool... Vals> struct BoolContainer;
template <typename... Types> struct TypeContainer;
// c++17 class -> typename
template <template <typename> class... T> struct TemplateContainer;
template <template <typename...> class... T> struct TemplateTypeContainer;
// c++17
template <auto... Vals> struct Container;

// 1.3.1
template <typename T> struct RemoveReferenceConst_ {
  private:
    using inner_type = typename std::remove_reference<T>::type;

  public:
    using type = typename std::remove_const<inner_type>::type;
};

template <typename T>
using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;

RemoveReferenceConst<const int&> removeRefConst = 3;

// 1.3.2
namespace _std {
template <bool B, typename T, typename F> struct conditional {
    using type = T;
};

template <typename T, typename F> struct conditional<false, T, F> {
    using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;
}; // namespace _std

// not frequently used
_std::conditional<true, int, float>::type condition_x = 3;
_std::conditional<false, int, std::string>::type condition_x2 = "21312";
_std::conditional_t<false, int, std::string> condition_x3 = "21312";

struct A;
struct B;

template <typename T> struct Fun1_3_2_ {
    constexpr static size_t value = 0;
};

template <> struct Fun1_3_2_<A> {
    constexpr static size_t value = 1;
};

template <> struct Fun1_3_2_<B> {
    constexpr static size_t value = 2;
};

constexpr size_t h1_3_2 = Fun1_3_2_<B>::value;

// c++ 14
template <typename T> constexpr size_t Fun1_3_2_14 = 0;

template <> constexpr size_t Fun1_3_2_14<A> = 1;

template <> constexpr size_t Fun1_3_2_14<B> = 2;

constexpr size_t h1_3_2_14 = Fun1_3_2_14<A>;

// wrapper, full specialization is not allowed in non-full specialization
template <typename TW> struct Wrapper {
    template <typename T, typename TDummy = void> struct Fun_ {
        constexpr static size_t value = 0;
    };

    template <typename TDummy> // partial specialization
    struct Fun_<int, TDummy> {
        constexpr static size_t value = 1;
    };
};

constexpr size_t wrapperValue = Wrapper<int>::Fun_<int>::value;

namespace _std2 {
template <bool B, typename T = void> struct enable_if {};

template <typename T> struct enable_if<true, T> {
    using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;
}; // namespace _std2

// If _std2::enable_if_t<IsFeedBackOut, bool> is a valid type (which it will be
// when IsFeedBackOut is true), then create a non-type template parameter of
// this type with a default value of true."
template <bool IsFeedBackOut, typename T,
          _std2::enable_if_t<IsFeedBackOut, bool> = true>
constexpr decltype(auto) FeedBackOut_(T&& value) {
    return std::forward<T>(value);
};

template <bool IsFeedBackOut, typename T,
          _std2::enable_if_t<!IsFeedBackOut, bool> = true>
constexpr decltype(auto) FeedBackOut_(T&& value) {
    return std::forward<T>(value);
};

// Substitution Failure Is Not An Error (SFINAE)
constexpr auto t = FeedBackOut_<true>(8);

template <bool Check, std::enable_if_t<Check, bool> = true> auto funCk() {
    return static_cast<int>(0);
}

template <bool Check, std::enable_if_t<!Check, bool> = true> auto funCk() {
    return std::string("");
}

template <bool Check> auto wrapCk() { return funCk<Check>(); }

auto wrapCkVar = wrapCk<false>();

// c++17
template <bool Check> auto funCk2() {
    if constexpr (Check) {
        return static_cast<int>(0);
    } else {
        return std::string("");
    }
}

auto funCk2Var = funCk2<true>();

// 1.3.3
template <size_t Input>
constexpr size_t OnesCount = (Input & 1) + OnesCount<(Input >> 1)>;

template <> constexpr size_t OnesCount<0> = 0;

constexpr size_t res = OnesCount<45>; // 32 + 8 + 4 + 1

// Base case
template <size_t... Inputs> constexpr size_t Accumulate = 0;

// Recursive case
template <size_t CurInput, size_t... Inputs>
constexpr size_t Accumulate<CurInput, Inputs...> =
    CurInput + Accumulate<Inputs...>;

// Usage
constexpr size_t resAccu = Accumulate<1, 2, 3, 4, 5>;

// c++17 fold expression
template <size_t... values> constexpr auto funcValues() {
    return (0 + ... + values);
}

constexpr auto resValues = funcValues<1, 2, 3, 4, 5, 6>();

// 1.3.4
template <size_t A> struct Wrap2_ {
    template <size_t ID, typename TDummy = void> struct imp {
        constexpr static size_t value = ID + imp<ID - 1>::value;
    };

    template <typename TDummy> // partial specialization
    struct imp<0, TDummy> {
        constexpr static size_t value = 0;
    };

    template <size_t ID> constexpr static size_t value = imp<ID + A>::value;
};

auto wrap2Value = Wrap2_<3>::value<2>;

// this will lead to less instances
namespace stdWrap2 {
template <size_t ID> struct imp {
    constexpr static size_t value = ID + imp<ID - 1>::value;
};

template <> // partial specialization
struct imp<0> {
    constexpr static size_t value = 0;
};

template <size_t A> struct Wrap2_ {
    template <size_t ID> constexpr static size_t value = imp<ID + A>::value;
};
} // namespace stdWrap2

auto wrap2Value2 = stdWrap2::Wrap2_<3>::value<2>;

// 1.3.5
template <size_t N> constexpr bool is_odd = ((N & 1) == 1);

template <bool Cur, typename TNext> constexpr static bool AndValue = false;

template <typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template <size_t N> struct AllOdd_ {
    constexpr static bool is_cur_odd = is_odd<N>;
    // if is_cur_odd is false, then do not need to calc AllOdd<N - 1>, i.e
    // return false if is_cur_odd is true, then go on checking AllOdd<N - 1>
    constexpr static bool value = AndValue<is_cur_odd, AllOdd_<N - 1>>;
};

// 1.4 奇异递归模板式 Curiously Recurring Template Pattern, CRTP
// CRTP virtual template
template <typename D> struct Base {
    template <typename TI> void Fun(const TI& input) {
        D* ptr = static_cast<D*>(this);
        ptr->Imp(input);
    }

    static void FunStatic() { D::ImpStatic(); }
};

struct Derived : public Base<Derived> {
    template <typename TI> void Imp(const TI& input) {
        std::cout << input << std::endl;
    }

    static void ImpStatic() {
        std::cout << "Reimplementing static function" << std::endl;
    }
};

struct Derived2 : public Base<Derived2> {
    template <typename TI> void Imp(const TI& input) {
        std::cout << input << " + 2 " << std::endl;
    }
};

// 2.2.1 VarTypeDict
namespace NSVarTypeDict {
struct NullParameter {};

template <size_t N, template <typename...> class TCont, typename... T>
struct Create_ {
    using type = typename Create_<N - 1, TCont, NullParameter, T...>::type;
};

template <template <typename...> class TCont, typename... T>
struct Create_<0, TCont, T...> {
    using type = TCont<T...>;
};
} // namespace NSVarTypeDict

namespace NSVarTypeDictLOG {
struct NullParameter;

template <size_t N, typename TCont, typename... T> struct Create_;

template <size_t N, template <typename...> class TCont, typename... T,
          typename... TTmp>
struct Create_<N, TCont<T...>, TTmp...> {
    using type = std::conditional_t<
        (N & 1),
        typename Create_<(N >> 1), TCont<T..., TTmp...>, TTmp...,
                         TTmp...>::type,
        typename Create_<(N >> 1), TCont<T...>, TTmp..., TTmp...>::type>;
};

template <template <typename...> class TCont, typename... T, typename... TTmp>
struct Create_<0, TCont<T...>, TTmp...> {
    using type = TCont<T...>;
};
} // namespace NSVarTypeDictLOG

namespace NSMultiTypeDict {
template <typename TTag, typename... TParameters>
constexpr size_t Tag2ID = static_cast<size_t>(-1);

template <typename TTag, typename... TParameters>
constexpr size_t Tag2ID<TTag, TTag, TParameters...> = 0;

template <typename TTag, typename TCur, typename... TParameters>
constexpr size_t Tag2ID<TTag, TCur, TParameters...> =
    Tag2ID<TTag, TParameters...> == static_cast<size_t>(-1)
        ? static_cast<size_t>(-1)
        : Tag2ID<TTag, TParameters...> + 1;

template <typename TVal, size_t N, size_t M, typename TProcessedTypes,
          typename... TRemainTypes>
struct NewTupleType_;

template <typename TVal, size_t N, size_t M, template <typename...> class TCont,
          typename... TModifiedTypes, typename TCurType,
          typename... TRemainTypes>
struct NewTupleType_<TVal, N, M, TCont<TModifiedTypes...>, TCurType,
                     TRemainTypes...> {
    using type = typename NewTupleType_<TVal, N, M + 1,
                                        TCont<TModifiedTypes..., TCurType>,
                                        TRemainTypes...>::type;
};

template <typename TVal, size_t N, template <typename...> class TCont,
          typename... TModifiedTypes, typename TCurType,
          typename... TRemainTypes>
struct NewTupleType_<TVal, N, N, TCont<TModifiedTypes...>, TCurType,
                     TRemainTypes...> {
    using type = TCont<TModifiedTypes..., TVal, TRemainTypes...>;
};

template <typename TVal, size_t TagPos, typename TCont, typename... RemainTypes>
using NewTupleType =
    typename NewTupleType_<TVal, TagPos, 0, TCont, RemainTypes...>::type;
} // namespace NSMultiTypeDict

template <typename... TParameters> struct VarTypeDict {
    template <typename... TTypes> struct Values {
        Values() = default;

        Values(std::shared_ptr<void> (&&input)[sizeof...(TTypes)]) {
            for (size_t i = 0; i < sizeof...(TTypes); ++i) {
                m_tuple[i] = std::move(input[i]);
            }
        }

        template <typename TTag, typename TVal> auto Set(TVal&& val) && {
            using namespace NSMultiTypeDict;

            constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;

            using rawVal = std::decay_t<TVal>;
            rawVal* tmp = new rawVal{std::forward<TVal>(val)};
            m_tuple[TagPos] = std::shared_ptr<void>(tmp, [](void* ptr) {
                rawVal* nptr = static_cast<rawVal*>(ptr);
                delete nptr;
            });

            using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;
            return new_type{std::move(m_tuple)};
        }

        template <typename TTag> const auto& Get() const {
            using namespace NSMultiTypeDict;

            constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;

            using ReturnType =
                std::tuple_element_t<TagPos, std::tuple<TTypes...>>;

            return *static_cast<const ReturnType*>(m_tuple[TagPos].get());
        }

      private:
        std::shared_ptr<void> m_tuple[sizeof...(TTypes)];
    };

    static auto Create() {
        // using namespace NSVarTypeDict;
        // using type = typename Create_<sizeof...(TParameters), Values>::type;
        using namespace NSVarTypeDictLOG;
        using type = typename Create_<sizeof...(TParameters), Values<>,
                                      NullParameter>::type;
        return type{};
    }
};

struct A;
struct B;
struct Weight;
struct Weight2;
using FParams = VarTypeDict<A, B, Weight>;

template <typename TIn> float fun2_2_1(const TIn& in) {
    auto a = in.template Get<A>();
    auto b = in.template Get<B>();
    auto weight = in.template Get<Weight>();
    return a * weight + b * (1.0f - weight);
}

// 2.3.1 Policy
namespace policy {
struct AccPolicy {
    using MajorClass = AccPolicy;

    struct AccuTypeCategory {
        struct Add;
        struct Mul;
    };
    using Accu = AccuTypeCategory::Add;

    struct IsAveValueCategory;
    static constexpr bool IsAve = false;

    struct ValueTypeCategory;
    using Value = float;
};

#define TypePolicyObj(PolicyName, Ma, Mi, Val)                                 \
    struct PolicyName : virtual public Ma {                                    \
        using MinorClass = Ma::Mi##TypeCategory;                               \
        using Mi = Ma::Mi##TypeCategory::Val;                                  \
    }

#define ValueTypePolicyObj(PolicyName, Ma, Mi, Val)                            \
    struct PolicyName : virtual public Ma {                                    \
        using MinorClass = Ma::Mi##TypeCategory;                               \
        using Mi = Val;                                                        \
    }

#define ValuePolicyObj(PolicyName, Ma, Mi, Val)                                \
    struct PolicyName : virtual public Ma {                                    \
        using MinorClass = Ma::Mi##ValueCategory;                              \
        static constexpr bool Mi = Val;                                        \
    }

#define TypePolicyTemplate(PolicyName, Ma, Mi)                                 \
    template <typename Val> struct PolicyName : virtual public Ma {            \
        using MinorClass = Ma::Mi##TypeCategory;                               \
        using Mi = Ma::Mi##TypeCategory::Val;                                  \
    }

#define ValueTypePolicyTemplate(PolicyName, Ma, Mi)                            \
    template <typename Val> struct PolicyName : virtual public Ma {            \
        using MinorClass = Ma::Mi##TypeCategory;                               \
        using Mi = Val;                                                        \
    }

#define ValuePolicyTemplate(PolicyName, Ma, Mi)                                \
    template <bool Val> struct PolicyName : virtual public Ma {                \
        using MinorClass = Ma::Mi##ValueCategory;                              \
        static constexpr bool Mi = Val;                                        \
    }

TypePolicyObj(PAddAccu, AccPolicy, Accu, Add);
TypePolicyObj(PMulAccu, AccPolicy, Accu, Mul);
ValueTypePolicyObj(PDoubleValue, AccPolicy, Value, double);
ValuePolicyObj(PAve, AccPolicy, IsAve, true);
ValuePolicyObj(PNoAve, AccPolicy, IsAve, false);
ValueTypePolicyTemplate(PValueTypeIs, AccPolicy, Value);
ValuePolicyTemplate(PAvePolicyIs, AccPolicy, IsAve);

template <bool Cur, typename TNext> static constexpr bool AndValue = false;

template <typename TNext>
static constexpr bool AndValue<true, TNext> = TNext::value;

template <typename... TPolicies> struct PolicyContainer {};

namespace NSPolicySelect {
template <typename TPolicyCont> struct MinorCheck_ {
    static constexpr bool value = true;
};

template <typename TMinorClass, typename... TRemainPolicies>
struct MinorDedup_ {
    static constexpr bool value = true;
};

template <typename TMinorClass, typename TCurPolicy,
          typename... TRemainPolicies>
struct MinorDedup_<TMinorClass, TCurPolicy, TRemainPolicies...> {
    using CurMinorClass = typename TCurPolicy::MinorClass;
    // check if the current policy has the different minor class as the current
    // minor class
    static constexpr bool cur_check =
        !std::is_same_v<TMinorClass, CurMinorClass>;
    static constexpr bool value =
        AndValue<cur_check, MinorDedup_<TMinorClass, TRemainPolicies...>>;
};

template <typename TCurPolicy, typename... TRemainPolicies>
struct MinorCheck_<PolicyContainer<TCurPolicy, TRemainPolicies...>> {
    // compare current policy minor class with the remaining policies
    static constexpr bool cur_check =
        MinorDedup_<typename TCurPolicy::MinorClass, TRemainPolicies...>::value;
    // MinorCheck_<PolicyContainer<TRemainPolicies...> checks if the remaining
    // policies have the same minor class
    static constexpr bool value =
        AndValue<cur_check, MinorCheck_<PolicyContainer<TRemainPolicies...>>>;
};

template <typename TPolicyContainer, typename TMajorClass,
          typename... TPolicies>
struct MajorFilter_;

template <template <typename...> class TPolicyContainer, typename TMajorClass,
          typename... TFilteredPolicy, typename TCurPolicy,
          typename... TRemainingPolicies>
struct MajorFilter_<TPolicyContainer<TFilteredPolicy...>, TMajorClass,
                    TCurPolicy, TRemainingPolicies...> {
    using type = std::conditional_t<
        std::is_same_v<typename TCurPolicy::MajorClass, TMajorClass>,
        typename MajorFilter_<TPolicyContainer<TFilteredPolicy..., TCurPolicy>,
                              TMajorClass, TRemainingPolicies...>::type,
        typename MajorFilter_<TPolicyContainer<TFilteredPolicy...>, TMajorClass,
                              TRemainingPolicies...>::type>;
};

// Specialization for empty policy list (termination case)
template <template <typename...> class TPolicyContainer, typename TMajorClass,
          typename... TFilteredPolicy>
struct MajorFilter_<TPolicyContainer<TFilteredPolicy...>, TMajorClass> {
    using type = TPolicyContainer<TFilteredPolicy...>;
};

template <typename TPolicyContainer> struct PolicySelRes;

template <typename TPolicy>
struct PolicySelRes<PolicyContainer<TPolicy>> : public TPolicy {};

template <typename TCurPolicy, typename... TRemainPolicies>
struct PolicySelRes<PolicyContainer<TCurPolicy, TRemainPolicies...>>
    : public TCurPolicy,
      public PolicySelRes<PolicyContainer<TRemainPolicies...>> {};

template <typename TPolicyCont> static constexpr bool IsArrayEmpty = false;

template <typename... TPolicies>
static constexpr bool IsArrayEmpty<PolicyContainer<TPolicies...>> =
    sizeof...(TPolicies) == 0;

template <typename TMajorClass, typename TPolicyContainter> struct Selector_;

// specialization so that the second template parameter can only be a
// PolicyContainer
template <typename TMajorClass, typename... TPolicies>
struct Selector_<TMajorClass, PolicyContainer<TPolicies...>> {
    // create a new policy container with the TMajorClass Only
    using TMF = typename MajorFilter_<PolicyContainer<>, TMajorClass,
                                      TPolicies...>::type;

    // check if there are no two policies with the same minor class
    static_assert(MinorCheck_<TMF>::value, "Minor policy conflict");

    using type =
        std::conditional_t<IsArrayEmpty<TMF>, TMajorClass, PolicySelRes<TMF>>;
};
}; // namespace NSPolicySelect

template <typename MajorClass, typename TPolicyContainter>
using PolicySelect =
    typename NSPolicySelect::Selector_<MajorClass, TPolicyContainter>::type;

template <typename AccuType> static constexpr bool DependencyFalse = false;

// struct Add;
// // default usage Accumulator<> ...
// template <typename TAccuType = Add, bool DoAverage = false, typename
// ValueType = float> struct Accumulator2 {};

// more flexible:
// Accumulator2<PValueTypeIs<float>,PAccuTypeIs<Add>,PAveValueIs<false>>

// a template that receives a list of policies, and then uses it to eval the
// result.
template <typename... TPolicies> struct Accumulator {
    using TPolicyRes =
        PolicySelect<AccPolicy,
                     PolicyContainer<TPolicies...>>; // policy select result

    using ValueType = typename TPolicyRes::Value; // float;
    using AccuType =
        typename TPolicyRes::Accu; // AccPolicy::AccuTypeCategory::Add;
    static constexpr bool IsAve = TPolicyRes::IsAve; // false;

  public:
    template <typename TIn> static auto Eval(const TIn& in) {
        if constexpr (std::is_same_v<AccuType,
                                     AccPolicy::AccuTypeCategory::Add>) {
            ValueType count = 0, res = 0;
            for (const auto& val : in) {
                res += val;
                count += 1;
            }
            if constexpr (IsAve) {
                return res / count;
            } else {
                return res;
            }
        } else if constexpr (std::is_same_v<AccuType,
                                            AccPolicy::AccuTypeCategory::Mul>) {
            ValueType count = 0, res = 1;
            for (const auto& val : in) {
                res *= val;
                count += 1;
            }
            if constexpr (IsAve) {
                return pow(res, 1.0 / count);
            } else {
                return res;
            }
        } else {
            static_assert(DependencyFalse<AccuType>, "Unkown AccuType");
            return ValueType(0);
        }
    }
};

void test() {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    std::cout << Accumulator<>::Eval(a) << std::endl;
    std::cout << Accumulator<PAddAccu>::Eval(a) << std::endl;
    std::cout << Accumulator<PAddAccu, PAvePolicyIs<true>>::Eval(a)
              << std::endl;
    std::cout << Accumulator<PMulAccu>::Eval(a) << std::endl;
    std::cout << Accumulator<PMulAccu, PAve>::Eval(a) << std::endl;
    // // should fail to compile
    // // std::cout << policy::Accumulator2<PMulAccu, PAddAccu>::Eval(a) <<
    // std::endl;
    std::cout << Accumulator<PAve, PMulAccu>::Eval(a) << std::endl;
    std::cout << Accumulator<PAve, PMulAccu, PValueTypeIs<double>>::Eval(a)
              << std::endl;
    std::cout << Accumulator<PAve, PMulAccu, PDoubleValue>::Eval(a)
              << std::endl;
}
} // namespace policy

template <typename TData> struct LowerAccessImpl;

template <typename TData> auto LowerAccess(TData&& data) {
    using RawType = std::remove_cvref_t<TData>;
    return LowerAccessImpl<RawType>(std::forward<TData>(data));
}

int main() {
    std::cout << res << std::endl;
    std::cout << resValues << std::endl;
    std::cout << wrap2Value << std::endl;
    std::cout << wrap2Value2 << std::endl;
    Derived d;
    d.Fun("test"); // allow use to override functions
    Derived::FunStatic();
    d.FunStatic();
    Derived2 d2;
    d2.Fun("test");

    // 1.2.2 VarTypeDict
    std::cout << fun2_2_1(
                     FParams::Create().Set<A>(1.3f).Set<B>(2.4f).Set<Weight>(
                         0.1f))
              << std::endl;

    // 2.3.1 Policy
    policy::test();
    return 0;
}