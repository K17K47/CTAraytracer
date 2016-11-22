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

#include"aux/math.hpp"
#include"lib/STLloader.hpp"

int loadSTLModel(Model **model, std::string path){
   std::ifstream file (path.c_str(), std::ifstream::in | std::ifstream::binary);
   if(file){
      file.seekg(0, file.end);
      int length = file.tellg();
      file.seekg(0, file.beg);

      if(length < sizeof(STL_Header)){
         std::cout<<"Arquivo é menor que cabeçalho\n";
         return 0;
      }
      STL_Header fileHeader;

      file.read(reinterpret_cast<char*>(&fileHeader), sizeof(STL_Header));
      if(!file){
         std::cout<<"Leitura do cabeçalho falhou\n";
         return 0;
      }

      std::cout<<"Número de triângulos:"<<fileHeader.triangleCount<<"\n";

      if(fileHeader.triangleCount*sizeof(STL_Triangle)+sizeof(STL_Header) != length){
         std::cout<<"Arquivo tem contagem de triângulos errada\n";
         return 0;
      }
      *model = new Model;

      STL_Triangle *buffer = new STL_Triangle[fileHeader.triangleCount];

      file.read(reinterpret_cast<char*>(buffer), fileHeader.triangleCount*sizeof(STL_Triangle));
      if(!file){
         std::cout<<"Leitura dos triângulos falhou\n";
         return 0;
      }

      Triangle tri;

      Vector3 xCoords, yCoords, zCoords;

      for(int i=0; i<fileHeader.triangleCount; i++){
            (*model)->vtx.push_back(Vector3(buffer[i].vtx1[0],buffer[i].vtx1[1],buffer[i].vtx1[2]));
            (*model)->vtx.push_back(Vector3(buffer[i].vtx2[0],buffer[i].vtx2[1],buffer[i].vtx2[2]));
            (*model)->vtx.push_back(Vector3(buffer[i].vtx3[0],buffer[i].vtx3[1],buffer[i].vtx3[2]));

            (*model)->nor.push_back(Vector3(buffer[i].normal[0],buffer[i].normal[1],buffer[i].normal[2]));

            xCoords = Vector3(buffer[i].vtx1[0],buffer[i].vtx2[0],buffer[i].vtx3[0]);
            yCoords = Vector3(buffer[i].vtx1[1],buffer[i].vtx2[1],buffer[i].vtx3[1]);
            zCoords = Vector3(buffer[i].vtx1[2],buffer[i].vtx2[2],buffer[i].vtx3[2]);

            if((xCoords.minCoeff() < (*model)->minX) || i==0) (*model)->minX = xCoords.minCoeff();
            if((xCoords.maxCoeff() > (*model)->maxX) || i==0) (*model)->maxX = xCoords.maxCoeff();

            if((yCoords.minCoeff() < (*model)->minY) || i==0) (*model)->minY = yCoords.minCoeff();
            if((yCoords.maxCoeff() > (*model)->maxY) || i==0) (*model)->maxY = yCoords.maxCoeff();

            if((zCoords.minCoeff() < (*model)->minZ) || i==0) (*model)->minZ = zCoords.minCoeff();
            if((zCoords.maxCoeff() > (*model)->maxZ) || i==0) (*model)->maxZ = zCoords.maxCoeff();

            for(int j=0; j<3; j++) tri.v[j] = i*3+j;
            tri.n = i;
            tri.type = buffer[i].attr;
            (*model)->triangles.push_back(tri);
      }
   }

   return 1;
}
