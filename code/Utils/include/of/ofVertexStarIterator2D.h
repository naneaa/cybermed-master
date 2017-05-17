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

#ifndef OFVERTEXSTARITERATOR2D_H
#define OFVERTEXSTARITERATOR2D_H

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofSing.h"
#include "ofIterator.h"

namespace of
{

#define SCELL typename ofVertexStarIterator2D<_Traits>::sCell
#define IDS typename ofVertexStarIterator2D<_Traits>::ids

/**
	@class		ofVertexStarIterator2D 
	@file		ofVertexStarIterator2D.h 
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 */

template <class _Traits> class ofVertexStarIterator2D : public ofIterator<_Traits>
{
public:
	
	typedef typename _Traits::sCell 	sCell;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::ids 		ids;

	typedef ofSing<_Traits>				sSing;
	typedef typename _Traits::sMesh		sMesh;

	ofVertexStarIterator2D(sMesh *_mesh);
	
	~ofVertexStarIterator2D();
	
	bool initialize(ids init);

	bool finish();
	bool notFinish();
	
	bool operator++();

	sCell *operator->();
	sCell *operator*();

	ids operator&();
	
private:

	ids iatu, iinit, iv;
	sCell *atu;
	sVertex *v;
	
	int status, is;
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior
};

template <class _Traits> ofVertexStarIterator2D<_Traits>::ofVertexStarIterator2D(sMesh *_mesh)
: ofIterator<_Traits>(_mesh)
{
	is = iatu = iinit = iv = -1;
	status = 0;
	v = NULL;
}

template <class _Traits> ofVertexStarIterator2D<_Traits>::~ofVertexStarIterator2D()
{
}

template <class _Traits> bool ofVertexStarIterator2D<_Traits>::initialize(ids init)
{
	OF_ASSERT(init >= 0);

	iv = init;
	v = this->mesh->getVertex(iv);
	
	status = 1;
	
	OF_ASSERT(v->inMesh());
	
	iatu = iinit = -1;
	
	atu = NULL;
	is = -1;
	
	return ++(*this);
}

template<class _Traits> bool ofVertexStarIterator2D<_Traits>::operator++()
{
	if(status == 1)
	{
		if(iatu < 0)
		{
			if(is < 0)
			{
				is = 0;
				iatu = v->getSingCell(is);
				atu = this->mesh->getCell(iatu);
				
				OF_ASSERT( (atu) && (atu->inMesh()) );
				
				iinit = iatu;
			}
		}
		else
		{
			OF_ASSERT( atu->getVertexIndex(iv) >= 0);
			
			iatu  = atu->getMateId( (atu->getVertexIndex(iv) + 1)%3 );
			
			if(iatu >=0)
			{
				atu = this->mesh->getCell(iatu);
			
				OF_ASSERT( atu->getVertexIndex(iv) >= 0);
				
				if(iatu == iinit)
				{
					atu = NULL;
					iatu = -1;
					status = 3;
					
					return false;
				}
			}
			else
			{
				is++;
				iatu = v->getSingCell(is);
				
				if(iatu >= 0)
				{
					atu = this->mesh->getCell(iatu);
				
					OF_ASSERT( (atu) && (atu->inMesh()) );
				}
				else
				{
					atu = NULL;
					iatu = -1;
					status = 3;
					return false;
				}
			}
		}
		
		return true;
	}
	else
		return false;
}

template<class _Traits> SCELL* ofVertexStarIterator2D<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* ofVertexStarIterator2D<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS ofVertexStarIterator2D<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool ofVertexStarIterator2D<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool ofVertexStarIterator2D<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif 
