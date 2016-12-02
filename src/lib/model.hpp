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

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include"aux/math.hpp"

enum SurfaceType{  //Define reflection attribute for triangles
   None = 0,
   Opaque = 1,
   Reflective = 2,
   Sensor = 3
};

struct Triangle{
   int v[3]; //Vertex index
   int n;   //Normal index
   SurfaceType type; //Triangle surface caracteristic
};

class Model{ //Stores 3D Mesh data
   public:
      std::vector<Vector3> vtx; //Vertex data
      std::vector<Vector3> nor; //Surface normals data
      std::vector<Triangle> triangles; //Triangles data

      Vector3 min, max; //Minimal Axis Aligned Boundary Box

   public:
      void merge(Model *model); //Merge *model data
};

#endif
