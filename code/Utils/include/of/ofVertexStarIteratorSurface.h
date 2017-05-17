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

#ifndef OFVERTEXSTARITERATORSURFACE_H
#define OFVERTEXSTARITERATORSURFACE_H

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofSing.h"
#include "ofIterator.h"
#include "ofList.h"

namespace of
{

#define SCELL typename ofVertexStarIteratorSurface<_Traits>::sCell
#define IDS typename ofVertexStarIteratorSurface<_Traits>::ids

/**
	@class		ofVertexStarIteratorSurface 
	@file		ofVertexStarIteratorSurface.h 
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 */

template <class _Traits> class ofVertexStarIteratorSurface : public ofIterator<_Traits>
{
public:
	
	typedef typename _Traits::sCell 	sCell;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::ids 		ids;

	typedef ofSing<_Traits>				sSing;
	typedef typename _Traits::sMesh		sMesh;

	ofVertexStarIteratorSurface(sMesh *_mesh);
	
	~ofVertexStarIteratorSurface();
	
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
	
	ofList<ids> lista, flags;
	
	int status, is;
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior

	void addNeighbor();
};

template <class _Traits> ofVertexStarIteratorSurface<_Traits>::ofVertexStarIteratorSurface(sMesh *_mesh)
: ofIterator<_Traits>(_mesh)
{
	is = iatu = iinit = iv = -1;
	status = 0;
	v = NULL;
}

template <class _Traits> ofVertexStarIteratorSurface<_Traits>::~ofVertexStarIteratorSurface()
{
}

template <class _Traits> bool ofVertexStarIteratorSurface<_Traits>::initialize(ids init)
{
	OF_ASSERT(init >= 0);

	iv = init;
	v = this->mesh->getVertex(iv);

	status = 1;
	
	OF_ASSERT(v->inMesh());
	
	iatu = iinit = is = -1;
	
	atu = NULL;
	
	lista.clear();
	flags.clear();
	
	return ++(*this);
}

template<class _Traits> bool ofVertexStarIteratorSurface<_Traits>::operator++()
{
	if(status == 1)
	{
		if(iatu < 0)
		{
			if(is < 0)
			{
				is = 0;
				iatu = v->getSingCell(is);
				
				OF_ASSERT(iatu >= 0);
				
				atu = this->mesh->getCell(iatu);
				OF_ASSERT( (atu) && (atu->inMesh()) );
				
				flags.insert(iatu);
			
				addNeighbor();
				
				iinit = iatu;
			}
		}
		else
		{
			OF_ASSERT( atu->getVertexIndex(iv) >= 0);
			
			if(lista.empty())
			{
				is++;
				iatu = v->getSingCell(is);
				
				if(iatu >= 0)
				{
					//OF_ASSERT(!flags.inList(iatu));
					lista.insert(iatu);
					flags.insert(iatu);
				}
				else
				{
					atu = NULL;
					iatu = -1;
					status = 3;
					return false;
				}				
			}
			
			iatu  = lista.first();
			lista.erase(0);
				
			atu = this->mesh->getCell(iatu);
			OF_ASSERT( (atu) && (atu->inMesh()) );

			addNeighbor();
		}
		
		return true;
	}
	else
		return false;
}

template<class _Traits> void ofVertexStarIteratorSurface<_Traits>::addNeighbor()
{
	ids temp;
	
	temp = atu->getMateId((atu->getVertexIndex(iv)+1)%3);
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
	temp = atu->getMateId((atu->getVertexIndex(iv)+2)%3);
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}

	
	OF_ASSERT( atu->getVertexIndex(iv) >= 0);
}

template<class _Traits> SCELL* ofVertexStarIteratorSurface<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* ofVertexStarIteratorSurface<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS ofVertexStarIteratorSurface<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool ofVertexStarIteratorSurface<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool ofVertexStarIteratorSurface<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif 
