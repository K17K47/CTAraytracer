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

int main(){
   Model *model;

   if(loadSTLModel(&model, "model.stl")){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   Vector3 c = Vector3(10, -2, -2);
   Vector3 n = Vector3(-1, 0, 0);
   Vector3 v1 = Vector3(0, 4, 0);
   Vector3 v2 = Vector3(0, 0, 4);

   unsigned nx = 200;
   unsigned ny = 200;

   real x,y;

   RayTriangleColl coll;

   Vector3 dir, ori, p;

   Ray ray;

   int img[nx][ny];

   memset(img, 0, nx*ny*sizeof(int));

   for(int xIdx=0; xIdx<nx; xIdx++){
      for(int yIdx=0; yIdx<ny; yIdx++){
         x=(xIdx*1.0)/(nx*1.0);
         y=(yIdx*1.0)/(ny*1.0);

         ori = c+x*v1+y*v2;

         dir = n;

         ray.origin = ori;
         ray.dir = dir;

         //std::cout<<"Raio "<<xIdx<<" "<<yIdx<<"\n";
         //std::cout<<ori;
         coll = ray.intersectModel(model);
         //std::cout<<"Parametro da colisao"<<t<<"\n";
         if(coll.t>0) img[xIdx][yIdx]=real_abs(dir.dot(coll.n))*255;
      }
   }

   std::cout<<"P2\n";
   std::cout<<nx<<" "<<ny<<"\n";
   std::cout<<"255";
   for(int yIdx=0; yIdx<ny; yIdx++){
      for(int xIdx=0; xIdx<nx; xIdx++){
         std::cout<<img[xIdx][yIdx]<<" ";
      }
      std::cout<<"\n";
   }

   return 0;
}
