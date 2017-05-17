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

#ifndef OFVERTEX_H
#define OFVERTEX_H

#include "ofMacros.h"
#include "ofBase.h"

namespace of
{

#define SPACE typename ofVertex<size,_Traits>::space

/**
	@class		ofVertex
	@file		ofVertex.h
	@short
		Base class of vertex
	
		size is the dimension of vertex:
		2 - 2D vertex (x,y)
		3 - 3D vertex (x,y,z)
	
		_Traits must have typenames: 	space 
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
*/

template <int size, class _Traits> class ofVertex : public ofBase<_Traits>
{
public:
	
	typedef typename _Traits::space space;
	
  	/** Constructor 
	 * 
	 * @param void
	 *  
	 */
	ofVertex();

  	/** Destructor 
	 * 
	 * @param void
	 *  
	 */
	virtual ~ofVertex();
	
	/**	
	 * Return the specified coordinate
	 * 
	 * @param int pos index of coordinate
	 * @return space the specified coordinate
	 * 
	 */
	space getCoord(int pos OF_DMUTEXVD);

	/**	
	 * Return a vector of all coordinates
	 * 
	 * @param void
	 * @return space a vector of all coordinates
	 * 
	 */
	space *getCoords(OF_DMUTEXD);
	
	/**	
	 * Define the specified coordinate value
	 * 
	 * @param int pos index of coordinate
	 * @param space value coordinate value
	 * @return void
	 */
	void setCoord(int pos, space value OF_DMUTEXVD);

	/**	
	 * Define all coordinates values
	 * 
	 * @param space*values vector with coordinates values
	 * @return void
	 */
	void setCoords(space* values OF_DMUTEXVD);
	
	/**	
	 * Return the dimension of the vertex	
	 * 
	 * @param void
	 * @return int the dimension of the vertex	
	 */
	static inline int getDimension(){ return size;};
	
private:

	space coords[size];			/**< the vertices coordinates */
};

template <int size, class _Traits> ofVertex<size,_Traits>::ofVertex()
{
}

template <int size, class _Traits> ofVertex<size,_Traits>::~ofVertex()
{
}

template <int size, class _Traits> SPACE ofVertex<size,_Traits>::getCoord(int pos OF_DMUTEXV)
{
	space c;
	
	OF_ASSERT((pos>=0) && (pos < size));
	
	OF_LOCK(smutex);
	c = coords[pos];
	OF_UNLOCK(smutex);
	
	return c;	
}

template <int size, class _Traits> SPACE* ofVertex<size,_Traits>::getCoords(OF_DMUTEX)
{
	space *c;
	
	OF_LOCK(smutex);
	c = coords;
	OF_UNLOCK(smutex);
	
	return c;	
}

template <int size, class _Traits> void ofVertex<size,_Traits>::setCoord(int pos, space value OF_DMUTEXV)
{
	OF_ASSERT((pos>=0) && (pos < size));

	OF_LOCK(smutex);
	coords[pos] = value;
	OF_UNLOCK(smutex);
}

template <int size, class _Traits> void ofVertex<size,_Traits>::setCoords(space *values OF_DMUTEXV)
{
	OF_LOCK(smutex);
	for(int i = 0; i < size; i++)
		coords[i] = values[i];
	OF_UNLOCK(smutex);
}

#undef SPACE

}

#endif
