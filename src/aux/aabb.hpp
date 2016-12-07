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

#ifndef AABB_HPP_
#define AABB_HPP_

#include"aux/math.hpp"

struct AABB{
   Vector3 center;
   Vector3 halfsize;

   AABB() : center(Vector3(0,0,0)), halfsize(Vector3(0,0,0)) {}

   AABB(const Vector3 &centro, const Vector3 &dimensoes)
      : center(centro),
        halfsize(dimensoes) {}

   bool intersectAABB(const AABB &box);
};

AABB minimumTriangleAABB(Vector3 v[3]);

#endif
