// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#ifndef OFTRAITS_H
#define OFTRAITS_H

#include "ofVertex2D.h"
#include "ofVertex3D.h"
#include "ofCell2D.h"
#include "ofCell3D.h"
#include "ofMesh2D.h"
#include "ofMesh3D.h"
#include "ofMeshSurface.h"
#include "ofMeshQuadSurface.h"
#include "ofMeshNOSurface.h"
#include "ofGeometric.h"
#include "ofTopology.h"

namespace of
{
	
/**
	@file		ofTraits.h 

	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 
 */		
	
struct ofDefault2D
{
	typedef ofDefault2D						sTraits;
	typedef double							space;
	typedef int							ids;
	
	typedef ofVertex2D<sTraits>					sVertex;
	typedef ofCell2D<sTraits>					sCell;

	typedef ofMesh<sTraits>						sMesh;
	typedef ofMesh2D<sTraits>					sOper;

	typedef ofGeometric<sTraits>					sGeometric;
	typedef ofTopology<sTraits>					sTopology;

};

struct ofDefaultLong2D
{
	typedef ofDefaultLong2D						sTraits;
	typedef long double							space;
	typedef long 								ids;
	
	typedef ofVertex2D<sTraits>					sVertex;
	typedef ofCell2D<sTraits>					sCell;

	typedef ofMesh<sTraits>						sMesh;
	typedef ofMesh2D<sTraits>					sOper;

	typedef ofGeometric<sTraits>					sGeometric;
	typedef ofTopology<sTraits>					sTopology;
};

struct ofDefault3D
{
	typedef ofDefault3D							sTraits;
	typedef double								space;
	typedef int									ids;
	
	typedef ofVertex3D<sTraits>					sVertex;
	typedef ofCell3D<sTraits>					sCell;

	typedef ofMesh<sTraits>						sMesh;
	typedef ofMesh3D<sTraits>					sOper;

	typedef ofGeometric<sTraits>				sGeometric;
	typedef ofTopology<sTraits>					sTopology;
};

struct ofDefaultSurface
{
	typedef ofDefaultSurface				sTraits;
	typedef double						space;
	typedef int						ids;
	
	typedef ofVertex3D<sTraits>				sVertex;
	typedef ofCell2D<sTraits>				sCell;

	typedef ofMesh<sTraits>					sMesh;
	typedef ofMeshSurface<sTraits>				sOper;

	typedef ofGeometric<sTraits>				sGeometric;
	typedef ofTopology<sTraits>				sTopology;
};

struct ofDefaultQuadSurface
{
	typedef ofDefaultQuadSurface			sTraits;
	typedef double						space;
	typedef int						ids;
	
	typedef ofVertex3D<sTraits>				sVertex;
	typedef ofCell<4, sTraits>				sCell;

	typedef ofMesh<sTraits>					sMesh;
	typedef ofMeshQuadSurface<sTraits>				sOper;

	typedef ofGeometric<sTraits>				sGeometric;
	typedef ofTopology<sTraits>				sTopology;
};

struct ofDefaultNOSurface
{
	typedef ofDefaultNOSurface					sTraits;
	typedef double								space;
	typedef int									ids;
	
	typedef ofVertex3D<sTraits>					sVertex;
	typedef ofCell2D<sTraits>					sCell;

	typedef ofMesh<sTraits>						sMesh;
	typedef ofMeshNOSurface<sTraits>			sOper;

	typedef ofGeometric<sTraits>				sGeometric;
	typedef ofTopology<sTraits>					sTopology;
};

}

#endif
