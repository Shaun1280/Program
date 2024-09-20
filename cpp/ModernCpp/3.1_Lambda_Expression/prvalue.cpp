#include <type_traits>

class Widget {
  public:
    void doWork() {}
};

Widget getWidget() { return Widget(); }
const Widget getWidgetConst() { return Widget(); }

int main() {
    // auto& w = getWidget(); // Error: cannot bind non-const lvalue reference
    // of type 'Widget&' to an rvalue of type 'Widget'
    const auto& w = getWidget();              // getWidget() is an rvalue
    const Widget&& Widget = getWidgetConst(); // getWidgetConst() is an rvalue

    // Correct. The type of "01234" is const char [6], so it is an lvalue
    const char(&left)[6] = "01234";

    // Assert success. It is a const char [6] indeed. Note that decltype(expr)
    // yields lvalue reference if expr is an lvalue and neither an
    // unparenthesized id-expression nor an unparenthesized class member access
    // expression.
    static_assert(std::is_same_v<decltype("01234"), const char(&)[6]>, "");

    // Error. "01234" is an lvalue, which cannot be referenced by an rvalue
    // reference
    // const char (&&right)[6] = "01234";

    const char* p =
        "01234"; // Correct. "01234" is implicitly converted to const char*
    const char*&& pr = "01234"; // Correct. "01234" is implicitly converted to
                                // const char*, which is an rvalue
    // const char*& pr = "01234";  //  Error. There is no type const char*
    // lvalue
    return 0;
}