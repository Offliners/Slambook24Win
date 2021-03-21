#include<iostream>
#include<cmath>
#include<Eigen/Core>
#include<Eigen/Geometry>

#define M_PI 3.14159265358979323846

using namespace std;
using namespace Eigen;

int main(int argc, char **argv)
{
    Matrix3d rotation_matrix = Matrix3d::Identity();

    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1)); // 沿著z軸旋轉45°

    cout.precision(3);
    cout << "rotation matrix =\n" << rotation_vector.matrix() << endl;
    rotation_matrix = rotation_vector.toRotationMatrix();


    // 用AngleAxis進行座標轉換
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation (by angle axis) = " << v_rotated.transpose() << endl;


    // 或用旋轉矩陣
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation (by matrix) = " << v_rotated.transpose() << endl;


    // 尤拉角 : 可以將旋轉矩陣轉成尤拉角
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZXY順序，即roll pitch yaw順序
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;


    // 歐氏轉換
    Isometry3d T = Isometry3d::Identity();  //雖稱是3D，但實質是4*4矩陣
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1, 3, 4)); // 把平移向量設成(1, 3, 4)
    cout << "Transform matrix =\n" << T.matrix() << endl;


    // 轉換矩陣
    Vector3d v_transformed = T * v; // 相當於 R * v + t 
    cout << "v transformed = " << v_transformed.transpose() << endl;


    // 對於仿射轉換與射影轉換，使用Eigen::Affine3d和Eigen::Projective3d即可，略


    // 四元數
    Quaterniond q = Quaterniond(rotation_vector);
    cout << "quaternion from ratation vector = " << q.coeffs().transpose() << endl; // 注意coeffs順序是(x, y, z, w)，w為實部，前三者為虛部

    // 也可以把給轉移矩陣指定給他
    q = Quaterniond(rotation_matrix);
    cout << "quaternion from ratation matrix = " << q.coeffs().transpose() << endl;

    v_rotated = q * v; // 數學上是 qvq^(-1)
    cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << endl;

    cout << "should be equal to " << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl;

    return 0;
}