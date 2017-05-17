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

#ifndef OFOFFWRITER_H
#define OFOFFWRITER_H

#include <fstream>
#include <iomanip>

#include "ofMacros.h"
#include "ofMesh.h"
#include "ofWriter.h"
#include "ofVerticesIterator.h"
#include "ofCellsIterator.h"

using namespace std;

namespace of
{

/**
	@class		ofOffWriter 
	@file		ofOffWriter.h 
	@short
				Save the layers in a file of type OFF

	@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
	@version	1.0 
	@date		2007, July
 
 */	

template <class _Traits>  class ofOffWriter : public ofWriter<_Traits>
{
public:
	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sVertex sVertex;
	typedef typename _Traits::sCell sCell;
	
	typedef typename _Traits::sMesh		sMesh;
	
	ofOffWriter();
	~ofOffWriter();
	
	virtual bool write(sMesh* malha, const char* filename);

private:

	bool writer(ofstream &pf, sMesh *malha);
};

template <class _Traits>  ofOffWriter<_Traits>::ofOffWriter()
{

}

template <class _Traits>  ofOffWriter<_Traits>::~ofOffWriter()
{
}

template <class _Traits> bool ofOffWriter<_Traits>::write(sMesh* malha, const char *filename)
{
	OF_ASSERT(filename);
	OF_ASSERT(malha);	
	
	ofstream pf(filename);
	
	if( pf.is_open())
	{
			if(! writer(pf, malha))
				return false;
		
			pf.close();
	}
	else
		return false;
	
	return true;
}

template <class _Traits> bool ofOffWriter<_Traits>::writer(ofstream &pf, sMesh* malha)
{
	int i = 0,j;
	
	pf << "OFF" << endl;
	pf << malha->getNumberOfVertices() << " ";
	pf << malha->getNumberOfCells() << " ";
	pf << "0" << endl;
	
	
	ofVerticesIterator<_Traits> itv(malha);
	
	ofVector<ids,ids> nvids(malha->getBlockSize());
	i = 0;
	for(itv.initialize(); itv.notFinish(); ++itv)
	{
		if (sVertex::getDimension() == 2)
			pf << setprecision(15) << itv->getCoord(0) << " " << setprecision(15) << itv->getCoord(1) << " 0.0" << endl;
		else if (sVertex::getDimension() == 3)
			pf << setprecision(15) << itv->getCoord(0) << " " << setprecision(15) << itv->getCoord(1) << " " << setprecision(15) << itv->getCoord(2) << endl;
		
		nvids[&itv] = i++;		
	}
	
	ofCellsIterator<_Traits> itc(malha);
	
	for(itc.initialize(); itc.notFinish(); ++itc)
	{
		pf << sCell::getDimension() + 1; 
	
		for(j = 0; j <= sCell::getDimension(); j++)
			pf << " " << nvids[itc->getVertexId(j)];
		pf << endl; 
	}
	
	return true;
}

}

#endif
