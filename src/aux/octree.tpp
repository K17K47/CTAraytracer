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

template <typename T, unsigned N>
OctreeBranch<T,N>::OctreeBranch(Vector3 center, real size, OctreeBranch<T,N>* parentNode){
   Vector3 tmp;
   real halfSz = size/2;
   real quarterSz = size/4;
   parent = parentNode;
   pivot = center;
   sz = size;

   for(int i=0; i<8; i++){
      tmp = center;

      //x
      if( i&1 ){
         tmp[0]+=quarterSz;
      }else{
         tmp[0]-=quarterSz;
      }
      //y
      if( i&2 ){
         tmp[1]+=quarterSz;
      }else{
         tmp[1]-=quarterSz;
      }
      //z
      if( i&4 ){
         tmp[2]+=quarterSz;
      }else{
         tmp[2]-=quarterSz;
      }

      children[i] = new OctreeLeaf<T,N>(tmp, halfSz, this);
   }
}

template <typename T, unsigned N>
bool OctreeBranch<T,N>::isLeaf() {return false;}

template <typename T, unsigned N>
bool OctreeBranch<T,N>::isTerminal(){
   for(int i=0; i<8; i++){
      if(!children[i]->isLeaf()) return false;
   }

   return true;
}

template <typename T, unsigned N>
unsigned OctreeBranch<T,N>::locate(Vector3 pos){
   unsigned idx = 0;

   if((real_abs(pivot[0] - pos[0]) > sz/2) ||
      (real_abs(pivot[1] - pos[1]) > sz/2) ||
      (real_abs(pivot[2] - pos[2]) > sz/2)){
      return 8;
   }

   //x
   if(pivot[0] < pos[0]) idx+=1;
   //y
   if(pivot[1] < pos[1]) idx+=2;
   //z
   if(pivot[2] < pos[2]) idx+=4;

   return idx;
}

template <typename T, unsigned N>
int OctreeBranch<T,N>::insert(T obj, Vector3 pos){
   unsigned idx = locate(pos);

   if(idx==8) return -1;

   if(children[idx]->isLeaf()){
      if(dynamic_cast<OctreeLeaf<T,N>*>(children[idx])->obj.size()!=N){
         dynamic_cast<OctreeLeaf<T,N>*>(children[idx])->obj.push_back(obj);
         dynamic_cast<OctreeLeaf<T,N>*>(children[idx])->objPos.push_back(pos);
         return 0;
      }else{
         split(idx);
         return dynamic_cast<OctreeBranch<T,N>*>(children[idx])->insert(obj, pos);
      }
   }else{
      return dynamic_cast<OctreeBranch<T,N>*>(children[idx])->insert(obj, pos);
   }
}

template <typename T, unsigned N>
int OctreeBranch<T,N>::insert(std::vector<T> obj, std::vector<Vector3> pos){
   for(int i=0; i<obj.size(); i++){
      if(insert(obj[i], pos[i])) return -1;
   }
   return 0;
}


template <typename T, unsigned N>
void OctreeBranch<T,N>::split(unsigned idx){
   OctreeLeaf<T,N> tmp = *dynamic_cast<OctreeLeaf<T,N>*>(children[idx]);
   delete children[idx];
   children[idx] = new OctreeBranch<T,N>(tmp.pivot, tmp.sz, this);
   dynamic_cast<OctreeBranch<T,N>*>(children[idx])->insert(tmp.obj, tmp.objPos);
}

template <typename T, unsigned N>
OctreeLeaf<T,N>::OctreeLeaf(Vector3 center, real size, OctreeBranch<T,N>* parentNode){
   parent = parentNode;
   pivot = center;
   sz = size;
}

template <typename T, unsigned N>
bool OctreeLeaf<T,N>::isLeaf() {return true;}

template <typename T, unsigned N>
Octree<T,N>::Octree(Vector3 center, real sz){
   root = new OctreeBranch<T,N>(center, sz, nullptr);
}

template <typename T, unsigned N>
int Octree<T,N>::build(std::vector<T> obj, std::vector<Vector3> pos){
   return root->insert(obj[i], pos[i]);
}
