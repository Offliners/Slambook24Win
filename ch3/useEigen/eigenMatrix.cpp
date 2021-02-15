#include<iostream>                                                                                                                                                                                          
#include<ctime>
#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

using namespace std;

int main(int argc, char** argv)
{
        //           <type, column, row>
        Eigen::Matrix<float, 2, 3> matrix_23;

        Eigen::Vector3d v_3d;  // Eigen::Matrix<double, 3, 1>
        Eigen::Matrix<float,3,1> vd_3d;

        // initialize to zero
        Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();

        // dynamic
        Eigen::Matrix< double, Eigen::Dynamic, Eigen::Dynamic > matrix_dynamic;

        Eigen::MatrixXd matrix_x;

        matrix_23 << 1, 2, 3, 4, 5, 6;
        cout << matrix_23 << endl;

        for (int i = 0; i < 2; i++)
        {
                for (int j = 0; j < 3; j++)
                        cout << matrix_23(i,j) << "\t";
                cout<<endl;
        }

        // Matrix multiplication
        cout << "Matrix multiplication" << endl;
        v_3d << 3, 2, 1;
        Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
        cout << "Result 1" << endl;
        cout << result << endl;

        vd_3d << 4, 5, 6;
        Eigen::Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
        cout << "Result 2" << endl;
        cout << result2 << endl;

        // Random Matrix
        matrix_33 = Eigen::Matrix3d::Random();
        cout << matrix_33 << endl << endl;

        cout << matrix_33.transpose() << endl;      // Transpose
        cout << matrix_33.sum() << endl;            // Sum of all entries
        cout << matrix_33.trace() << endl;          // Trace
        cout << 10 * matrix_33 << endl;             // Scalar multiplication
        cout << matrix_33.inverse() << endl;        // Inverse
        cout << matrix_33.determinant() << endl;    // Determinant

        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver (matrix_33.transpose() * matrix_33);
        cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
        cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;


        // Solve equaion
        Eigen::Matrix< double, MATRIX_SIZE, MATRIX_SIZE > matrix_NN;
        matrix_NN = Eigen::MatrixXd::Random( MATRIX_SIZE, MATRIX_SIZE );
        Eigen::Matrix< double, MATRIX_SIZE,  1> v_Nd;
        v_Nd = Eigen::MatrixXd::Random( MATRIX_SIZE,1 );

        clock_t time_stt = clock();
        Eigen::Matrix<double,MATRIX_SIZE,1> x = matrix_NN.inverse()*v_Nd;
        cout <<"time use in normal inverse is " << 1000* (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms"<< endl;
    
        time_stt = clock();
        x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
        cout << "time use in Qr decomposition is " << 1000*  (clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms" << endl;

        return 0;
}                                                                                                                                                                                                           1,1           Top
