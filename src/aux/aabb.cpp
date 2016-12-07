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
   Vector3 tmpCenter, tmpHalfsize;

   tmpCenter = center - box.center;
   tmpHalfsize = halfsize + box.halfsize;

   bool x = real_abs(tmpCenter[0]) <= tmpHalfsize[0];
   bool y = real_abs(tmpCenter[1]) <= tmpHalfsize[1];
   bool z = real_abs(tmpCenter[2]) <= tmpHalfsize[2];

   return x && y && z;
}

AABB minimumTriangleAABB(Vector3 v[3]){
   AABB triAABB;

   //Uses barycenter of triangle as AABB center point
   triAABB.center = ((1.0)/(3.0))*(v[0]+v[1]+v[2]);

   v[0] -= triAABB.center;
   v[1] -= triAABB.center;
   v[2] -= triAABB.center;

   Vector3 halfsize;

   for(int i = 0; i < 3; i++) halfsize[i] = real_abs(v[0][i]);

   real tmp;

   for(int i = 1; i < 3; i++){
      for(int j = 0; j < 3; j++){
         tmp = real_abs(v[i][j]);
         if(halfsize[j] < tmp) halfsize[j] = tmp;
      }
   }

   triAABB.halfsize = halfsize;

   return triAABB;
}
