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

#ifndef OFBOUNDARYCELLCITERATOR2D_H
#define OFBOUNDARYCELLCITERATOR2D_H

#include "ofMacros.h"
#include "ofIterator.h"

namespace of
{

#define SCELL typename ofBoundaryCellCIterator2D<_Traits>::sCell
#define IDS typename ofBoundaryCellCIterator2D<_Traits>::ids

/**
@class		ofBoundaryCellCIterator2D 
@file		ofBoundaryCellCIterator2D.h 
@short 

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0 
@date		2007, July
 */

template <class _Traits> class ofBoundaryCellCIterator2D : public ofIterator<_Traits>
{
public:
	
	typedef typename _Traits::sCell	 	sCell;
	typedef typename _Traits::ids 		ids;

	typedef typename _Traits::sMesh		sMesh;

	ofBoundaryCellCIterator2D(sMesh *_mesh);
	
	~ofBoundaryCellCIterator2D();
	
	bool initialize(ids init, int edge = -1);

	bool finish();
	bool notFinish();
	
	bool operator++();
	bool operator--();

	sCell *operator->();
	sCell *operator*();

	ids operator&();
	
	int getEdge();

private:

	ids iatu;
	sCell *atu;
	
	int eatu, status;
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior
};

template <class _Traits> ofBoundaryCellCIterator2D<_Traits>::ofBoundaryCellCIterator2D(sMesh *_mesh)
: ofIterator<_Traits>(_mesh)
{
	status = 0;
	iatu = eatu = -1;
	atu = NULL;
}

template <class _Traits> ofBoundaryCellCIterator2D<_Traits>::~ofBoundaryCellCIterator2D()
{
}

template <class _Traits> bool ofBoundaryCellCIterator2D<_Traits>::initialize(ids init, int edge)
{
	OF_ASSERT(init >= 0);

	iatu = init;

	atu = this->mesh->getCell(iatu);
	
	OF_ASSERT(atu->inMesh());
	
	if(edge < 0)
	{
		if(atu->getMateId(0) < 0)
			eatu = 0;
		else if(atu->getMateId(1) < 0)
			eatu = 1;
		else if(atu->getMateId(2) < 0)
			eatu = 2;
	}
	else
		eatu = edge;
	
	status = 1;

	return true;
}

template<class _Traits> bool ofBoundaryCellCIterator2D<_Traits>::operator++()
{
	sCell *tempc = atu;
	int tempe = eatu, iant, itempc = iatu;
	
	if(status == 1)
	{
		
		while(tempc->getMateId((tempe+1)%3) >= 0)
		{
			iant = itempc;
			itempc = tempc->getMateId((tempe+1)%3);
			tempc = this->mesh->getCell(itempc);
			tempe = tempc->getMateIndex(iant);	
		}
		
		eatu = (tempe + 1)%3;
		atu = tempc;
		iatu = itempc;
	}
	else
		return false;
	
	return true;
}

template<class _Traits> bool ofBoundaryCellCIterator2D<_Traits>::operator--()
{
	sCell *tempc = atu;
	int tempe = eatu, iant, itempc = iatu;
	
	if(status == 1)
	{
		
		while(tempc->getMateId((tempe+2)%3) >= 0)
		{
			iant = itempc;
			itempc = tempc->getMateId((tempe+2)%3);
			tempc = this->mesh->getCell(itempc);
			tempe = tempc->getMateIndex(iant);	
		}
		
		eatu = (tempe + 2)%3;
		atu = tempc;
		iatu = itempc;
	}
	else
		return false;
	
	return true;
}

template<class _Traits> SCELL* ofBoundaryCellCIterator2D<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* ofBoundaryCellCIterator2D<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS ofBoundaryCellCIterator2D<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool ofBoundaryCellCIterator2D<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool ofBoundaryCellCIterator2D<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

template<class _Traits> int ofBoundaryCellCIterator2D<_Traits>::getEdge()
{
	if(status != 0)
		return eatu;
	
	return -1;
}

#undef SCELL
#undef IDS

}

#endif 
