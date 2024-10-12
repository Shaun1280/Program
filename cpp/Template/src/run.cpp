#include <iostream>

#include <MetaNN/data/batch/array.h>
#include <MetaNN/data/batch/duplicate.h>
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
#include <MetaNN/operators/facilities/category_cal.h>
#include <MetaNN/operators/facilities/organizer.h>
#include <MetaNN/operators/facilities/tags.h>

using CPU = MetaNN::DeviceTags::CPU;
using CategoryTags = MetaNN::CategoryTags;

using ADD = MetaNN::BinaryOpTags::Add;
using OperCate = MetaNN::OperCateCal<ADD, MetaNN::Matrix<int, CPU>,
                                     MetaNN::TrivialMatrix<int, CPU>>;

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

    auto array = MetaNN::Array<MetaNN::Matrix<int, CPU>>(3, 3);

    std::vector<MetaNN::Matrix<int, CPU>> vec;
    vec.push_back(matrix);
    MetaNN::Array<MetaNN::Matrix<int, CPU>> array2(vec.begin(), vec.end());
    auto array3 = MetaNN::MakeArray(vec.begin(), vec.end());
    auto array4 = MetaNN::Array<MetaNN::Scalar<int, CPU>>(3, 3);

    MetaNN::ZeroMatrix<int, CPU> mat(100, 200);
    auto batch_matrix0 = MetaNN::MakeDuplicate(10, mat);

    auto batch_matrix1 =
        MetaNN::MakeDuplicate<MetaNN::ZeroMatrix<int, CPU>>(10, 100, 200);

    MetaNN::Scalar<int, CPU> scalar(0);
    auto batch_scalar0 = MetaNN::MakeDuplicate(10, scalar);

    auto organizer =
        MetaNN::OperOrganizer<ADD, CategoryTags::Matrix>(matrix, matrix);

    std::cout << "ok" << std::endl;
    return 0;
}