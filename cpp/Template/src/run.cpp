#include <MetaNN/data/facilities/continuous_memory.h>
#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/cpu_matrix.h>
#include <MetaNN/data/matrices/matrices.h>

using CPU = MetaNN::DeviceTags::CPU;

int main() {
    MetaNN::ContinousMemory<int, CPU> memory(10);
    MetaNN::Matrix<int, CPU> matrix(3, 3);
    return 0;
}