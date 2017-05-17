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

#ifndef OFREADER_H
#define OFREADER_H

#include "ofMacros.h"
#include "ofMesh.h"

namespace of
{

/**
	@class		ofReader 
	@file		ofReader.h 
	@short
			Abstract class that define methods for ready of files

	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 
 */			

template <class _Traits> class ofReader
{
public:
	
	typedef typename _Traits::sMesh		sMesh;

	ofReader();
	/** Destructor*/
	virtual ~ofReader();
	
	virtual bool read(sMesh* malha, const char* filename) = 0;
};

template <class _Traits> ofReader<_Traits>::ofReader()
{
}

template <class _Traits> ofReader<_Traits>::~ofReader()
{
}

}

#endif
