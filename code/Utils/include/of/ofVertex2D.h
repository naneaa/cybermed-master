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

#ifndef OFVERTEX2D_H
#define OFVERTEX2D_H

#include "ofMacros.h"
#include "ofSingularVertex.h"

namespace of
{
	
/**
	@class		ofVertex2D 
	@file		ofVertex2D.h 
	@short		
				Base class of 2D vertex
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July

	*/

template <class _Traits> class ofVertex2D : public ofSingularVertex<2,_Traits>
{
public:

	typedef typename _Traits::space space;

	/* Constructor */
	ofVertex2D();
	ofVertex2D(space x, space y);
	
	/* Destructor */
	~ofVertex2D();
};

template <class _Traits> ofVertex2D<_Traits>::ofVertex2D()
{
}

template <class _Traits> ofVertex2D<_Traits>::ofVertex2D(space x, space y)
{
	this->setCoord(0,x);
	this->setCoord(1,y);
}


template <class _Traits> ofVertex2D<_Traits>::~ofVertex2D()
{
}

}

#endif
