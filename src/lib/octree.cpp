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

#define DEPTH 10
#include"lib/octree.hpp"

Octree::Octree(AABB box){
   root = new OctreeBranch(box, nullptr);
}

int Octree::build(std::vector<Triangle> *obj, Model *model){
   return root->insert(obj, model);
}

OctreeBranch::OctreeBranch(AABB box, OctreeBranch* parentNode){
   parent = parentNode;
   aabb = box;

   for(int i = 0; i < 8; i++) children[i] = nullptr;
}

int OctreeBranch::insert(Triangle tri, Model *model){
   Vector3 v[3];

   for(int i = 0; i < 3; i++) v[i] = model->vtx[tri.v[i]];

   AABB triAABB = minimumTriangleAABB(v);

   return insertSub(tri, triAABB);
}

int OctreeBranch::insert(std::vector<Triangle> *tri, Model *model){
   Vector3 v[3];

   std::vector<AABB> aabbs;

   for(int i = 0; i < tri->size(); i++){
         for(int j = 0; j < 3; j++) v[j] = model->vtx[(*tri)[i].v[j]];

         aabbs.push_back(minimumTriangleAABB(v));
   }

   return insertSub(tri, &aabbs);
}

bool OctreeBranch::isLeaf() {return false;}

unsigned OctreeBranch::locate(Vector3 pos){
   unsigned idx = 0;

   Vector3 tmp = aabb.center - pos;

   if((real_abs(tmp[0]) > aabb.halfsize[0]) ||
      (real_abs(tmp[1]) > aabb.halfsize[1]) ||
      (real_abs(tmp[2]) > aabb.halfsize[2])){
      return 8;
   }

   //x
   if(tmp[0] < 0) idx+=1;
   //y
   if(tmp[1] < 0) idx+=2;
   //z
   if(tmp[2] < 0) idx+=4;

   return idx;
}

AABB OctreeBranch::childrenAABB(unsigned idx){
   AABB tmp;
   tmp.halfsize = 0.5*aabb.halfsize;
   tmp.center = tmp.halfsize;

   //x
   if(idx & 1) tmp.center[0] *= -1;
   //y
   if(idx & 2) tmp.center[1] *= -1;
   //z
   if(idx & 4) tmp.center[2] *= -1;

   tmp.center += aabb.center;

   return tmp;
}

int OctreeBranch::insertSub(Triangle tri, AABB triAABB){
   bool intersects;

   for(int i = 0; i < 8; i++){
      intersects = false;

      if(children[i] == nullptr){
         intersects = triAABB.intersectAABB(childrenAABB(i));
      }else{
         intersects = triAABB.intersectAABB(children[i]->aabb);
      }

      if(intersects){
         if(children[i] == nullptr){
            children[i] = new OctreeLeaf(childrenAABB(i), this);
         }

         if(children[i]->isLeaf()){
            if(dynamic_cast<OctreeLeaf*>(children[i])->obj.size()!=DEPTH){
               dynamic_cast<OctreeLeaf*>(children[i])->obj.push_back(tri);
               dynamic_cast<OctreeLeaf*>(children[i])->aabbs.push_back(triAABB);
               return 0;
            }else{
               split(i);
               return dynamic_cast<OctreeBranch*>(children[i])->insertSub(tri, triAABB);
            }
         }else{
            return dynamic_cast<OctreeBranch*>(children[i])->insertSub(tri, triAABB);
         }
      }
   }

   return -1;
}

int OctreeBranch::insertSub(std::vector<Triangle> *tri, std::vector<AABB> *triAABB){
   for(int i = 0; i < tri->size(); i++){
      insertSub((*tri)[i], (*triAABB)[i]);
   }

   return 0;
}

void OctreeBranch::split(unsigned idx){
   OctreeLeaf *child = dynamic_cast<OctreeLeaf*>(children[idx]);

   OctreeBranch *tmp = new OctreeBranch(child->aabb, this);
   tmp->insertSub(&child->obj, &child->aabbs);

   delete children[idx];
   children[idx] = tmp;
}

OctreeLeaf::OctreeLeaf(AABB box, OctreeBranch* parentNode){
   aabb = box;
   parent = parentNode;
}

bool OctreeLeaf::isLeaf() {return true;}
