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
#include<fstream>

#include<chrono>

#include"lib/model.hpp"
#include"lib/ray.hpp"
#include"lib/STLloader.hpp"
#include"lib/raytracer.hpp"

int main(){
   Raytracer rayt;

   //Load Reflective mesh data
   if(loadSTLModel(&rayt.model, "reflector.stl", SurfaceType::Reflective)){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   Model *model;

   //Load Opaque mesh data
   if(loadSTLModel(&model, "sensorCover.stl", SurfaceType::Opaque)){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   //Merge both meshes
   rayt.model->merge(model);

   //Free memory allocated for already merged model
   delete model;

   if(loadSTLModel(&model, "sensor.stl", SurfaceType::Sensor)){
      std::cout<<"Falha ao carregar modelo!"<<std::endl;
      return 255;
   }

   rayt.model->merge(model);

   delete model;

   //Open output file
   std::filebuf fb;
   fb.open("image.pgm", std::ios::out);

   real planeSize = 14.0;

   std::ostream os(&fb);

   rayt.eye = Vector3(20,0,0);     //Set camera position

   rayt.right = Vector3(0,planeSize,0);    //Set basis for
   rayt.up = Vector3(0,0,planeSize);        //camera plane

   rayt.frustum = Vector3(20,0,0);

   rayt.persp = false;   //View point in perspective
   rayt.generateImg = true;   //Generate ray hit bitmap

   rayt.resx = 800; //Set camera plane resolution
   rayt.resy = 800;

   std::chrono::time_point<std::chrono::steady_clock> start=std::chrono::steady_clock::now();

   rayt.run(); //Run Raytracer and generate image

   std::chrono::duration<real> t=std::chrono::steady_clock::now()-start;

   std::cout<<"Estatísticas"<<std::endl;

   std::cout<<rayt.resx*rayt.resy<<" raios emitidos em "<<t.count()<<" segundos"<<std::endl;
   std::cout<<"Média de "<<(rayt.resx*rayt.resy)/t.count()<<" raios/s"<<std::endl;

   real unitArea = (planeSize*planeSize)/(rayt.resx*rayt.resy*1.0);
   int rayCount = rayt.rayHitCount[SurfaceType::Opaque]+rayt.rayHitCount[SurfaceType::Reflective]+rayt.rayHitCount[SurfaceType::Sensor];

   std::cout<<"Área por pixel: "<<unitArea<<" m^2/pixel"<<std::endl;

   std::cout<<rayCount<<" raios colidiram com o telescópio"<<std::endl;

   real raytracedArea = rayCount*unitArea;

   std::cout<<"Área frontal do telescópio(Raytracer): "<<raytracedArea<<" m^2"<<std::endl;

   real area = M_PI*6.5*6.5;

   std::cout<<"Área frontal do telescópio(Teórico): "<<area<<" m^2"<<std::endl;

   std::cout<<"Desvio: "<< raytracedArea - area <<" m^2"<<std::endl;

   std::cout<<"Raios refletidos ao sensor(%, Raytracer): "<<(100.0*rayt.rayHitCount[SurfaceType::Sensor])/(1.0*rayCount)<<" %"<<std::endl;

   std::cout<<"Raios refletidos ao sensor(%, Teórico): "<<(100.0*(area-9.0))/area<<" %"<<std::endl;

   //for(int i = 0; i < 4; i++) std::cout<<i<<" : "<<rayt.rayHitCount[i]<<std::endl;

   //Export grayscale image in format .pgm
   os<<"P2\n";   //PGM magic number
   os<<rayt.resx<<" "<<rayt.resy<<"\n";  //Writes image resolution
   os<<"255\n";  //Max color value

   for(int yIdx=0; yIdx<rayt.resy; yIdx++){  //Write image data to standard out
      for(int xIdx=0; xIdx<rayt.resx; xIdx++){
         if(rayt.attrib[xIdx*rayt.resy+yIdx] != SurfaceType::None){
            os<<85*(rayt.attrib[xIdx*rayt.resy+yIdx]-1)+(int)(85*real_abs(rayt.normMap[xIdx*rayt.resy+yIdx]))<<" ";
         }else{
            os<<"0 ";
         }
      }
      os<<"\n";
   }

   fb.close();

   return 0;
}
