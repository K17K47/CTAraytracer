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

#ifndef RAY_TPP_
#define RAY_TPP_

#include"lib/ray.hpp"

//Möller-Trumbore Algorith for ray-triangle intersection test
real Ray::intersectTriangle(Vector3 tri[3]){

   Vector3 e1 = tri[1]-tri[0];
   Vector3 e2 = tri[2]-tri[0];

   Vector3 P = dir.cross(e2);
   real det = e1.dot(P);

   if(det > -1e-6 && det < 1e-6) return -1.0;
   real invDet = 1.0/det;

   Vector3 T = origin-tri[0];

   real u = T.dot(P)*invDet;

   if(u < 0.0 || u > 1.0) return -1.0;

   Vector3 Q = T.cross(e1);

   real v = dir.dot(Q)*invDet;

   if(v < 0.0 || u+v > 1.0) return -1.0;

   real t = e2.dot(Q)*invDet;

   return t;
}

RayTriangleColl Ray::intersectModel(Model *model){
   real t = 0.0;
   Vector3 v[3];

   RayTriangleColl coll;

   coll.t = 0.0;

   //TODO: Implement sub-linear collision testing with spatial subdivision
   for(int i=0; i < model->triangles.size(); i++){ //For each triangle...
      for(int j=0; j < 3; j++) v[j]=model->vtx[model->triangles[i].v[j]];

      t = intersectTriangle(v);  //...test if is intersected by the ray

      if(t > 1e-6 && (t < coll.t || coll.t == 0.0)){
         //Pick only the closest collisions, with a tolerance of 1e-6
         coll.t = t;
         coll.triangleIdx = i;
      }
   }

   if(coll.t > 0.0){ //If collision ocurred...
      //...copy normal and surface type to collision data structure
      coll.n = model->nor[model->triangles[coll.triangleIdx].n];
      coll.attr = model->triangles[coll.triangleIdx].type;
   }else{   //If there wasn't a collision,
      coll.t = -1.0; //Give it a impossible ray parameter
      coll.attr = SurfaceType::None;   //And a null surface type
   }

   return coll;
}

int Ray::firstNode(Vector3 t0, Vector3 tm){
   int tMax = t0.maxCoeff();

   //Testa qual o primeiro plano intersectado pelo raio
   if(tMax == t0[0]){ //Plano YZ
      return (tm[1]<t0[0])*2+(tm[2]<t0[0])*4;
   } else if(tMax == t0[1]){ //Plano XZ
      return (tm[0]<t0[1])*1+(tm[2]<t0[1])*4;
   } else{ //Plano XY
      return (tm[0]<t0[2])*1+(tm[1]<t0[2])*2;
   }
   return 8;
}

int Ray::newNode(Vector3 t, Vector3 v){
   real tMin = t[0];
   int j=0;
   for(int i=1; i<3; i++){
      if(t[i]<tMin){
         tMin = t[i];
         j = i;
      }
   }

   return v[j];
}

void Ray::procSubtree(Vector3 t0, Vector3 t1, OctreeNode* node, std::vector<OctreeLeaf*>* colisions){
   if(node == nullptr) return;

   Vector3 tm;

   int currNode;

   if(t1[0] < 0.0 || t1[1] < 0.0 || t1[2] < 0.0)
      return;

   if(node->isLeaf()){
      colisions->push_back(dynamic_cast<OctreeLeaf*>(node));
      return;
   }

   tm=0.5*(t0+t1);

   currNode = firstNode(t0,tm);

   do{
      switch(currNode){
         case 0:
            procSubtree(t0,tm, dynamic_cast<OctreeBranch*>(node)->children[0], colisions);
            currNode = newNode(tm, Vector3(4, 2, 1));//newNode(tm[0], 4, tm[1], 2, tm[2], 1);
            break;
         case 1:
            procSubtree(Vector3(t0[0], t0[1], tm[2]), Vector3(tm[0], tm[1], t1[2]), dynamic_cast<OctreeBranch*>(node)->children[1], colisions);
            currNode = newNode(Vector3(tm[0], tm[1], t1[2]), Vector3(5, 3, 8));//newNode(tm[0], 5, tm[1], 3, t1[2], 8);
            break;
         case 2:
            procSubtree(Vector3(t0[0], tm[1], t0[2]), Vector3(tm[0], t1[1], tm[2]), dynamic_cast<OctreeBranch*>(node)->children[2], colisions);
            currNode = newNode(Vector3(tm[0], t1[1], tm[2]), Vector3(6, 8, 3));//newNode(tm[0], 6, t1[1], 8, tm[2], 3);
            break;
         case 3:
            procSubtree(Vector3(t0[0], tm[1], tm[2]), Vector3(tm[0], t1[1], t1[2]), dynamic_cast<OctreeBranch*>(node)->children[3], colisions);
            currNode = newNode(Vector3(tm[0], t1[1], t1[2]), Vector3(7, 8, 8));//newNode(tm[0], 7, t1[1], 8, t1[2], 8);
            break;
         case 4:
            procSubtree(Vector3(tm[0], t0[1], t0[2]), Vector3(t1[0], tm[1], tm[2]), dynamic_cast<OctreeBranch*>(node)->children[4], colisions);
            currNode = newNode(Vector3(t1[0], tm[1], tm[2]), Vector3(8, 6, 5));//newNode(t1[0], 8, tm[1], 6, tm[2], 5);
            break;
         case 5:
            procSubtree(Vector3(tm[0], t0[1], tm[2]), Vector3(t1[0], tm[1], t1[2]), dynamic_cast<OctreeBranch*>(node)->children[5], colisions);
            currNode = newNode(Vector3(t1[0], tm[1], t1[2]), Vector3(8, 7, 8));//newNode(t1[0], 8, tm[1], 7, t1[2], 8);
            break;
         case 6:
            procSubtree(Vector3(tm[0], tm[1], t0[2]), Vector3(t1[0], t1[2], tm[2]), dynamic_cast<OctreeBranch*>(node)->children[6], colisions);
            currNode = newNode(Vector3(t1[0], t1[1], tm[2]), Vector3(8, 8, 7));//newNode(t1[0], 8, t1[1], 8, tm[2], 7);
            break;
         case 7:
            procSubtree(tm, t1, dynamic_cast<OctreeBranch*>(node)->children[7], colisions);
            currNode = 8;
            break;
      }
   }while(currNode<8);
}

void Ray::rayParameter(Octree *oct, std::vector<OctreeLeaf*> *colisions){
   Vector3 t0;
   Vector3 t1;

   Vector3 pivot = oct->root->aabb.center;
   Vector3 size = oct->root->aabb.halfwidth;

   real tmp;

   for(int i=0; i<3; i++){
      tmp = pivot[i]-origin[i];

      t0[i]=(tmp-size[i])/dir[i];
      t1[i]=(tmp+size[i])/dir[i];
   }

   if(t1.minCoeff() > t0.maxCoeff())
      procSubtree(t0,t1, oct->root, colisions);
}

int Ray::intersectOctree(Octree *octree, std::vector<OctreeLeaf*> *colisions){
   colisions->clear();
   rayParameter(octree, colisions);
   return 0;
}

#endif

