#ifndef MATH_HPP_
#define MATH_HPP_

#include<math.h>
#include<float.h>

#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<eigen3/Eigen/Geometry>

#include<vector>

#define QUADP

#ifdef QUADP
   #define real_sqrt sqrtl
   #define real_pow powl
   #define real_abs fabsl
   #define real_sin sinl
   #define real_cos cosl
   #define real_exp expl

   #define REAL_MAX LDBL_MAX
   typedef long double real;
#elif DOUBLEP
   #define real_sqrt sqrtl
   #define real_pow powl
   #define real_abs fabsl
   #define real_sin sinl
   #define real_cos cosl
   #define real_exp expl

   #define REAL_MAX DBL_MAX
   typedef double real;
#else
   #define real_sqrt sqrtf
   #define real_sqrt sqrtf
   #define real_pow powf
   #define real_abs fabsf
   #define real_sin sinf
   #define real_cos cosf
   #define real_exp expf

   #define REAL_MAX FLT_MAX
   typedef float real;
#endif

typedef Eigen::Matrix<real, 2, 1, 0, 2, 1> Vector2;
typedef Eigen::Matrix<real, 3, 1, 0, 3, 1> Vector3;
typedef Eigen::Matrix<real, 4, 1, 0, 4, 1> Vector4;
typedef Eigen::Matrix<real, 3, 3, 0, 3, 3> Matrix33;
typedef Eigen::Matrix<real, 3, 4, 0, 3, 4> Matrix34;
typedef Eigen::Matrix<real, 4, 4, 0, 4, 4> Matrix44;
typedef Eigen::Quaternion<real> Quaternion;
typedef Eigen::AngleAxis<real> AngleAxis;
typedef Eigen::Translation<real, 3> Translation3;

#endif
