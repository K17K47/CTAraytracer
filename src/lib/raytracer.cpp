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
   Vector3 n = (up.cross(right)).normalized();  //Calculate camera plane normal vector

   Vector3 scrOrigin = -0.5*(right+up);//Calculate screen origin on camera plane

   Vector3 cameraOrigin = scrOrigin + eye;

   if(generateImg){
      attrib.clear();
      normMap.clear();
      attrib.reserve(resx*resy); //Preallocate enough memory for the generated image
      normMap.reserve(resx*resy);
   }

   for(int i = 0; i < 4; i++) rayHitCount[i] = 0;

   Ray ray;
   RayTriangleColl coll, prevColl;

   Vector3 prevRayDir;

   real t1, t2;

   if(oct == nullptr){
      oct = new Octree(AABB(Vector3(0,0,0), model->max));
      oct->build(&model->triangles, model);
   }

   real inv_ResX = 1.0/(resx-1.0);
   real inv_ResY = 1.0/(resy-1.0);

   //Raytrace for each pixel in camera plane
   for(int x=0; x<resx; x++){
      for(int y=0; y<resy; y++){
         t1 = x*inv_ResX;   //Calculate camera plane parametrized
         t2 = y*inv_ResY;   //pixel coordinates

         //Sets ray origin on pixel coordinate on camera plane
         ray.origin = cameraOrigin+t1*right+t2*up;

         ray.dir = persp*(ray.origin-frustum).normalized()+(!persp)*n;

         prevColl.attr = SurfaceType::None;//Clears last collision surf. attrib.

         //TODO: Shoot multiple ray for each pixel, and average their color
         do{
            //Shoot ray and test for intersection
            coll = ray.intersectModelOctree(oct, model);

            //Exits when ray misses or hit opaque surface
            if(coll.attr != SurfaceType::Reflective) break;

            //If ray hits reflective surface...
            //..stores collision attributes...
            prevColl = coll;
            prevRayDir = ray.dir;

            //...calculate secondary ray origin...
            ray.origin += coll.t * ray.dir;

            //...and reflect ray direction vector in relation to surf. normal
            ray.dir = (ray.dir - 2.0*ray.dir.dot(coll.n)*coll.n).normalized();
         }while(true);

         //Ray statistics
         if(coll.attr == SurfaceType::None && prevColl.attr == SurfaceType::Reflective){
            rayHitCount[SurfaceType::Reflective]++;
            if(generateImg){
               attrib.push_back(SurfaceType::Reflective);
               normMap.push_back(prevRayDir.dot(prevColl.n));
            }
         }else{
            rayHitCount[coll.attr]++;
            if(generateImg){
               attrib.push_back(coll.attr);
               if(coll.attr == SurfaceType::None){
                  normMap.push_back(0.0);
               }else{
                  normMap.push_back(ray.dir.dot(coll.n));
               }
            }
         }
      }
   }
}
