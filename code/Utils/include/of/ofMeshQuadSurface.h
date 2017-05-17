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

#ifndef OFMESHQUADSURFACE_H
#define OFMESHQUADSURFACE_H

#include "ofMacros.h"
#include "ofSing.h"
#include "ofMesh.h"
#include "ofMeshOper.h"
#include "ofVertexStarIteratorSurface.h"

namespace of
{

/**
@class		ofMeshQuadSurface 
@file		ofMeshQuadSurface.h 
@short 
		Operation Class for Quadrilaterals in 3D space (with oriented quadrilaterals)
		
		_Traits must have: ids, sVertex, sCell, sSing, sMesh

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0 
@date		2007, July
 
 */

template <class _Traits> class ofMeshQuadSurface : public ofMeshOper<_Traits>
{
public:
	typedef typename _Traits::ids		 ids;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::sCell 	sCell;

	typedef ofSing<_Traits> 			sSing;
	typedef typename _Traits::sMesh		sMesh;

	/**	Constructor
	 * 
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	ofMeshQuadSurface(sMesh *_mesh);

	/**	Destructor */	
	~ofMeshQuadSurface();

	/** Add cell in mesh
	 * 
	 *	\param idcell: cell id
	 * 	\param idvertices: vector with vertices ids of the cell
	 */	
	void addCell(ids idcell, ids *idvertices OF_DMUTEXVD);

	/**	Delete a cell
	 * 
	 * 	\param idcell: cell id
	 */	
	void delCell(ids idcell OF_DMUTEXVD);

private:

#ifdef OF_THREADS
	//void lockVertices(int num, sVertex* v);
	//void unlockVertices(int num, sVertex* v);
#endif
};

template <class _Traits> ofMeshQuadSurface<_Traits>::ofMeshQuadSurface(sMesh *_mesh)
: ofMeshOper<_Traits>(_mesh)
{
}

template <class _Traits> ofMeshQuadSurface<_Traits>::~ofMeshQuadSurface()
{
}

template <class _Traits> void ofMeshQuadSurface<_Traits>::addCell(ids idcell, ids *idvertices OF_DMUTEXV)
{
	// Correct vertex id (i.e. >=0)
	OF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0)&&(idvertices[3] >= 0));
	// Any vertex that are a like
	OF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[0] != idvertices[3]));
	OF_ASSERT((idvertices[1] != idvertices[2])&&(idvertices[1] != idvertices[3])&&(idvertices[2] != idvertices[3]));

	sCell *c = this->mesh->getCell(idcell);
	ids idv[4] = { idvertices[0], idvertices[1], idvertices[2], idvertices[3]};
	sVertex *v[4] = { this->mesh->getVertex(idv[0]), this->mesh->getVertex(idv[1]), this->mesh->getVertex(idv[2]), this->mesh->getVertex(idv[3])};
	sCell *cop;
	sSing *s;
	ids icop;
	int i, pos;

	//c->clearMates();

	c->setVertexId(0,idv[0]);
	c->setVertexId(1,idv[1]);
	c->setVertexId(2,idv[2]);
	c->setVertexId(3,idv[3]);

	// 4 vertexes
	for(i = 0; i < 4 ; i++)
	{
		// singularity from ant vertex
		s = v[(i+3)%4]->getSing();

		//cout << "vertex " << i << ": " << s << endl;

		while (s)
		{
			icop = s->getCell();
			cop = this->mesh->getCell(icop);
			if ( cop->getVertexId((cop->getVertexIndex(idv[(i+2)%4]) - 1)%4) == idv[(i+3)%4])
			{
				c->setMateId(i, icop);
				
				cout << "mate in " << c << " " << i << ": "<< icop << endl;
				
				cop->setMateId((cop->getVertexIndex(idv[(i+2)%4]) + 1)%4, idcell);
				s = NULL;
			}
			else
				s = s->getNext();
		}
	}

	for(i = 0; i < 4; i++)
	{
		if (c->getMateId((i+2)%4) < 0)
		{
			if(c->getMateId((i+1)%4) >= 0)
			{
		  		pos = v[i]->inSings(c->getMateId((i+1)%4));
				v[i]->setSingCell(pos,idcell);
			}
			else
				v[i]->addSing(idcell);
		}
		else
		{
			if(c->getMateId((i+1)%4) >= 0)
			{
				icop = c->getMateId((i+1)%4);
				pos = v[i]->inSings(icop);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop);
					icop = cop->getMateId((cop->getVertexIndex(idv[i])+1)%4);
					if(icop < 0)
						v[i]->delSing(pos);
				}
			}
		}

		if (c->getMateId((i+3)%4) < 0)
		{
			if(c->getMateId((i+1)%4) >= 0)
			{
		  		pos = v[i]->inSings(c->getMateId((i+1)%4));
				v[i]->setSingCell(pos,idcell);
			}
			else
				v[i]->addSing(idcell);
		}
		else
		{
			if(c->getMateId((i+1)%4) >= 0)
			{
				icop = c->getMateId((i+1)%4);
				pos = v[i]->inSings(icop);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop);
					icop = cop->getMateId((cop->getVertexIndex(idv[i])+1)%4);
					if(icop < 0)
						v[i]->delSing(pos);
				}
			}
		}

		/*if (c->getMateId((i+0)%4) < 0)
		{
			if(c->getMateId((i+1)%4) >= 0)
			{
		  		pos = v[i]->inSings(c->getMateId((i+1)%4));
				v[i]->setSingCell(pos,idcell);
			}
			else
				v[i]->addSing(idcell);
		}
		else
		{
			if(c->getMateId((i+1)%4) >= 0)
			{
				icop = c->getMateId((i+1)%4);
				pos = v[i]->inSings(icop);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop);
					icop = cop->getMateId((cop->getVertexIndex(idv[i])+1)%4);
					if(icop < 0)
						v[i]->delSing(pos);
				}
			}
		}*/
	}

	for(i = 0; i < 4; i++)
	{

	}
}

template <class _Traits> void ofMeshQuadSurface<_Traits>::delCell(ids idcell OF_DMUTEXV)
{
	int i,pos;
	sCell *cop, *c = this->mesh->getCell(idcell);
	sVertex *v[4] = { this->mesh->getVertex(c->getVertexId(0)), this->mesh->getVertex(c->getVertexId(1)), this->mesh->getVertex(c->getVertexId(2)), this->mesh->getVertex(c->getVertexId(3))};
	ids icop;
	
}

}

#endif
