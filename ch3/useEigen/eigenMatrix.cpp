#include<iostream>
#include<ctime>

// 稠密矩陣的代數運算(逆、特徵值等)
#include<Eigen/Core>

// Eigen 核心部分
#include<Eigen/Dense>

#define MATRIX_SIZE 50

using namespace std;
using namespace Eigen;

int main(int argc, char **argv)
{
    // 宣告一個2*3的float矩陣
    Matrix<float, 2, 3> matrix_23;

    // Vector3d實質上是Eigen::Matrix<double, 3, 1>，即3D向量
    Vector3d v_3d;
    
    // 剛上面相同
    Matrix<float, 3, 1> vd_3d;

    // Matrix3d實質上是Eigen::Matrix<double, 3, 3>
    Matrix3d matrix_33 = Matrix3d::Zero(); // 初始化為0

    // 如果不確定矩陣大小，可用動態大小的矩陣
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;

    // 更簡單的
    MatrixXd matrix_x;

    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout << "matrix 2*3 from 1 to 6 :\n" << matrix_23 << endl;


    // 用()存取矩陣中的元素
    cout << "print matrix 2*3 :" << endl;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
            cout << matrix_23(i, j) << "\t";
        cout << endl;
    }

    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;


    // 不能混和兩種不同型態的矩陣
    // Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    // 需要顯性轉型
    Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << "[1, 2, 3;4, 5, 6] * [3, 2, 1] = " << result.transpose() << endl;

    Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
    cout << "[1, 2, 3;4, 5, 6] * [3, 2, 1] = " << result2.transpose() << endl;

    // 同樣地，不能搞錯矩陣的維度
    // Eigen::Matrix<dounle, 2, 3> result_wrong_dimension = matrix_23.cast<double>() * v_3d;


    // 矩陣運算
    matrix_33 = Matrix3d::Random();  // 亂數矩陣
    cout << "random matrix :\n" << matrix_33 << endl;
    cout << "transpose :\n" << matrix_33.transpose() << endl; // 轉置
    cout << "sum :\n" << matrix_33.sum() << endl; // 個元素和
    cout << "trace :\n" << matrix_33.trace() << endl; // 跡
    cout << "times 10 :\n" << 10 * matrix_33 << endl; // 數乘
    cout << "inverse :\n" << matrix_33.inverse() << endl; // 逆
    cout << "det :\n" << matrix_33.determinant() << endl; // 行列式


    // 特徵值
    // 實對稱矩陣可以保證對角化成功
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen values =\n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors =\n" << eigen_solver.eigenvectors() << endl;


    // 解方程式
    // 求解 matrix_NN * x = v_Nd 方程式
    // 直接求逆自然是最直接的，但是運算量大
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN * matrix_NN.transpose(); // 保證半正定
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);


    clock_t time_stt = clock();
 
    // 直接求逆
    Matrix<double, MATRIX_SIZE, 1> x1 = matrix_NN.inverse() * v_Nd;

    cout << "time of normal inverse is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x1 = " << x1.transpose() << endl;

    time_stt = clock();

    // 使用QR分解
    Matrix<double, MATRIX_SIZE, 1> x2 = matrix_NN.colPivHouseholderQr().solve(v_Nd);

    cout << "time of decomposition is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x2 = " << x2.transpose() << endl;

    time_stt = clock();

    // 對於正定矩陣，還可以使用Cholesky分解
    Matrix<double, MATRIX_SIZE, 1> x3 = matrix_NN.ldlt().solve(v_Nd);

    cout << "time of ldlt decomposition is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x3 = " << x3.transpose() << endl;

    return 0;
}