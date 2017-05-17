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

#ifndef OFVRMLREADER_H
#define OFVRMLREADER_H

#include <fstream>
#include <cstdlib>
#include <cctype>

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofReader.h"

using namespace std;

namespace of
{

/**
	@class		ofVrmlReader 
	@file		ofVrmlReader.h 
	@short		
			Class that reads a Vrml model (file) based on Vrml 2.0 definitions and
			add vertices and cells to OF structure of mesh. If troubles occurs
			during the reading, check out restrictions in CybDataObtainer.h			
						
	@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version	1.5 
	@date		2009, November
 */		
	
template <class _Traits> class ofVrmlReader : public ofReader<_Traits>
{
public:
	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sVertex sVertex;
	typedef typename _Traits::sCell sCell;
	
	typedef typename _Traits::sMesh	sMesh;
	
	/**	
	 * Constructor
	 * 
	 * @param void
	 */
	ofVrmlReader();
	
	/**	
	 * Destructor
	 * 
	 * @param void
	 */
	~ofVrmlReader();
	
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

template <class _Traits> ofVrmlReader<_Traits>::ofVrmlReader()
{
}

template <class _Traits> ofVrmlReader<_Traits>::~ofVrmlReader()
{
}

template <class _Traits> bool ofVrmlReader<_Traits>::read(sMesh* malha, const char *filename)
{
	OF_ASSERT(filename);
	OF_ASSERT(malha);

	ifstream pf(filename);

	if( pf.is_open())
	{
			if(!reader(pf, malha))
			{
				puts("\nRead Error!\n");
				return false;
			}
		
			pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool ofVrmlReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3];
	int auxvtx[3];
	char c;

	OF_ASSERT(auxstr);
	
	pf >> auxstr;

	/* try to find 'point' tag */
	while( (! pf.eof()) && (strcmp(auxstr,"point") != 0) )
	{
		pf >> auxstr;
	}	
	if(pf.eof())
		return false;

	pf >> c;

	/* start to add 'space coords' to 'sMesh* malha' with 'addVertex' method */
	if( c == '[')
	{	
		pf >> c;	
		if(c == ']')
			return false;
			
		do{
			pf.putback(c);
			pf >> auxstr;
			coords[0] = atof(auxstr);
			pf >> auxstr;
			coords[1] = atof(auxstr);
			pf >> coords[2];
			malha->addVertex(coords);
			pf >> c;
			if(c ==',')
				pf >> c;
		}while(c == '-' || isdigit(c)); // verify if the next character is a number (negative or not)
			
		if(c != ']')
			return false;
	}
	else
		return false;

	/* try to find 'coordIndex' tag */
	while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
	{
		pf >> auxstr;
	}
	if(pf.eof())
		return false;
	pf >> c;

	/* start to add 3d vector to 'sMesh* malhar' with 'addCell' method */
	if( c == '[' )
	{	
		pf >> c;
		if(c == ']')
			return false;
		
		do{
			pf.putback(c);
			pf >> auxstr;
			auxvtx[0] = atoi(auxstr);
			pf >> auxstr;
			auxvtx[1] = atoi(auxstr);
			pf >> auxvtx[2];
			malha->addCell(auxvtx);
				
			// if there isnt '-1' after, there isnt another cell to add
			pf >> c;
			if(c == ',')
				pf >> c;
			if(c != '-') // verify if there is another cell to add
				break;
			pf >> c;
			pf >> c;
			if(c == ',')
				pf >> c;
				
		}while(c == '-' || isdigit(c));
			
		if(c != ']')
			return false;
	}
	else
		return false;
	cout << "Modelo Carregado" << endl;
	return true;
}


template <class _Traits> bool ofVrmlReader<_Traits>::read(sMesh* malha, const char *filename, int cellDimension)
{
	OF_ASSERT(filename);
	OF_ASSERT(malha);

	ifstream pf(filename);

	if( pf.is_open())
	{
			if(! reader(pf, malha, cellDimension))
			{
				printf("\nRead Error!\n");
				return false;
			}
		
			pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool ofVrmlReader<_Traits>::reader(ifstream &pf, sMesh* malha, int cellDimension)
{
	char auxstr[255];
	space coords[3];
	int j;
	int auxvtx[cellDimension];
	char c;

	OF_ASSERT(auxstr);

	pf >> auxstr;

	/* try to find 'point' tag */
	while( (! pf.eof()) && (strcmp(auxstr,"point") != 0) )
	{
		pf >> auxstr;
	}	
	if(pf.eof())
		return false;

	pf >> c;

	/* start to add 'space coords' to 'sMesh* malha' with 'addVertex' method */
	if( c == '[')
	{	
		pf >> c;	
		if(c == ']')
			return false;
			
		do{
			pf.putback(c);
			pf >> auxstr;
			coords[0] = atof(auxstr);
			pf >> auxstr;
			coords[1] = atof(auxstr);
			pf >> coords[2];
			malha->addVertex(coords);
			pf >> c;
			if(c ==',')
				pf >> c;
		}while(c == '-' || isdigit(c)); // verify if the next character is a number (negative or not)
			
		if(c != ']')
			return false;
	}
	else
		return false;

	/* try to find 'coordIndex' tag */
	while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
	{
		pf >> auxstr;
	}
	if(pf.eof())
		return false;
	pf >> c;

	/* start to add 3d vector do 'sMesh* malhar' with 'addCell' method */
	if( c == '[' )
	{	
		pf >> c;
		if(c == ']')
			return false;
			
		do{
			pf.putback(c);
			for(j = 0;  j < cellDimension-1; j++)
			{
				pf >> auxstr;
				auxvtx[j] = atoi(auxstr);
			}
			pf >> auxvtx[j];
			
			malha->addCell(auxvtx);
		
			// if there isnt '-1' after, there isn't another cell to add
			pf >> c;
			if(c == ',')
				pf >> c;
			if(c != '-') // verify if there is another cell to add
				break;
			pf >> c;
			pf >> c;
			if(c == ',')
				pf >> c;
		}while(c == '-' || isdigit(c));
			
		if(c != ']')
			return false;
	}
	else
		return false;

	return true;
}

}

#endif
