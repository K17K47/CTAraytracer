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

#ifndef RAY_TPP_
#define RAY_TPP_

#include"lib/ray.hpp"

real Ray::intersectTriangle(Vector3 tri[3]){ //Möller-Trumbore Algorithm

   Vector3 e1 = tri[1]-tri[0];
   Vector3 e2 = tri[2]-tri[0];

   Vector3 P = dir.cross(e2);
   real det = e1.dot(P);

   if(det > -1e-6 && det < 1e-6) return -1.0;
   real invDet = 1.0/det;

   Vector3 T = origin-tri[0];

   real u = T.dot(P)*invDet;

   if(u < 0.0 || u > 1.0) return -1.0;

   Vector3 Q = T.cross(e1);

   real v = dir.dot(Q)*invDet;

   if(v < 0.0 || u+v > 1.0) return -1.0;

   real t = e2.dot(Q)*invDet;

   return t;
}

RayTriangleColl Ray::intersectModel(Model *model){
   real t;
   Vector3 v[3];

   RayTriangleColl coll;

   coll.t = 0.0;

   for(int i=0; i<model->triangles.size(); i++){
      for(int j=0; j<3; j++) v[j]=model->vtx[model->triangles[i].v[j]];
      t = intersectTriangle(v);
      if(t>0.0 && (t<coll.t || coll.t==0.0)){
         coll.t=t;
         coll.triangleIdx=i;
      }
   }

   if(coll.t!=0.0){
      coll.n=model->vtx[model->triangles[coll.triangleIdx].n];
   }

   return coll;
}

#endif
