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

#include"lib/raytracer.hpp"
#include"lib/ray.hpp"

void Raytracer::run(){
   Vector3 n = up.cross(right);
   n *= (1.0/n.norm());

   Vector3 scrOrigin = -0.5*(right+up);

   img.reserve(resx*resy);

   Ray ray;
   RayTriangleColl coll, prevColl;

   Vector3 prevRayDir;

   real t1, t2;

   for(int x=0; x<resx; x++){
      for(int y=0; y<resy; y++){
         t1 = (x*1.0)/(resx-1.0);
         t2 = (y*1.0)/(resy-1.0);

         if(persp){
            ray.dir = frustum-(eye+scrOrigin+t1*right+t2*up);
            ray.dir *= 1.0/ray.dir.norm();
            ray.origin = frustum;
         }else{
            ray.origin = eye+scrOrigin+t1*right+t2*up;
            ray.dir = n;
         }

         prevColl.attr = CollType::None;

         do{
            coll = ray.intersectModel(model);
            if(coll.attr == CollType::Reflective){
               prevColl = coll;
               prevRayDir = ray.dir;

               ray.origin += coll.t * ray.dir;

               ray.dir += 2.0*ray.dir.dot(coll.n)*coll.n;
               ray.dir *= 1.0/ray.dir.norm();
            }
         }while(coll.attr == CollType::Reflective);

         if(coll.attr == CollType::Opaque) {
            img.push_back(127*real_abs(ray.dir.dot(coll.n)));
         }else if(prevColl.attr == CollType::Reflective){
            img.push_back(128+127*real_abs(prevRayDir.dot(prevColl.n)));
         }else{
            img.push_back(255); //Background color
         }
      }
   }
}
