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

#include<iostream>

#include"lib/model.hpp"
#include"lib/ray.hpp"
#include"lib/STLloader.hpp"
#include"lib/raytracer.hpp"

int main(){
   Raytracer rayt;

   if(loadSTLModel(&rayt.model, "telescopeReflector.stl", SurfaceType::Reflective)){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   Model *model;

   if(loadSTLModel(&model, "telescopeBeams.stl", SurfaceType::Opaque)){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   rayt.model->merge(model);

   delete model;

   rayt.eye = Vector3(-16,0,0);
   rayt.right = Vector3(0,-3,0);
   rayt.up = Vector3(0,0,3);
   rayt.frustum = Vector3(-17,0,0);

   rayt.persp = true;

   rayt.resx = 1600;
   rayt.resy = 1600;

   rayt.run();

   std::cout<<"P2\n";
   std::cout<<rayt.resx<<" "<<rayt.resy<<"\n";
   std::cout<<"255\n";
   for(int yIdx=0; yIdx<rayt.resy; yIdx++){
      for(int xIdx=0; xIdx<rayt.resx; xIdx++){
         std::cout<<rayt.img[xIdx*rayt.resy+yIdx]<<" ";
      }
      std::cout<<"\n";
   }

   return 0;
}
