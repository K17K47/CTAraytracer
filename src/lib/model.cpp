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
   vtx.insert(vtx.end(), model->vtx.begin(), model->vtx.end());
   nor.insert(nor.end(), model->nor.begin(), model->nor.end());
   triangle.insert(triangle.end(), model->triangle.begin(), model->triangle.end());

   if(minX > model->minX) minX = model->minX;
   if(maxX < model->maxX) maxX = model->maxX;

   if(minY > model->minY) minY = model->minY;
   if(maxY < model->maxY) maxY = model->maxY;

   if(minZ > model->minZ) minZ = model->minZ;
   if(maxZ < model->maxZ) maxZ = model->maxZ;
}
