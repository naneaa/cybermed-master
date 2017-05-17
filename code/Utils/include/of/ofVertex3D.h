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

#ifndef OFVERTEX3D_H
#define OFVERTEX3D_H

#include "ofMacros.h"
#include "ofSingularVertex.h"

namespace of
{
	
/**
	@class		ofVertex3D 
	@file		ofVertex3D.h 
	@short		
				Base class of 3D vertex
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July

 */	

template <class _Traits> class ofVertex3D : public ofSingularVertex<3,_Traits>
{
public:

	typedef typename _Traits::space space;

	 /** Constructor 
	 * 
	 * @param void
	 *  
	 */
	ofVertex3D();
	
	 /** Constructor
	 * 
	 * @param space x vertex coordinate x
	 * @param space y vertex coordinate y
	 * @param space z vertex coordinate z
	 *  
	 */
	ofVertex3D(space x, space y, space z);
	
	 /** Destructor 
	 * 
	 * @param void
	 *  
	 */
	~ofVertex3D();
};

template <class _Traits> ofVertex3D<_Traits>::ofVertex3D()
{
}

template <class _Traits> ofVertex3D<_Traits>::ofVertex3D(space x, space y, space z)
{
	this->setCoord(0,x);
	this->setCoord(1,y);
	this->setCoord(2,z);
}

template <class _Traits> ofVertex3D<_Traits>::~ofVertex3D()
{
}

}

#endif
