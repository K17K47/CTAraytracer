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

#include"aux/aabb.hpp"

bool AABB::intersectAABB(const AABB &box){
   Vector3 tmpCenter, tmpHalfwidth;

   tmpCenter = center - box.center;
   tmpHalfwidth = halfwidth - box.halfwidth;

   bool x = real_abs(tmpCenter[0]) <= tmpHalfwidth[0];
   bool y = real_abs(tmpCenter[1]) <= tmpHalfwidth[1];
   bool z = real_abs(tmpCenter[2]) <= tmpHalfwidth[2];

   return x && y && z;
}

AABB minimumTriangleAABB(Vector3 v[3]){
   AABB triAABB;
   triAABB.center = ((1.0)/(3.0))*(v[0]+v[1]+v[2]);

   for(int i = 0; i < 3; i++) v[i] -= triAABB.center;

   Vector3 halflength = v[0];

   for(int i = 1; i < 3; i++){
      for(int j = 0; j < 3; j++)
         if(halflength[j] < v[i][j]) halflength[j] = v[i][j];
   }

   triAABB.halfwidth = halflength;

   return triAABB;
}
