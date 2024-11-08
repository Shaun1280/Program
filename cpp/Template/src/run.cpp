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
#include <MetaNN/operators/abs.h>
#include <MetaNN/operators/add.h>
#include <MetaNN/operators/collapse.h>
#include <MetaNN/operators/divide.h>
#include <MetaNN/operators/dot.h>
#include <MetaNN/operators/element_mul.h>
#include <MetaNN/operators/facilities/category_cal.h>
#include <MetaNN/operators/facilities/organizer.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/negative_log_likelihood.h>
#include <MetaNN/operators/operators.h>
#include <MetaNN/operators/sigmoid.h>
#include <MetaNN/operators/sigmoid_derivative.h>
#include <MetaNN/operators/sign.h>
#include <MetaNN/operators/softmax.h>
#include <MetaNN/operators/softmax_derivative.h>
#include <MetaNN/operators/tanh.h>
#include <MetaNN/operators/transpose.h>

using CPU = MetaNN::DeviceTags::CPU;
using CategoryTags = MetaNN::CategoryTags;

using ADD = MetaNN::BinaryOpTags::Add;
using Sigmoid = MetaNN::UnaryOpTags::Sigmoid;
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

    auto organizer_sigmoid =
        MetaNN::OperOrganizer<Sigmoid, CategoryTags::Matrix>(matrix);

    std::cout << MetaNN::IsMatrix<decltype(matrix)> << std::endl;
    auto sigmoid = MetaNN::Sigmoid(matrix);
    auto sigmoid2 = MetaNN::Sigmoid(batch_matrix1);

    auto add = matrix + matrix;
    auto add2 = matrix + MakeDuplicate(10, matrix);
    std::cout << add.RowNum() << " " << add.ColNum() << std::endl;
    std::cout << add2.BatchNum() << " " << add2.RowNum() << " " << add2.ColNum()
              << std::endl;

    auto transpose = MetaNN::Transpose(matrix);

    auto collapse = MetaNN::Collapse(batch_matrix1);
    std::cout << collapse.RowNum() << " " << collapse.ColNum() << std::endl;

    auto abs = MetaNN::Abs(matrix);
    std::cout << "abs: " << abs.RowNum() << " " << abs.ColNum() << std::endl;

    auto sign = MetaNN::Sign(matrix);
    std::cout << "sign: " << sign.RowNum() << " " << sign.ColNum() << std::endl;

    auto tanh = MetaNN::Tanh(matrix);
    std::cout << "tanh: " << tanh.RowNum() << " " << tanh.ColNum() << std::endl;

    auto softmax = MetaNN::VecSoftmax(matrix);
    std::cout << "softmax: " << softmax.RowNum() << " " << softmax.ColNum()
              << std::endl;

    auto dot = Dot(matrix, matrix);
    auto dot2 = Dot(matrix, MakeDuplicate(10, matrix));
    std::cout << "dot: " << dot.RowNum() << " " << dot.ColNum() << std::endl;
    std::cout << "dot2: " << dot2.BatchNum() << " " << dot2.RowNum() << " "
              << dot2.ColNum() << std::endl;

    auto element_mul = matrix * matrix;
    auto element_mul2 = matrix * MakeDuplicate(10, matrix);
    std::cout << "element_mul: " << element_mul.RowNum() << " "
              << element_mul.ColNum() << std::endl;
    std::cout << "element_mul2: " << element_mul2.BatchNum() << " "
              << element_mul2.RowNum() << " " << element_mul2.ColNum()
              << std::endl;

    auto divide = matrix / matrix;
    auto divide2 = matrix / MakeDuplicate(10, matrix);
    std::cout << "divide: " << divide.RowNum() << " " << divide.ColNum()
              << std::endl;
    std::cout << "divide2: " << divide2.BatchNum() << " " << divide2.RowNum()
              << " " << divide2.ColNum() << std::endl;

    auto nll = MetaNN::NegativeLogLikelihood(matrix, matrix);
    std::cout << "nll: " << divide.RowNum() << " " << divide.ColNum()
              << std::endl;

    auto softmax_derivative = MetaNN::VecSoftmaxDerivative(matrix, matrix);
    std::cout << "softmax_derivative: " << softmax_derivative.RowNum() << " "
              << softmax_derivative.ColNum() << std::endl;

    auto sigmoid_derivative = MetaNN::SigmoidDerivative(matrix, matrix);
    std::cout << "sigmoid derivative: " << sigmoid_derivative.RowNum() << " "
              << sigmoid_derivative.ColNum() << std::endl;

    std::cout << "ok" << std::endl;
    return 0;
}