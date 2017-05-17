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

#ifndef OFVERTEXSTARITERATOR3D_H
#define OFVERTEXSTARITERATOR3D_H

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofSing.h"
#include "ofIterator.h"
#include "ofList.h"

namespace of
{

#define SCELL typename ofVertexStarIterator3D<_Traits>::sCell
#define IDS typename ofVertexStarIterator3D<_Traits>::ids

/**
	@class		ofVertexStarIterator3D 
	@file		ofVertexStarIterator3D.h 
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 */

template <class _Traits> class ofVertexStarIterator3D : public ofIterator<_Traits>
{
public:
	
	typedef typename _Traits::sCell 	sCell;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::ids 		ids;

	typedef ofSing<_Traits>				sSing;
	typedef typename _Traits::sMesh		sMesh;

	/** Constructor 
	 * 
	 * @param sMesh* _mesh the mesh in which we want to iterate on cells
	 *  
	 */
	ofVertexStarIterator3D(sMesh *_mesh);
	
	/** Destructor 
	 * 
	 * @param void
	 *  
	 */
	~ofVertexStarIterator3D();
	
	/** Initialize the operator 
	 * 
	 * @param ids init the vertex we want to start (default zero)
	 * @return bool if it was possible to initialize the iterator
	 *  
	 */
	bool initialize(ids init);

	/** Return if the iterator is in the end
	 * 
	 * @param void
	 * @return bool if the iterator is in the end
	 *  
	 */
	bool finish();
	
	/** Return if the iterator is not in the end
	 * 
	 * @param void
	 * @return bool if the iterator is not in the end
	 *  
	 */
	bool notFinish();
	
	/** Increment operator
	 * 
	 * @param void
	 * @return bool if it was possible to increment the iterator
	 *  
	 */
	bool operator++();

	/** Pointer operator
	 * 
	 * @param void
	 * @return sCell* the iterator current cell
	 *  
	 */
	sCell *operator->();
	
	/** Pointer operator
	 * 
	 * @param void
	 * @return sCell* the iterator current cell
	 *  
	 */
	sCell *operator*();

	/** Address operator
	 * 
	 * @param void
	 * @return ids the address of iterator current cell
	 *  
	 */
	ids operator&();
	
private:

	ids iatu, iinit, iv; /**< the vertex address, the init vertex and the init cell*/
	sCell *atu;			/**< pointer to vertex */
	sVertex *v;			/**< the vertex on which we are iterating on cell */
	
	
	ofList<ids> lista, flags;	/**< list of indices and flags */
	
	int status, is;				/**< // 0 - iterator without position
									// 1 - iterator in normal position
									// 2 - iterator in the superior bound
									// 3 - iterator in the inferior bound */

	/** Add a  vertex star neighbor
	 * 
	 * @param void
	 * @return void
	 *  
	 */
	void addNeighbor();
};

template <class _Traits> ofVertexStarIterator3D<_Traits>::ofVertexStarIterator3D(sMesh *_mesh)
: ofIterator<_Traits>(_mesh)
{
	is = iatu = iinit = iv = -1;
	status = 0;
	v = NULL;
}

template <class _Traits> ofVertexStarIterator3D<_Traits>::~ofVertexStarIterator3D()
{
}

template <class _Traits> bool ofVertexStarIterator3D<_Traits>::initialize(ids init)
{
	OF_ASSERT(init >= 0);

	iv = init;
	v = this->mesh->getVertex(iv);

	status = 1;
	
	OF_ASSERT(v->inMesh());
	
	iatu = iinit = -1;
	
	atu = NULL;
	is = -1;
	
	lista.clear();
	flags.clear();
	
	return ++(*this);
}

template<class _Traits> bool ofVertexStarIterator3D<_Traits>::operator++()
{
	if(status == 1)
	{
		if(iatu < 0)
		{
			if(is < 0)
			{
				is = 0;
				iatu = v->getSingCell(is);
				
				OF_ASSERT(iatu >=0);
				
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
					OF_ASSERT(!flags.inList(iatu));
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
			
			iatu  = lista.pos(0);
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

template<class _Traits> void ofVertexStarIterator3D<_Traits>::addNeighbor()
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
	temp = atu->getMateId((atu->getVertexIndex(iv)+3)%3);
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
	
	
	OF_ASSERT( atu->getVertexIndex(iv) >= 0);
}

template<class _Traits> SCELL* ofVertexStarIterator3D<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* ofVertexStarIterator3D<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS ofVertexStarIterator3D<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool ofVertexStarIterator3D<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool ofVertexStarIterator3D<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif 
