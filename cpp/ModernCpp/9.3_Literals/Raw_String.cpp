#include <iostream>
#include <string>

int main() {
    std::string str = R"(C:\Path\To\File)"; // string is wrapped in R"()" to
                                            // avoid escape characters
    std::cout << str << std::endl;
    return 0;
}
