#include <MetaNN/data/facilities/continuous_memory.h>
#include <MetaNN/data/facilities/lower_access.h>
#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/cpu_matrix.h>
#include <MetaNN/data/matrices/matrices.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/data/matrices/zero_matrix.h>

using CPU = MetaNN::DeviceTags::CPU;

int main() {
    MetaNN::ContinousMemory<int, CPU> memory(10);
    MetaNN::Matrix<int, CPU> matrix(3, 3);
    auto la = LowerAccess(matrix);
    auto ptr = la.RawMemory();
    auto trivialMatrix = MetaNN::MakeTrivialMatrix<int, CPU>(3, 3, 1);
    auto zeroMatrix = MetaNN::ZeroMatrix<int, CPU>(3, 3);
    return 0;
}