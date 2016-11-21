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

#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include"aux/math.hpp"

class OctreeNode{
   public:
   OctreeNode* parent;
   Vector3 pivot;
   real sz;

   virtual bool isLeaf()=0;
};

template<typename T, unsigned N>
class OctreeBranch : public OctreeNode{
   public:
   OctreeNode* children[8];

   OctreeBranch(Vector3 center, real size, OctreeBranch* parentNode);
   int insert(T obj, Vector3 pos);
   int insert(std::vector<T> obj, std::vector<Vector3> pos);
   void split(unsigned idx);

   bool isLeaf();
   bool isTerminal();

   unsigned locate(Vector3 pos);
};

template<typename T, unsigned N>
class OctreeLeaf : public OctreeNode{
   public:
   std::vector<T> obj(N);
   std::vector<Vector3> objPos(N);

   OctreeLeaf(Vector3 center, real size, OctreeBranch<T,N>* parentNode);
   bool empty = true;
   bool isLeaf();
};

template <typename T, unsigned N>
class Octree{
   public:
   OctreeBranch<T,N>* root;

   Octree(Vector3 center, real sz);
   int build(std::vector<T> obj, std::vector<Vector3> pos);
};

#include"octree.tpp"

#endif
