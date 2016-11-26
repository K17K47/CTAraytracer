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

int loadSTLModel(Model **model, std::string path, SurfaceType attr){
   //Open model file on input stream
   std::ifstream file (path.c_str(), std::ifstream::in | std::ifstream::binary);
   if(file){
      file.seekg(0, file.end);
      int length = file.tellg(); //Get file length
      file.seekg(0, file.beg);

      //Test if file has minimum header size
      if(length < sizeof(STL_Header)) return 1;

      STL_Header fileHeader;

      //Read model header
      file.read(reinterpret_cast<char*>(&fileHeader), sizeof(STL_Header));
      if(!file) return 1;

      //Test if file has correct size for the count of triangles read
      if(fileHeader.triangleCount*sizeof(STL_Triangle)+sizeof(STL_Header)
         != length) return 1;

      *model = new Model;

      //Allocate buffer for triangles
      STL_Triangle *buffer = new STL_Triangle[fileHeader.triangleCount];

      //Read triangles from model file into buffer
      file.read(reinterpret_cast<char*>(buffer),
                fileHeader.triangleCount*sizeof(STL_Triangle));
      if(!file) return 1;

      Triangle tri;

      Vector3 xCoords, yCoords, zCoords;

      for(int i=0; i<fileHeader.triangleCount; i++){
            //Copy vertexes and normals from buffer to Model
            (*model)->vtx.push_back(Vector3(buffer[i].vtx1[0],
                                    buffer[i].vtx1[1],buffer[i].vtx1[2]));
            (*model)->vtx.push_back(Vector3(buffer[i].vtx2[0],
                                    buffer[i].vtx2[1],buffer[i].vtx2[2]));
            (*model)->vtx.push_back(Vector3(buffer[i].vtx3[0],
                                    buffer[i].vtx3[1],buffer[i].vtx3[2]));

            (*model)->nor.push_back(Vector3(buffer[i].normal[0],
                                    buffer[i].normal[1],buffer[i].normal[2]));

            //Pick coordinates from triangle vertex...
            Vector3 coords[3];
            coords[0] = Vector3(buffer[i].vtx1[0],buffer[i].vtx2[0],
                              buffer[i].vtx3[0]);
            coords[1] = Vector3(buffer[i].vtx1[1],buffer[i].vtx2[1],
                              buffer[i].vtx3[1]);
            coords[2] = Vector3(buffer[i].vtx1[2],buffer[i].vtx2[2],
                              buffer[i].vtx3[2]);

            //...and calculate minimum AABB for mesh
            for(int j = 0; j < 3; j++){
               if((coords[j].minCoeff() < (*model)->min[j]) || i==0)
                  (*model)->min[j] = coords[j].minCoeff();
               if((coords[j].maxCoeff() > (*model)->max[j]) || i==0)
                  (*model)->max[j] = coords[j].maxCoeff();
            }

            //Fill triangle struct
            for(int j=0; j<3; j++) tri.v[j] = i*3+j;
            tri.n = i;
            tri.type = attr;

            //And push it on end of triangles vector
            (*model)->triangles.push_back(tri);
      }
   }

   return 0;
}
