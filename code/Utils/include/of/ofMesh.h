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

#ifndef OFMESH_H
#define OFMESH_H

#include "ofMacros.h"
#include "ofVector.h"

namespace of
{

#define IDS typename ofMesh<_Traits>::ids
#define SVERTEX typename ofMesh<_Traits>::sVertex
#define SCELL typename ofMesh<_Traits>::sCell

/**
@class		ofMesh 
@file		ofMesh.h 
@short
	Mesh Class
	This class must be initialized with elements types (vertices and cells) and the operation class.
	Operation class depends of the vertices and cells dimensions.
	_Traits must have: space, ids, sVertex, sCell, sOper

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0 
@date		2007, July
*/

template <class _Traits> class ofMesh
{
public:

	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sVertex sVertex;
	typedef typename _Traits::sCell sCell;
	typedef typename _Traits::sOper sOper;
	typedef typename _Traits::sTopology sTopology;
	
	//friend template<class _Traits> class sTopology;
	
	

	/**	
	 * Constructor
	 * 
	 * @param block_size size of vector blocks. The maximum size of vector is block_size * block_size
	 */
	ofMesh(ids block_size = 5000);
	
	/** 
	 * Destructor 
	 * 
	 * @param void
	 * 
	 */
	~ofMesh();
	
	/**	
	 * Add a vertex in mesh
	 * 
	 * @param space* coords vector with the vertex coordinates
	 * @return ids the vertex id in mesh
	 */
	ids addVertex(space *coords OF_DMUTEXVD);

	/**	
	 * Delete a vertex in mesh
	 * 
	 * @param ids idvertex the vertex will be deleted
	 * @return bool if the vertex was deleted
	 */
	bool delVertex(ids idvertex OF_DMUTEXVD);
	
	/**	
	 * Return the number of vertices in mesh
	 * @param void
	 * @return ids the number of vertices in mesh
	 */
	ids getNumberOfVertices(OF_DMUTEXD);

	/** 
	 * Return the greater vertex id
	 * @param void
	 * @return ids the greater vertex id 
	 */
	ids getVertexMaxId(OF_DMUTEXD);
	
	/**	
	 * Return the vertex address
	 * 
	 * @param ids idvertex the vertex id
	 * @return sVertex* the vertex address
	 */
	sVertex* getVertex(ids idvertex OF_DMUTEXVD);
	
	/**	
	 * Return true if the specified vertex id is a vertex in mesh
	 * @param ids idvertex the vertex id
	 * @return bool if the specified vertex id is a vertex in mesh
	 */
	bool isVertex(ids idvertex OF_DMUTEXVD);

	/** 
	 * Add a cell in mesh
	 * 
	 * @param ids idvertices vector with vertices ids of the cell
	 * @return ids the cell id in mesh
	 */
	ids addCell(ids *idvertices OF_DMUTEXVD);
	
	/** 
	 * Delete a cell in mesh
	 * 	
	 * @param ids idcell the cell id
	 * @return bool if the cell was deleted
	 */
	bool delCell(ids idcell OF_DMUTEXVD);

	/** 
	 * Return the number of cells in mesh
	 * 
	 * @param void
	 * @return ids the number of cells in mesh
	 */
	ids getNumberOfCells(OF_DMUTEXD);
	
	/** 
	 * Return the greater cell id in mesh
	 * 
	 * @param void
	 * @return ids the greater cell id in mesh
	 */
	ids getCellMaxId(OF_DMUTEXD);
	
	/**	
	 * Return the cell address
	 * 
	 * @param ids idcell the cell id
	 * @return sCell* the cell address
	 */
	sCell* getCell(ids idcell OF_DMUTEXVD);
	
	/** 
	 * Return if the specified cell id is a cell in mesh
	 * 
	 * @param void
	 * @return bool if the specified cell id is a cell in mesh
	 */
	bool isCell(ids idcell OF_DMUTEXVD);

	/**	Define the number of vertices
	 * 
	 * (DONT USE)
	 */
	void setNumberOfVertices(ids number OF_DMUTEXVD);

	/**	Define the number of cells
	 * 
	 * (DONT USE)
	 */
	void setNumberOfCells(ids number OF_DMUTEXVD);

	
	/**	
	 * Add a vertex in specified position in mesh
	 * 
	 * @param ids idvertex position of vertex
	 * @param space* coords vector with the vertex coordinates
	 * 
	 * @return void
	 */
	void addVertex(ids idvertex, space *coords OF_DMUTEXVD);

	/** 
	 * Add a cell in specified position in mesh
	 * 
	 * @param ids idcell position of cell
	 * @param ids* idvertices vector with vertices ids of the cell
	 * 	
	 * @return void
	 */
	void addCell(ids idcell, ids *idvertices OF_DMUTEXVD);

	/** 
	 * Add a cell in the mesh
	 * 
	 * @param ids* idvertices vector with vertices ids of the cell
	 * @param ids* idops the mesh operator id
	 * 	
	 * @return ids the cell id
	 */
	ids addCell(ids *idvertices, ids *idops OF_DMUTEXVD);
	
	/** 
	 * Return the mesh block size
	 * 
	 * @param void
	 * @return ids the mesh block size
	 */
	ids getBlockSize();

	/** 
	 * Free a cell in the mesh
	 * 
	 * @param ids idcell the cell id
	 * @return void 
	 */
	void freeCell(ids idcell OF_DMUTEXVD);
	
	/** 
	 * Free a vertex in the mesh
	 * 
	 * @param ids idvertex the vertex id
	 * @return void
	 */
	void freeVertex(ids idvertex OF_DMUTEXVD);

 private:
	
	sOper oper;		/**< the mesh operator */
	
	ids bsize;		/**< the mesh block size */
	
	ofVector<sVertex,ids> vertices;	/**< vector with vertices ids */
	ofVector<sCell,ids> cells;		/**< vector with cells ids */
	
#ifdef OF_THREADS
 	pthread_mutex_t vertices_mutex;
 	pthread_mutex_t cells_mutex;
#endif
};

template <class _Traits> ofMesh<_Traits>::ofMesh(ids block_size):
 oper(this), vertices(block_size), cells(block_size)
{
	
	bsize = block_size;
	
#ifdef OF_THREADS
	pthread_mutex_init(&vertices_mutex,0);
	pthread_mutex_init(&cells_mutex,0);
#endif
}

template <class _Traits> ofMesh<_Traits>::~ofMesh()
{
#ifdef OF_THREADS
	pthread_mutex_destroy(&vertices_mutex);
	pthread_mutex_destroy(&cells_mutex);
#endif
}

template <class _Traits> IDS ofMesh<_Traits>::getBlockSize()
{
	return bsize;
}

// Vertices ***********************************************************************************

template <class _Traits> IDS ofMesh<_Traits>::addVertex(space *coords OF_DMUTEXV)
{
	ids idvertex;

	OF_ASSERT(coords);
	
	OF_LOCK(vertices_mutex);
	
	idvertex = vertices.getFree();
	
	OF_UNLOCK(vertices_mutex);
	
	addVertex(idvertex, coords OF_MUTEXV);

	return idvertex;
}

template <class _Traits> void ofMesh<_Traits>::addVertex(ids idvertex, space *coords OF_DMUTEXV)
{
	sVertex* v;

	OF_ASSERT(coords);
	
	v = &vertices[idvertex];
	v->setCoords(coords OF_MUTEXV);
	
}

template <class _Traits> bool ofMesh<_Traits>::delVertex(ids idvertex OF_DMUTEXV)
{
	OF_ASSERT(idvertex >= 0);
	
	bool temp;
	
	if(vertices[idvertex].getNumberOfSings(OF_MUTEX) == 0)
	{	
		OF_LOCK(vertices_mutex);		
	
		temp = vertices.free(idvertex);
		
		OF_UNLOCK(vertices_mutex);
	}
	else
		temp = false;	

	return temp;
}

template <class _Traits> IDS ofMesh<_Traits>::getNumberOfVertices(OF_DMUTEX)
{
	OF_LOCK(vertices_mutex);
	
	ids temp = vertices.getSize();

	OF_UNLOCK(vertices_mutex);

	return temp;
}

template <class _Traits> void ofMesh<_Traits>::setNumberOfVertices(ids number OF_DMUTEXV)
{
	OF_LOCK(vertices_mutex);
	
	vertices.setSize(number);

	OF_UNLOCK(vertices_mutex);
}

template <class _Traits> IDS ofMesh<_Traits>::getVertexMaxId(OF_DMUTEX)
{
	OF_LOCK(vertices_mutex);
	
	ids temp = vertices.getMaxId();

	OF_UNLOCK(vertices_mutex);

	return temp;
}

template <class _Traits> SVERTEX* ofMesh<_Traits>::getVertex(ids idvertex OF_DMUTEXV)
{
	OF_ASSERT(idvertex >= 0);
	return &vertices[idvertex];
}

template <class _Traits> bool ofMesh<_Traits>::isVertex(ids idvertex OF_DMUTEXV)
{
	return vertices[idvertex].inMesh(OF_MUTEX);
}



// Cells ***********************************************************************************

template <class _Traits> IDS ofMesh<_Traits>::addCell(ids *idvertices OF_DMUTEXV)
{
	OF_ASSERT(idvertices);

	OF_LOCK(cells_mutex);
	
	int idcell = cells.getFree();
	
	OF_UNLOCK(cells_mutex);
	
	oper.addCell(idcell, idvertices OF_MUTEXV);

	return idcell;
}

template <class _Traits> void ofMesh<_Traits>::addCell(ids idcell, ids *idvertices OF_DMUTEXV)
{
	OF_ASSERT(idvertices);

	oper.addCell(idcell, idvertices OF_MUTEXV);
}

template <class _Traits> bool ofMesh<_Traits>::delCell(ids idcell OF_DMUTEXV)
{
	
	OF_ASSERT( (idcell >= 0)&&(idcell <= getCellMaxId(OF_MUTEX)) );

	oper.delCell(idcell OF_MUTEXV);
	
	OF_LOCK(cells_mutex);
	
	cells.free(idcell);
		
	OF_UNLOCK(cells_mutex);
	
	return true;
}

template <class _Traits>  IDS ofMesh<_Traits>::getNumberOfCells(OF_DMUTEX)
{
	OF_LOCK(cells_mutex);
	
	ids temp = cells.getSize();

	OF_UNLOCK(cells_mutex);

	return temp;
}

template <class _Traits> void ofMesh<_Traits>::setNumberOfCells(ids number OF_DMUTEXV)
{
	OF_LOCK(cells_mutex);
	
	cells.setSize(number);

	OF_UNLOCK(cells_mutex);
}

template <class _Traits> IDS ofMesh<_Traits>::getCellMaxId(OF_DMUTEX)
{
	OF_LOCK(vertices_mutex);
	
	ids temp = cells.getMaxId();

	OF_UNLOCK(vertices_mutex);

	return temp;
}

template <class _Traits>  SCELL* ofMesh<_Traits>::getCell(ids idcell OF_DMUTEXV)
{
	OF_ASSERT(idcell >= 0);
	return &cells[idcell];
}

template <class _Traits> bool ofMesh<_Traits>::isCell(ids idcell OF_DMUTEXV)
{
	return cells[idcell].inMesh(OF_MUTEX);
}

template <class _Traits> IDS ofMesh<_Traits>::addCell(ids *idvertices, ids *idops OF_DMUTEXV)
{
	ids idcell;

	OF_ASSERT(idvertices);
	OF_ASSERT(idops);
	
	OF_LOCK(cells_mutex);
	
	idcell = cells.getFree();
	
	OF_UNLOCK(cells_mutex);
	
	oper.addCell(idcell, idvertices, idops OF_MUTEXV);
		
	return idcell;
}

template <class _Traits> void ofMesh<_Traits>::freeCell(ids idcell OF_DMUTEXVD)
{
	OF_LOCK(cells_mutex);
	
	cells.free(idcell);
		
	OF_UNLOCK(cells_mutex);
}

template <class _Traits> void ofMesh<_Traits>::freeVertex(ids idvertex OF_DMUTEXVD)
{
	OF_LOCK(vertices_mutex);		

	vertices.free(idvertex);
		
	OF_UNLOCK(vertices_mutex);
}

#undef IDS
#undef SVERTEX
#undef SCELL

}

#endif
