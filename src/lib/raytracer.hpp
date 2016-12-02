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

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

#include"aux/math.hpp"
#include"lib/model.hpp"

class Raytracer{
   public:
      //EIGEN_MAKE_ALIGNED_OPERATOR_NEW
      Vector3 eye;         //Camera plane position
      Vector3 up, right;   //Camera plane basis

      Vector3 frustum;  //Convergence point for a viewpoint in perspective

      Model *model;  //Mesh to raytrace

      unsigned resx, resy; //Resolution of the generated image

      std::vector<unsigned> img; //Image data

      bool persp; //Sets perspective(true) or orthogonal(false) view
      bool generateImg; //If true, generate a image

      unsigned rayHitCount[4]; //Count how many rays missed, reflected or hit
   public:
      void run(); //Raytrace and generate mesh image
};

#endif
