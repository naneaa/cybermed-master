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

#ifndef OFCELL2D_H
#define OFCELL2D_H

#include "ofMacros.h"
#include "ofCell.h"

namespace of
{

/**
@class		ofCell2D 
@file		ofCell2D.h 
@short
	Base class of triangle

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0
@date		2007, July
*/
template <class _Traits> class ofCell2D : public ofCell<3,_Traits>
{
public:

	 /** Constructor 
	 * 
	 * @param void
	 *  
	 */
	ofCell2D();

	/** Destructor 
	 * 
	 * @param void
	 *  
	 */
	virtual ~ofCell2D();
};

template <class _Traits> ofCell2D<_Traits>::ofCell2D()
{
}

template <class _Traits> ofCell2D<_Traits>::~ofCell2D()
{
}

}

#endif
