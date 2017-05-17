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

#ifndef OFVECTOR_H
#define OFVECTOR_H

#include "ofMacros.h"

namespace of
{

/**
	@class		ofVector 
	@file		ofVector.h 
	@short		
				Base Vector
							
				This is a block allocation version of vector with free space management

	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July

 */		
	
template <class T, class ids> class ofVector
{
public:

	/**	
	 * Constructor
	 * 
	 * @param ids block_size the size of each block (The maximum capacity of vector if : block_size * block_size)
	 */
	ofVector(ids block_size);
	
	/**	
	 * Destructor
	 */
	~ofVector();
	
	/** 
	 * Return the specified element
	 * 
	 * @param ids index the position of element
	 * @return T& the specified element
	 */
	T& operator[](ids index);
	
	/**	
	 * Return a free position in vector
	 * @param void
	 * @return ids  a free position in vector
	 */
	ids getFree();

	/**	
	 * Define the number of elements in vector
	 * 
	 * 	(DONT USE)
	 */
	void setSize(ids size);
	
	/**	
	 * Return the number of elements in vector
	 * @param void
	 * @return ids the number of elements in vector
	 */
	ids getSize();
	
	/**	
	 * Return the maximum position in vector
	 * @param void
	 * @return ids the maximum position in vector
	 */
	ids getMaxId();

	/**	
	 * Delete a position in vector
	 * 
	 * @param ids index the position that will be deleted
	 * @return bool if this position was deleted
	 */
	bool free(ids index);
	
private:
	
	T** vetor;		/**< store the vector */
	int block;		/**< the block size*/
	
	ids  nt;		/**< number of elements in the vector */
	ids ntmax;		/**< max number of elements in the vector */
	ids first;		/**< first element in the vector */
	ids last;		/**< last element in the vector */
 	bool hasfree;	/**< if the vector has free positions */
};

template <class T, class ids> ofVector<T,ids>::ofVector(ids block_size)
{
	OF_ASSERT(block_size > 0);
	block = block_size;
	
	vetor = new T*[block];

	OF_ASSERT(vetor);

	for(ids off1=0; off1 < block; off1++)
		vetor[off1] = NULL;
		
	nt = ntmax = 0;
	hasfree = false;
}

template <class T, class ids> ofVector<T,ids>::~ofVector()
{
	for(ids off1=0; off1 < block; off1++)
		if(vetor[off1])
			delete [] vetor[off1];
		
		delete [] vetor;
}

template <class T, class ids> T& ofVector<T,ids>::operator [](ids index)
{
	OF_ASSERT(index >= 0);

	if(vetor[index / block])
 		return vetor[index / block][index % block];
	else
	{
		vetor[index / block] = new T[block];
		OF_ASSERT(vetor[index / block]);
		return vetor[index / block][index % block];
	}
}

template <class T, class ids> ids ofVector<T,ids>::getFree()
{
	ids i;
	
	if (!hasfree)
	{
		i = ntmax;
		ntmax++;
	}
	else
	{
		i = first;
		
		if(last == first)
			hasfree = false;
		else
#ifdef OF_THREADS
			first = (*this)[i].getPosition(false);
#else
			first = (*this)[i].getPosition();
#endif
	}

#ifdef OF_THREADS
	(*this)[i].setInMesh(true, false);
#else
	(*this)[i].setInMesh(true);
#endif
	nt++;

	return i;
}
	
template <class T, class ids> void ofVector<T,ids>::setSize(ids size)
{
	if(ntmax < size)
		ntmax = size; 
	
	nt = size;
}

template <class T, class ids> ids ofVector<T,ids>::getSize()
{
	return nt; 
}

template <class T, class ids> ids ofVector<T,ids>::getMaxId()
{
	return ntmax;
}

template <class T, class ids> bool ofVector<T,ids>::free(ids index)
{
	OF_ASSERT(index >= 0);
	
	T* v = &(*this)[index];
	
	OF_ASSERT(v->inMesh());
	if(hasfree)
	{
#ifdef OF_THREADS
		v->setPosition(first, false);
#else
		v->setPosition(first);
#endif
		first = index;
	}
	else
	{
#ifdef OF_THREADS
	v->setInMesh(false, false);
#else
	v->setInMesh(false);
#endif
		hasfree = true;
		first = index;
		last = first;
	}
	nt--;
	
	return true;
}

}

#endif
