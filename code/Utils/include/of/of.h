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

/**
@file		of.h 
@short

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo and
		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.5
@date		2009, November
 */

#ifndef OF_H
#define OF_H

// System includes ---------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef OF_THREADS
	#include <libpq-fe.h>
	#include <pthread.h>
#endif

#ifdef OF_DEBUG
	#include <assert.h>
#endif 

using namespace std;

// OF includes -------------------------------------------------------------
#include "ofMacros.h"
#include "ofBase.h"
#include "ofVector.h"
#include "ofList.h"
#include "ofKdTree.h"
#include "ofXmlParser.h"

#include "ofVertex.h"
#include "ofSing.h"
#include "ofCell.h"

#include "ofSingularVertex.h"
#include "ofVertex2D.h"
#include "ofVertex3D.h"
#include "ofCell2D.h"
#include "ofCell3D.h"

#include "ofBoundaryCellIterator2D.h"
#include "ofBoundaryCellCIterator2D.h"
#include "ofCellsIterator.h"
#include "ofVerticesIterator.h"
#include "ofVertexStarIterator2D.h"
#include "ofVertexStarIterator3D.h"
#include "ofVertexStarIteratorSurface.h"
#include "ofEdgeStarIterator3D.h"

#include "ofMesh.h"
#include "ofMeshOper.h"
#include "ofMesh2D.h"
#include "ofMesh3D.h"
#include "ofMeshSurface.h"
#include "ofMeshNOSurface.h"
#include "ofDelaunay2D.h"
#include "ofGeometric.h"
#include "ofTopology.h"
#include "ofBinaryIO.h"

#include "ofReader.h"
#include "ofWriter.h"
#include "ofOfReader.h"
#include "ofVtkReader.h"
#include "ofPolyDataReader.h"
#include "ofOffReader.h"
#include "ofOffWriter.h"
#include "ofVrmlReader.h"
#include "ofWrlReader.h"
#include "ofOfWriter.h"
#include "ofVtkWriter.h"
#include "ofPolyDataWriter.h"

#include "ofTraits.h"

#include "ofTReader.h"
#include "ofPgReader.h"

#endif
