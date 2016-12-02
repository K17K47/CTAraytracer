/*
*    CTARaytracer
*    Copyright (C) 2016  Lucas Lopes Costa <lucas_lc.hf@hotmail.com>
*
*    This library is free software; you can redistribute it and/or
*    modify it under the terms of the GNU Lesser General Public
*    License as published by the Free Software Foundation; either
*    version 3 of the License, or (at your option) any later version.
*
*    This library is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    Lesser General Public License for more details.
*
*    You should have received a copy of the GNU Lesser General Public
*    License along with this library; if not, write to the Free Software
*    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
typedef Eigen::Transform<real, 3, Eigen::TransformTraits::Projective> Transform;

#endif
