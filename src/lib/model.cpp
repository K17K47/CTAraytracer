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

#include"lib/model.hpp"

void Model::merge(Model *model){
   //Merge vertex data
   int vOldSize = vtx.size();
   vtx.insert(vtx.end(), model->vtx.begin(), model->vtx.end());

   //Merge normals data
   int nOldSize = nor.size();
   nor.insert(nor.end(), model->nor.begin(), model->nor.end());

   //Merge triangles data
   int tOldSize = triangles.size();
   triangles.insert(triangles.end(), model->triangles.begin(), model->triangles.end());

   //Offsets Vertex and Normal indexes on triangles from merged model
   //TODO: Test for duplicated vertexes and normals, lowering memory use
   for(int i=tOldSize; i<triangles.size(); i++){
      for(int j=0; j<3; j++) triangles[i].v[j]+=vOldSize;
      triangles[i].n += nOldSize;
      triangles[i].triangleIdx = i;
   }

   for(int i=0; i < 3; i++){
      if(min[i] > model->min[i]) min[i] = model->min[i];
      if(max[i] < model->max[i]) max[i] = model->max[i];
   }
}
