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

#ifndef OFWRLREADER_H
#define OFWRLREADER_H

#include <fstream>

#include <cstring>

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofReader.h"

using namespace std;

namespace of
{

/**
	@class		ofWrlReader 
	@file		ofWrlReader.h 
						
	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 */		
	
template <class _Traits> class ofWrlReader : public ofReader<_Traits>
{
public:
	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sVertex sVertex;
	typedef typename _Traits::sCell sCell;
	
	typedef typename _Traits::sMesh		sMesh;
	
	/**	
	 * Constructor
	 * 
	 * @param void
	 */
	ofWrlReader();
	
	/**	
	 * Destructor
	 * 
	 * @param void
	 */
	~ofWrlReader();
	
	/**	
	 * Read the mesh
	 * 
	 * @param sMesh* malha the mesh that will be generated
	 * @param const char* filename the wrl filename
	 * 
	 * @return bool if it was possible to read the file
	 */
	virtual bool read(sMesh* malha, const char* filename);

	/**	
	 * Read the mesh
	 * 
	 * @param sMesh* malha the mesh that will be generated
	 * @param const char* filename the wrl filename
	 * @param int cellDimension the cell dimension
	 * 
	 * @return bool if it was possible to read the file
	 */
	virtual bool read(sMesh* malha, const char* filename, int cellDimension);

private:

	/**	
	 * Read the mesh
	 * 
	 * @param sMesh* malha the mesh that will be generated
	 * @param ifstream& pf the input file stream
	 * 
	 * @return bool if it was possible to read the file
	 */
	bool reader(ifstream &pf, sMesh* malha);

	/**	
	 * Read the mesh
	 * 
	 * @param sMesh* malha the mesh that will be generated
	 * @param ifstream& pf the input file stream
	 * @param int cellDimension the cell dimension
	 * 
	 * @return bool if it was possible to read the file
	 */
	bool reader(ifstream &pf, sMesh* malha, int cellDimension);
};

template <class _Traits> ofWrlReader<_Traits>::ofWrlReader()
{
}

template <class _Traits> ofWrlReader<_Traits>::~ofWrlReader()
{
}

template <class _Traits> bool ofWrlReader<_Traits>::read(sMesh* malha, const char *filename)
{
	OF_ASSERT(filename);
	OF_ASSERT(malha);

	ifstream pf(filename);

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

template <class _Traits> bool ofWrlReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3];
	int j, k;
	int auxvtx[3];
	char c;
	bool comaAtcoordIndex = false;

	OF_ASSERT(auxstr);

	while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
	{
		pf >> auxstr;
	}

	pf >> c;

	if( c == '[' )
	{
		pf >> auxvtx[0];
		pf >> c;
		if( c == ',' )
		{
			pf >> auxvtx[0];
			pf >> c;
			if( c == ',' ) 
			{
				pf >> auxvtx[0];
				pf >> c;
				if( c == ',' ) 
				{
					comaAtcoordIndex = true;
				}
			}
		}
	}

	pf.seekg(0); // rewind

	while( (! pf.eof()) && (strcmp(auxstr,"point") != 0) )
	{
		pf >> auxstr;
	}
	
	if(! pf.eof())
	{
		pf >> c;
		
		if( c == '[')
		{
			while ( c != ']')
			{
				for(j = 0; j < 3; j++)
				{
					pf >> coords[j];

				}
	
				malha->addVertex(coords);

				pf >> c;
				
			}
		}
		else
			return false;

		while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
		{
			pf >> auxstr;
		}

		pf >> c;

		if( c == '[' )
		{
			while ( c != ']')
			{
				for(j = 0; j < 3; j++)
				{
					pf >> auxvtx[j];
					if(comaAtcoordIndex)
						pf >> c;
				}

				malha->addCell(auxvtx);

				pf >> k;
				pf >> c;
			}
		}
		else
			return false;
	}
	else
		return false;


	return true;
}


template <class _Traits> bool ofWrlReader<_Traits>::read(sMesh* malha, const char *filename, int cellDimension)
{
	OF_ASSERT(filename);
	OF_ASSERT(malha);

	ifstream pf(filename);

	if( pf.is_open())
	{
			if(! reader(pf, malha, cellDimension))
				return false;
		
			pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool ofWrlReader<_Traits>::reader(ifstream &pf, sMesh* malha, int cellDimension)
{
	char auxstr[255];
	space coords[3];
	int j, k;
	int auxvtx[cellDimension];
	char c;
	bool comaAtcoordIndex = false;

	OF_ASSERT(auxstr);

	while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
	{
		pf >> auxstr;
	}

	pf >> c;

	if( c == '[' )
	{
		pf >> auxvtx[0];
		pf >> c;
		if( c == ',' )
		{
			pf >> auxvtx[0];
			pf >> c;
			if( c == ',' ) 
			{
				pf >> auxvtx[0];
				pf >> c;
				if( c == ',' )
				{
					comaAtcoordIndex = true;
				}
			}
		}
	}

	pf.seekg(0); // rewind

	while( (! pf.eof()) && (strcmp(auxstr,"point") != 0) )
	{
		pf >> auxstr;
	}
	
	if(! pf.eof())
	{
		pf >> c;
		
		if( c == '[')
		{
			while ( c != ']')
			{
				for(j = 0; j < 3; j++)
				{
					pf >> coords[j];
				}

				malha->addVertex(coords);

				pf >> c;
				
			}
		}
		else
			return false;

		while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
		{
			pf >> auxstr;
		}

		pf >> c;

		if( c == '[' )
		{
			while ( c != ']')
			{
				for(j = 0; j < cellDimension; j++)
				{
					pf >> auxvtx[j];
					cout << j << ": " << auxvtx[j] << endl;
					if(comaAtcoordIndex)
						pf >> c;
				}

				malha->addCell(auxvtx);

				pf >> k;
				pf >> c;
			}
		}
		else
			return false;
	}
	else
		return false;


	return true;
}

}

#endif
