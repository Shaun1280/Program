#include <iostream>

#include <MetaNN/data/batch/matrix.h>
#include <MetaNN/data/facilities/continuous_memory.h>
#include <MetaNN/data/facilities/lower_access.h>
#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/cpu_matrix.h>
#include <MetaNN/data/matrices/matrices.h>
#include <MetaNN/data/matrices/one_hot_vector.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/data/matrices/zero_matrix.h>

using CPU = MetaNN::DeviceTags::CPU;
using CategoryTags = MetaNN::CategoryTags;

int main() {
    MetaNN::ContinuousMemory<int, CPU> memory(10);
    MetaNN::Matrix<int, CPU> matrix(3, 3);
    auto la = LowerAccess(matrix);
    auto ptr = la.RawMemory();
    auto trivialMatrix = MetaNN::MakeTrivialMatrix<int, CPU>(3, 3, 1);
    auto zeroMatrix = MetaNN::ZeroMatrix<int, CPU>(3, 3);
    auto oneHotVector = MetaNN::OneHotVector<int, CPU>(3, 1);
    auto batchMatrix = MetaNN::Batch<int, CPU, CategoryTags::Matrix>(3, 3, 3);
    auto x = batchMatrix[2](1, 2);
    std::cout << x << std::endl;
    std::cout << "ok" << std::endl;
    return 0;
}