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

class octreeNode{
   public:
   octreeNode* parent;
   Vector3 pivot;
   real sz;

   virtual bool isLeaf()=0;
};

template<typename T, unsigned N>
class octreeBranch : public octreeNode{
   public:
   octreeNode* children[8];

   octreeBranch(Vector3 center, real size, octreeBranch* parentNode);
   int insert(T obj, Vector3 pos);
   int insert(std::vector<T> obj, std::vector<Vector3> pos);
   void split(unsigned idx);

   bool isLeaf();

   unsigned locate(Vector3 pos);
};

template<typename T, unsigned N>
class octreeLeaf : public octreeNode{
   public:
   std::vector<T> obj(N);
   std::vector<Vector3> objPos(N);

   octreeLeaf(Vector3 center, real size, octreeBranch<T,N>* parentNode);
   bool empty = true;
   bool isLeaf();
};

template <typename T, unsigned N>
class octree{
   public:
   octreeBranch<T,N>* root;

   octree(Vector3 center, real sz);
   int build(std::vector<T> obj, std::vector<Vector3> pos);
};

#include"octree.tpp"

#endif
