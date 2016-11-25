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

enum CollType {
   None = 0,
   Opaque = 1,
   Reflective = 2
};

struct Triangle{
   int v[3]; //Vertex index
   int n;   //Normal index
   CollType type; //0-Opaque,1-Reflective,2-CCD
};

class Model{
   public:
      std::vector<Vector3> vtx;
      std::vector<Vector3> nor;
      std::vector<Triangle> triangles;

      real minX, maxX;
      real minY, maxY;
      real minZ, maxZ;

   public:
      void merge(Model *model);
};

#endif
