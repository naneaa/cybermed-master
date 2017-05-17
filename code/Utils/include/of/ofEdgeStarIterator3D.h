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

#ifndef OFEDGESTARITERATOR3D_H
#define OFEDGESTARITERATOR3D_H

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofSing.h"
#include "ofIterator.h"
#include "ofList.h"

namespace of
{

#define SCELL typename ofEdgeStarIterator3D<_Traits>::sCell
#define IDS typename ofEdgeStarIterator3D<_Traits>::ids

/**
@class		ofEdgeStarIterator3D 
@file		ofEdgeStarIterator3D.h 
@short

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0
@date		2007, July
 */

template <class _Traits> class ofEdgeStarIterator3D : public ofIterator<_Traits>
{
public:
	
	typedef typename _Traits::sCell 		sCell;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::ids 		ids;

	typedef ofSing<_Traits>				sSing;
	typedef typename _Traits::sMesh		sMesh;

	ofEdgeStarIterator3D(sMesh *_mesh);
	
	~ofEdgeStarIterator3D();
	
	bool initialize(ids idcell, int index1, int index2);

	bool finish();
	bool notFinish();
	
	bool operator++();

	sCell *operator->();
	sCell *operator*();

	ids operator&();
	
private:

	ids iatu, iinit, iv;
	int ie1, ie2;
	sCell *atu;
	sVertex *v;
	
	ofList<ids> lista, flags;
	
	int status, is;
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior

	void addNeighbor();
};

template <class _Traits> ofEdgeStarIterator3D<_Traits>::ofEdgeStarIterator3D(sMesh *_mesh)
: ofIterator<_Traits>(_mesh)
{
	is = iatu = iinit = iv -1;
	ie1 = ie2 = -1;
	status = 0;
	v = NULL;
}

template <class _Traits> ofEdgeStarIterator3D<_Traits>::~ofEdgeStarIterator3D()
{
}

template <class _Traits> bool ofEdgeStarIterator3D<_Traits>::initialize(ids idcell, int index1, int index2)
{
	OF_ASSERT(idcell >= 0);
	OF_ASSERT((index1 >= 0)&&(index1 <= sCell::getDimension()));
	OF_ASSERT((index2 >= 0)&&(index2 <= sCell::getDimension()));

	ie1 = index1;
	ie2 = index2;
	iinit = idcell;

	status = 1;
	
	iatu = -1;
	
	atu = NULL;
	
	lista.clear();
	flags.clear();
	
	return ++(*this);
}

template<class _Traits> bool ofEdgeStarIterator3D<_Traits>::operator++()
{
	if(status == 1)
	{
		if(iatu < 0)
		{
			atu = this->mesh->getCell(iinit);
			OF_ASSERT( (atu) && (atu->inMesh()) );
				
			flags.insert(iatu);
			
			addNeighbor();
				
			iatu = iinit;
		}
		else
		{
			if(lista.empty())
			{
				atu = NULL;
				iatu = -1;
				status = 3;
				return false;
			}
			else
			{
			
				iatu  = lista.pos(0);
				lista.erase(0);
				
				atu = this->mesh->getCell(iatu);
				OF_ASSERT( (atu) && (atu->inMesh()) );

				addNeighbor();
			}
		}
		
		return true;
	}
	else
		return false;
}

template<class _Traits> void ofEdgeStarIterator3D<_Traits>::addNeighbor()
{
	ids temp;
	
	temp = atu->getLeftFaceIndex(ie1, ie2);
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
	temp = atu->getRightFaceIndex(ie1, ie2);
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
}

template<class _Traits> SCELL* ofEdgeStarIterator3D<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* ofEdgeStarIterator3D<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS ofEdgeStarIterator3D<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool ofEdgeStarIterator3D<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool ofEdgeStarIterator3D<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif 
