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

#ifndef RAY_HPP_
#define RAY_HPP_

#include"aux/math.hpp"
#include"aux/octree.hpp"
#include"lib/colision.hpp"
#include"lib/model.hpp"

class Ray{
   public:
      Vector3 origin;
      Vector3 dir;
   public:
      template <typename T, unsigned N>
      int intersectOctree(Octree<T,N> *octree, std::vector<colision> *colisions);

      int intersectTriangle(Triangle *tri, colision *col);
   private:
      int firstNode(Vector3 t0, Vector3 tm);
      int newNode(Vector3 t, Vector3 v);

      template <typename T, unsigned N>
      void procSubtree(Vector3 t0, Vector3 t1, OctreeNode* node, std::vector<colision> *colisions);

      template <typename T, unsigned N>
      void rayParameter(Octree<T,N> *oct, std::vector<colision> *colisions);
};

#include"lib/ray.tpp"

#endif
