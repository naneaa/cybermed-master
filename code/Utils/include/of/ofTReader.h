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

#ifdef OF_THREADS

#ifndef OFTREADER_H
#define OFTREADER_H

#include "ofMacros.h"
#include "ofMesh.h"

namespace of
{

/**
	@class		ofTReader 
	@file		ofTReader.h 
	@short		Ready files model	
	
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 
 */		

template <class sTraits> class ofTReader
{
public:
	typedef typename sTraits::ids ids;
	
	typedef typename _Traits::sMesh		sMesh;

	/** Construtor */
	ofTReader(int threads_vertices, int threads_cells);
	/** Destrutor */
	virtual ~ofTReader();

	void setNumberOfThreads(int threads_vertices, int threads_cells);

	virtual bool read(sMesh* malha, char* xml) = 0;

protected:

	struct ofTReaderData
	{
		char *str;
	
		ids id;
		ids start;
		ids end;
		sMesh *malha;
		ofXmlParser *config;
		
	};

	int nthreadsv, nthreadsc;
};

template <class sTraits> ofTReader<sTraits>::ofTReader(int threads_vertices, int threads_cells)
{
	setNumberOfThreads(threads_vertices, threads_cells);
}

template <class sTraits> ofTReader<sTraits>::~ofTReader()
{
}

template <class sTraits> void ofTReader<sTraits>::setNumberOfThreads(int threads_vertices, int threads_cells)
{
	OF_ASSERT(threads_vertices > 0);
	OF_ASSERT(threads_cells > 0);

	nthreadsv = threads_vertices;
	nthreadsc = threads_cells;
}

}

#endif
#endif
