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

#ifndef OFCELL3D_H
#define OFCELL3D_H

#include "ofMacros.h"
#include "ofCell.h"

namespace of
{

/**
@class		ofCell3D 
@file		ofCell3D.h 
@short
	Base class of tetrahedron

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0
@date		2007, July
*/
template <class _Traits> class ofCell3D : public ofCell<4,_Traits>
{
public:

	typedef typename _Traits	::ids ids;

	/* Constructor */
	ofCell3D();
	
	/* Destructor */
	virtual ~ofCell3D();
	
	int getRightFaceIndex(ids index1, ids index2);
	int getLeftFaceIndex(ids index1, ids index2);
	
};

template <class _Traits> ofCell3D<_Traits>::ofCell3D()
{
}

template <class _Traits> ofCell3D<_Traits>::~ofCell3D()
{
}

template <class _Traits> int ofCell3D<_Traits>::getRightFaceIndex(ids index1, ids index2)
{
	OF_ASSERT( (index1 >= 0)&&(index1<=3) );
	OF_ASSERT( (index2 >= 0)&&(index2<=3) );
	OF_ASSERT( index1 != index2 );

	if((index1==0)&&(index2==1)) return 3;
	if((index1==1)&&(index2==0)) return 2;
	
	if((index1==0)&&(index2==2)) return 1;
	if((index1==2)&&(index2==0)) return 3;
	
	if((index1==0)&&(index2==3)) return 2;
	if((index1==3)&&(index2==0)) return 1;
	
	if((index1==1)&&(index2==2)) return 3;
	if((index1==2)&&(index2==1)) return 0;
	
	if((index1==1)&&(index2==3)) return 0;
	if((index1==3)&&(index2==1)) return 2;
	
	if((index1==2)&&(index2==3)) return 1;
	if((index1==3)&&(index2==2)) return 0;
	
	return -1;
}

template <class _Traits> int ofCell3D<_Traits>::getLeftFaceIndex(ids index1, ids index2)
{
	OF_ASSERT( (index1 >= 0)&&(index1<=3) );
	OF_ASSERT( (index2 >= 0)&&(index2<=3) );
	OF_ASSERT( index1 != index2 );

	if((index1==0)&&(index2==1)) return 2;
	if((index1==1)&&(index2==0)) return 3;
	
	if((index1==0)&&(index2==2)) return 3;
	if((index1==2)&&(index2==0)) return 1;
	
	if((index1==0)&&(index2==3)) return 1;
	if((index1==3)&&(index2==0)) return 2;
	
	if((index1==1)&&(index2==2)) return 0;
	if((index1==2)&&(index2==1)) return 3;
	
	if((index1==1)&&(index2==3)) return 2;
	if((index1==3)&&(index2==1)) return 0;
	
	if((index1==2)&&(index2==3)) return 0;
	if((index1==3)&&(index2==2)) return 1;
	
	return -1;
}

}

#endif
