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

#ifndef OFCELL_H
#define OFCELL_H

#include "ofMacros.h"
#include "ofBase.h"

namespace of
{

#define IDS typename ofCell<size,_Traits>::ids

/**
@class		ofCell 
@file		ofCell.h 
@short
	Base class of cell

	size is the dimension of cell:
 	3 - triangle
 	4 - tetrahedron
 
 	_Traits must have typenames: 	ids

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0
@date		2007, July
*/
template <int size, class _Traits> class ofCell : public ofBase<_Traits>
{
public:

	typedef typename _Traits	::ids ids;
	
	/**	
	 * Constructor, initialize vertices and mates ids
	 * 	
	 * @param void
	 * 	
	 */
	ofCell();

	/** 
	 * Destructor 
	 * 
	 * @param void
	 *  
	 */
	virtual ~ofCell();
	
	/** 
	 * Return the mate cell id of the specified index
	 * 
	 * @param int index position of mate cell
	 * @return ids the mate cell id of the specified index
	 */
	ids	getMateId(int index OF_DMUTEXVD);
	
	/**	
	 * Return the vertex id of the specified index
	 * 
	 * @param int index position of vertex
	 * @return ids the vertex id of the specified index
	 */
	ids	getVertexId(int index OF_DMUTEXVD);
	
	/** 
	 * Define the mate cell id of the specified index
	 * 
	 * @param int index position of mate cell
	 * @param ids cell the mate cell id
	 * @return void
	 */
	void setMateId(int index, ids cell OF_DMUTEXVD);
	
	/** 
	 * Define the vertex id of the specified index
	 * 
	 * @param int index position of vertex
	 * @param ids vertex the vertex id
	 * @return void
	 */
	void setVertexId(int index, ids vertex OF_DMUTEXVD);
	
	/**	
	 * Reset the mate cells ids and define -1 for all positions
	 * 
	 * @param void
	 * @return void
	 */
	void clearMates(OF_DMUTEXD);

	/**	
	 * Return the position of the specified vertex id
	 * 
	 * @param ids vertex the vertex id
	 * @return int the position of the specified vertex id
	 */
	int getVertexIndex(ids vertex OF_DMUTEXVD);
	
	/**	
	 *Return the position of the specified mate cell id
	 * 
	 * @param ids cell the mate cell id
	 * @return int the position of the specified mate cell id
	 */
	int	getMateIndex(ids cell OF_DMUTEXVD);
	
	/**	
	 * Return the opposite cell id of the specified vertex id
	 * 	
	 * @param ids cell the vertex id
	 * @return ids the opposite cell id of the specified vertex id
	 */
	ids	getMateVertexId(ids vertex OF_DMUTEXVD);
	
	/**	
	 * Return the opposite vertex id of the specified mate cell id
	 * 	
	 * @param ids cell the mate cell id
	 * @return ids the opposite vertex id of the specified mate cell id
	 */
	ids	getVertexMateId(ids cell OF_DMUTEXVD);

	
	/**	
	 * Return the dimension of this cell
	 * @param void
	 * @return int the dimension of this cell
	 */
	static inline int getDimension(){ return size-1;};
	
private:

	ids vertices[size];		/**< the vertices'ids */
	ids mates[size];		/**< the vertices mates'ids */
};

template <int size, class _Traits> ofCell<size,_Traits>::ofCell()
{
#ifdef OF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif
	
	for(int i = 0; i < size; i++)
	{
		vertices[i] = -1;
		mates[i] = -1;
	}
	
#ifdef OF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <int size, class _Traits> ofCell<size,_Traits>::~ofCell()
{
}

template <int size, class _Traits> IDS ofCell<size,_Traits>::getMateId(int index OF_DMUTEXV)
{
	OF_ASSERT((index >= 0)&&(index < size));
	
	OF_LOCK(smutex);
	
	ids temp = mates[index];

	OF_UNLOCK(smutex);
	
	return temp;
}

template <int size, class _Traits> IDS ofCell<size,_Traits>::getVertexId(int index OF_DMUTEXV)
{
	OF_ASSERT((index >= 0)&&(index < size));

	OF_LOCK(smutex);
	
	ids temp = vertices[index];
	
	OF_UNLOCK(smutex);
	
	return temp;
}

template <int size, class _Traits> void ofCell<size,_Traits>::setMateId(int index, ids cell OF_DMUTEXV)
{
	OF_ASSERT((index >= 0)&&(index < size));

	OF_LOCK(smutex);

	mates[index] = cell;

	OF_UNLOCK(smutex);
}

template <int size, class _Traits> void ofCell<size,_Traits>::setVertexId(int index, ids vertex OF_DMUTEXV)
{
	OF_ASSERT((index >= 0)&&(index < size));

	OF_LOCK(smutex);

	vertices[index] = vertex;
	
	OF_UNLOCK(smutex);
}

template <int size, class _Traits> IDS ofCell<size,_Traits>::getMateVertexId(ids vertex OF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getVertexId(i OF_MUTEXV) == vertex)
			return getMateId(i OF_MUTEXV);
			
	return -1;
}

template <int size, class _Traits> IDS ofCell<size,_Traits>::getVertexMateId(ids cell OF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getMateId(i OF_MUTEXV) == cell)
			return getVertexId(i OF_MUTEXV);
			
	return -1;
}

template <int size, class _Traits> int ofCell<size,_Traits>::getMateIndex(ids cell OF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getMateId(i OF_MUTEXV) == cell)
			return i;
			
	return -1;
}

template <int size, class _Traits> void ofCell<size,_Traits>::clearMates(OF_DMUTEX)
{
	for(int i = 0; i < size; i++)
		setMateId(i,-1 OF_MUTEXV);
}

template <int size, class _Traits> int ofCell<size,_Traits>::getVertexIndex(ids vertex OF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getVertexId(i OF_MUTEXV) == vertex)
			return i;
			
	return -1;
}

#undef IDS

}

#endif
