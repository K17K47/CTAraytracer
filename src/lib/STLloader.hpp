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

#ifndef STLLOADER_HPP_
#define STLLOADER_HPP_

#include<cstdint>
#include<string>

#include"lib/model.hpp"

#pragma pack(1)
struct STL_Header{
   uint8_t header[80];
   uint32_t triangleCount;
};

#pragma pack(1)
struct STL_Triangle{
   float normal[3];
   float vtx1[3];
   float vtx2[3];
   float vtx3[3];
   uint16_t attr;
};

int loadSTLModel(Model **model, std::string path, int attr);

#endif
