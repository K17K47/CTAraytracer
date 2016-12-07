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

#include"aux/math.hpp"
#include"aux/aabb.hpp"

#include"lib/model.hpp"
#include"lib/STLloader.hpp"
#include"lib/octree.hpp"

int main(){
   Model *model;

   //Load Reflective mesh data
   if(loadSTLModel(&model, "telescope.stl", SurfaceType::Opaque)){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   AABB aabb;

   aabb.center = Vector3(0,0,0);

   std::cout<<model->max<<"\n";

   aabb.halfsize = model->max;

   Octree oct(aabb);

   oct.build(&(model->triangles), model);

   return 0;
}
