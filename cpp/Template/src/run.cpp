#include <MetaNN/data/facilities/continuous_memory.h>
#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/matrices.h>

using CPU = MetaNN::DeviceTags::CPU;

int main() {
    MetaNN::ContinousMemory<int, CPU> memory(10);
    return 0;
}