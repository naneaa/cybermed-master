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

#ifndef OFSING_H
#define OFSING_H

#include "ofMacros.h"

namespace of
{

#define SSING typename ofSing<_Traits>::sSing
#define IDS typename ofSing<_Traits>::ids


/**
	@class		ofSearchDIDO 
	@file		ofSearchDIDO.h 
	@short
			Base Class of singular component in vertex
			
			_Traits must have: ids, sSing

	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 
 */	

template <class _Traits> class ofSing
{
public:

	typedef typename _Traits::ids ids;
	
	typedef ofSing<_Traits> sSing;

	/** Constructor */
	ofSing();

	/** Destrutor */
	~ofSing();
	
	/**	Return the next singular component
	 */
	sSing* getNext();

	/**	Define the next singular component
	 */
	void setNext(sSing* _next);
	
	/**	Return the cell of this singular component
	 */
	ids getCell();

	/**	Define the cell of this singular component
	 */
	void setCell(ids _cell);	
	
private:
	ids cell;
	sSing *next;
};

template <class _Traits> ofSing<_Traits>::ofSing()
{
	next = NULL;
}

template <class _Traits> ofSing<_Traits>::~ofSing()
{
}

template <class _Traits> SSING* ofSing<_Traits>::getNext()
{
	return next;
}

template <class _Traits> void ofSing<_Traits>::setNext(sSing* _next)
{
	next = _next;
}

template <class _Traits> IDS ofSing<_Traits>::getCell()
{
	return cell;
}

template <class _Traits> void ofSing<_Traits>::setCell(ids _cell)
{
	OF_ASSERT(_cell >= 0);
	
	cell = _cell;
}

#undef IDS
#undef SSING

}

#endif
