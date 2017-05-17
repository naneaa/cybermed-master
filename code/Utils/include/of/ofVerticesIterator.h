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

#ifndef OFVERTICESITERATOR_H
#define OFVERTICESITERATOR_H

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofIterator.h"

namespace of
{

#define SVERTEX typename ofVerticesIterator<_Traits>::sVertex
#define IDS typename ofVerticesIterator<_Traits>::ids

/**
	@class		ofVerticesIterator 
	@file		VerticessIterator.h 
	@short
		Iterator for vertices
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
*/

template <class _Traits> class ofVerticesIterator : public ofIterator<_Traits>
{
public:
	
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::ids 		ids;
	
	typedef typename _Traits::sMesh		sMesh;

	/** Constructor 
	 * 
	 * @param sMesh* _mesh the mesh in which we want to iterate on vertices
	 *  
	 */	
	ofVerticesIterator(sMesh *_mesh);
	
	/** Destructor 
	 * 
	 * @param void
	 *  
	 */
	~ofVerticesIterator();
	
	/** Initialize the operator 
	 * 
	 * @param ids init the vertex we want to start (default zero)
	 * @return bool if it was possible to initialize the iterator
	 *  
	 */
	bool initialize(ids init = 0);

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
	
	/** Decrement operator
	 * 
	 * @param void
	 * @return bool if it was possible to decrement the iterator
	 *  
	 */
	bool operator--();

	/** Pointer operator
	 * 
	 * @param void
	 * @return sVertex* the iterator current vertex
	 *  
	 */
	sVertex *operator->();
	
	/** Pointer operator
	 * 
	 * @param void
	 * @return sVertex* the iterator current vertex
	 *  
	 */	
	sVertex *operator*();

	/** Address operator
	 * 
	 * @param void
	 * @return ids the address of iterator current cell
	 *  
	 */
	ids operator&();	
	
private:
	
	ids iatu, iinit;		/**< the vertex address and the init vertex */
	sVertex *atu;			/**< pointer to vertex */
	
	int status;				/**< 	// 0 - iterator without position
									// 1 - iterator in normal position
									// 2 - iterator in the superior bound
									// 3 - iterator in the inferior bound */
};

template <class _Traits> ofVerticesIterator<_Traits>::ofVerticesIterator(sMesh *_mesh)
: ofIterator<_Traits>(_mesh)
{
	iatu = iinit = -1;
	status = 0;
}

template <class _Traits> ofVerticesIterator<_Traits>::~ofVerticesIterator()
{
}

template <class _Traits> bool ofVerticesIterator<_Traits>::initialize(ids init)
{
	OF_ASSERT(init >= 0);
	
	iinit = init;

	status = 1;
	
	iatu = -1;
	
	atu = NULL;
	
	return ++(*this);
}

template<class _Traits> bool ofVerticesIterator<_Traits>::operator++()
{

	if(status == 1)
	{
		if( this->mesh->getNumberOfVertices() > 0 )
		{
			if(iatu < 0)
			{
				if(iinit < 0)
					iinit = 0;
				else
					if( iinit > this->mesh->getVertexMaxId() )
					{
						status = 3;
						return false;
					};
				
				iatu = iinit;

			}
			else
				iatu++;

			atu = this->mesh->getVertex(iatu);

			while( (!atu->inMesh()) && (iatu + 1 <= this->mesh->getVertexMaxId()) )
			{
				iatu++;
				atu = this->mesh->getVertex(iatu);
			}
			
			if ( !atu->inMesh() )
			{
				status = 3;
				return false;
			}
			
			OF_ASSERT( atu );
						
			return true;
		}
		else
		{
			status = 3;
			return false;
		}
	}
	else
		return false;
}

template<class _Traits> bool ofVerticesIterator<_Traits>::operator--()
{

	if(status == 1)
	{
		if( this->mesh->getNumberOfVertices() > 0 )
		{
			if(iatu < 0)
			{
				if(iinit < 0)
					iinit = this->mesh->getVertexMaxId();
				else
					if( iinit > this->mesh->getVertexMaxId() )
					{
						// status = 3;
						return false;
					};
				
				iatu = iinit;

			}
			else
			{
				if( iatu == 0 )
				{
					status = 2;
					return false;
				}
				else
					iatu--;
			}

			atu = this->mesh->getVertex(iatu);

			while( (!atu->inMesh()) && (iatu - 1 >= 0) )
			{
				iatu--;
				atu = this->mesh->getVertex(iatu);
			}
			
			if ( !atu->inMesh() )
			{
				status = 2;
				return false;
			}
			
			OF_ASSERT( atu );
						
			return true;
		}
		else
		{
			status = 2;
			return false;
		}
	}
	else
		return false;
}

template<class _Traits> SVERTEX* ofVerticesIterator<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SVERTEX* ofVerticesIterator<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS ofVerticesIterator<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool ofVerticesIterator<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool ofVerticesIterator<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SVERTEX
#undef IDS

}

#endif 
