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
#include"aux/aabb.hpp"

#include"lib/model.hpp"

class OctreeNode{
   public:
   OctreeNode* parent;
   AABB aabb;

   virtual bool isLeaf()=0;
};

class OctreeBranch : public OctreeNode{
   public:
      OctreeNode* children[8];

      OctreeBranch(AABB box, OctreeBranch* parentNode);

      int insert(Triangle tri, Model *model);
      int insert(std::vector<Triangle> *tri, Model *model);

      void split(unsigned idx);

      bool isLeaf();

      unsigned locate(Vector3 pos);
      AABB childrenAABB(unsigned idx);
   private:
      int insertSub(Triangle tri, AABB triAABB);
      int insertSub(std::vector<Triangle> *tri, std::vector<AABB> *triAABB);
};

class OctreeLeaf : public OctreeNode{
   public:
   std::vector<Triangle> obj;
   std::vector<AABB> aabbs;

   OctreeLeaf(AABB box, OctreeBranch* parentNode);
   bool empty = true;
   bool isLeaf();
};

class Octree{
   public:
   OctreeBranch* root;

   Octree(AABB box);
   int build(std::vector<Triangle> *obj, Model *model);
};

#endif
