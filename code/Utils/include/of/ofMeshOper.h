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

#ifndef OFMESHOPER_H
#define OFMESHOPER_H

#include "ofMacros.h"
#include "ofMesh.h"

namespace of
{

/**
 @class		ofMeshOper 
 @file		ofMeshOper.h 
 @short 
	 	Base Operation Class for ofMesh
 			
  		_Traits must have: ids, sMesh 
 
 @author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
 @version	1.0 
 @date		2007, July
 
*/

template<class _Traits> class ofMeshOper
{
public:

	typedef typename _Traits::ids	ids;

	typedef typename _Traits::sMesh		sMesh;

protected:

	/* Constructor */
	ofMeshOper(sMesh *_mesh);

	/* Destrutor */
	~ofMeshOper();
	
	sMesh *mesh;
};

template <class _Traits> ofMeshOper<_Traits>::ofMeshOper(sMesh *_mesh)
{
	OF_ASSERT(_mesh);
	mesh = _mesh;
}

template <class _Traits> ofMeshOper<_Traits>::~ofMeshOper()
{
}

}

#endif
