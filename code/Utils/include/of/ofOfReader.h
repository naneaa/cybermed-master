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

#ifndef OFOFREADER_H
#define OFOFREADER_H

#include <fstream>

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofBinaryIO.h"
#include "ofReader.h"

using namespace std;

namespace of
{

/**
	@class		ofOfReader 
	@file		ofOfReader.h 

	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 
 */	
	
template <class _Traits> class ofOfReader : public ofReader<_Traits>
{
public:
	typedef typename _Traits::space 	space;
	typedef typename _Traits::ids 		ids;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::sCell 	sCell;
	
	typedef typename _Traits::sMesh		sMesh;
	typedef ofBinaryIO<_Traits> 		sBinaryIO;
	
	ofOfReader();
	~ofOfReader();
	
	virtual bool read(sMesh* malha, const char* filename);

private:
	sBinaryIO io;
	
	bool checkVersion(ifstream &pf);
	bool readHeader(ifstream &pf, ids &nv, ids &nc);
	
	bool reader(ifstream &pf, sMesh* malha);
};

template <class _Traits> ofOfReader<_Traits>::ofOfReader()
{
}

template <class _Traits> ofOfReader<_Traits>::~ofOfReader()
{
}

template <class _Traits> bool ofOfReader<_Traits>::read(sMesh* malha, const char *filename)
{
	OF_ASSERT(filename);
	OF_ASSERT(malha);	
	
	ifstream pf(filename, ios_base::in | ios_base::binary);
	
	if( pf.is_open())
	{
			if(! reader(pf, malha))
				return false;
		
			pf.close();
	}
	else
		return false;
	
	return true;
}

template <class _Traits> bool ofOfReader<_Traits>::checkVersion(ifstream &pf)
{
	char c;
	
	pf.read(&c, sizeof(char)); if(c != 'O') return false;
	pf.read(&c, sizeof(char)); if(c != 'F') return false;
	pf.read(&c, sizeof(char)); if(c != '-') return false;
	pf.read(&c, sizeof(char)); if(c != 'B') return false;
	pf.read(&c, sizeof(char)); if(c != 'I') return false;
	pf.read(&c, sizeof(char)); if(c != 'N') return false;
	pf.read(&c, sizeof(char)); if(c != 'A') return false;
	pf.read(&c, sizeof(char)); if(c != 'R') return false;
	pf.read(&c, sizeof(char)); if(c != 'Y') return false;
	pf.read(&c, sizeof(char)); if(c != '-') return false;
	pf.read(&c, sizeof(char)); if(c != 'V') return false;
	pf.read(&c, sizeof(char)); if(c != '1') return false;
	pf.read(&c, sizeof(char)); if(c != '.') return false;
	pf.read(&c, sizeof(char)); if(c != '0') return false;
	pf.read(&c, sizeof(char)); if(c != '0') return false;
	pf.read(&c, sizeof(char)); if(c != '1') return false;

	return true;	
}

template <class _Traits> bool ofOfReader<_Traits>::readHeader(ifstream &pf, ids &nv, ids &nc)
{
	if( ( io.idsLoad(pf) <= (int)sizeof(space) ) && ( io.idsLoad(pf) <= (int)sizeof(ids)) )
	{
		if( ( io.idsLoad(pf) == sVertex::getDimension() ) && ( io.idsLoad(pf) == sCell::getDimension() ) )
		{
			nv = io.idsLoad(pf);
			nc = io.idsLoad(pf);
		}
		else
			return false;
	}
	else
		return false;

	return true;
}


template <class _Traits> bool ofOfReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{

	space coords[3];
	int i, nv, j, nc, k;
	int auxvtx[sCell::getDimension() + 1], auxop[sCell::getDimension() + 1];

	if(!checkVersion(pf))
		return false;
	
	if(!readHeader(pf, nv, nc))
		return false;
		
	OF_ASSERT(nv > 0);
	
	for (i=0; i<nv; i++)
	{
		for(j = 0; j < sVertex::getDimension(); j++)
			coords[j] = io.spaceLoad(pf);

		malha->addVertex(coords);
	}

	OF_ASSERT(nc >= 0);
		
	for (i=0; i<nc; i++)
	{
		for (j=0; j<= sCell::getDimension() ; j++)
		{
			k = io.idsLoad(pf);
			OF_ASSERT((k >= 0)&&(k < nv));
			auxvtx[j] = k;
		}
		
		for (j=0; j<= sCell::getDimension() ; j++)
		{
			k = io.idsLoad(pf);
			auxop[j] = k;
		}
		
		malha->addCell(auxvtx, auxop);
	}
	
	sVertex *v;
	ids n;
	
	for (i=0; i<nv; i++)
	{
		k = io.idsLoad(pf);
		
		v = malha->getVertex(i); 
		
		for(j=0; j < k; j++)
		{
			n = io.idsLoad(pf);
			v->addSing(n);
		}
	}	
	
	return true;
}

}

#endif
