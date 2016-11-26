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

#ifndef RAY_HPP_
#define RAY_HPP_

#include"aux/math.hpp"
#include"lib/model.hpp"

struct RayTriangleColl{ //Ray-Triangle collision data
      real t;  //Ray parameter for the collision
      Vector3 n;  //Intersected triangle normal vector
      SurfaceType attr; //Triangle optical caracteristic
      int triangleIdx;  //Triangle index
};


class Ray{
   public:
      Vector3 origin; //Ray origin
      Vector3 dir;   //Ray direction vector
   public:
      real intersectTriangle(Vector3 v[3]);  //Test ray collision with triangle
      RayTriangleColl intersectModel(Model *model);//Test ray collision with mesh
};

#endif
