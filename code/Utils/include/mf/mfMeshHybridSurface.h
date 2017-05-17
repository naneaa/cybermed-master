#ifndef MFMESHHYBRIDSURFACE_H
#define MFMESHHYBRIDSURFACE_H

#include "mfMacros.h"
#include "mfSing.h"
#include "mfMesh.h"
#include "mfMeshOper.h"
//#include "mfVertexStarIteratorQuadSurf.h"

namespace mf
{

/**	Operation Class for Hybrid Surface in a 3D space (with oriented quadrilaterals)
 *
 *	_Traits must have: ids, sVertex, sCell, sSing, sMesh
 */
template <class _Traits> class mfMeshHybridSurface : public mfMeshOper<_Traits>
{
public:

	typedef typename _Traits::ids		 ids;		/**< Id typename definition*/
	typedef typename _Traits::sVertex	sVertex;	/**< Vertex typename definition*/
	typedef typename _Traits::sCell		sCell;		/**< Cell typename definition*/
	typedef mfSing<_Traits>			sSing;		/**< Singular typename definition*/
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition*/

	/**	Constructor
	 *
	 *	\param _mesh: the mesh address that this class will manipulate
	 */
	mfMeshHybridSurface(sMesh *_mesh);

	/**	Destructor */
	~mfMeshHybridSurface();

	/** Add cell in mesh
	 *
	 *	\param idcell: cell id
	 *	\param idvertices: vector with vertices ids of the cell
	 */
	void addCell(ids idcell, ids *idvertices MF_DMUTEXVD);

	/**	Delete a cell
	 *
	 *	\param idcell: cell id
	 */
	void delCell(ids idcell MF_DMUTEXVD);

private:

#ifdef MF_THREADS
	void lockVertices(int num, sVertex* v);
	void unlockVertices(int num, sVertex* v);
#endif
};

template <class _Traits> mfMeshHybridSurface<_Traits>::mfMeshHybridSurface(sMesh *_mesh)
: mfMeshOper<_Traits>(_mesh)
{
}

template <class _Traits> mfMeshHybridSurface<_Traits>::~mfMeshHybridSurface()
{
}

template <class _Traits> void mfMeshHybridSurface<_Traits>::addCell(ids idcell, ids *idvertices MF_DMUTEXV)
{
	// Correct vertex id (i.e. >=0). In the case of idvertices[3] >= -1, it will be -1 if cell is triangle.
	MF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0)&&(idvertices[3] >= -1));
	// Any vertex that are alike
	MF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[0] != idvertices[3]));
	MF_ASSERT((idvertices[1] != idvertices[2])&&(idvertices[1] != idvertices[3])&&(idvertices[2] != idvertices[3]));

	sCell *c = this->mesh->getCell(idcell);
	ids idv[4] = { idvertices[0], idvertices[1], idvertices[2], idvertices[3]};

	sVertex *v[4] = {this->mesh->getVertex(idv[0]), this->mesh->getVertex(idv[1]), this->mesh->getVertex(idv[2]), NULL};

	if(idv[3]+1)
	{
		v[3] = this->mesh->getVertex(idv[3]);
	}

	sCell *cop;
	sSing *s;
	ids icop;
	ids idEdge;
	int i, pos;

	c->clearMates();

	c->setVertexId(0,idv[0]);
	c->setVertexId(1,idv[1]);
	c->setVertexId(2,idv[2]);
	c->setVertexId(3,idv[3]);

	if(idv[3]+1) // if cell is quadrangular.
	{
		for(i = 0; i < 4; i++)
		{
			s = v[i]->getSing(); // [i]

			while (s)
			{
				icop = s->getCell();
				cop = this->mesh->getCell(icop);
				if(((cop->getVertexId(3)+1)?(cop->getVertexId((cop->getVertexIndex(idv[i]) + 3)%4)):(cop->getVertexId((cop->getVertexIndex(idv[i]) + 2)%3))) == idv[(i+1)%4])
				{
					idEdge = this->mesh->addEdge();
					c->setEdgeId(i, idEdge);
					cop->setEdgeId(cop->getVertexIndex(idv[(i+1)%4]), idEdge);
					c->setMateId(i, icop);
					cop->setMateId(cop->getVertexIndex(idv[(i+1)%4]), idcell);

					s = NULL;
				}
				else
					s = s->getNext();
			}
		}

		for(i = 0; i < 4; i++)
		{
			if (c->getMateId((i+3)%4) < 0)
			{
				if(c->getMateId(i) >= 0)
				{
					pos = v[i]->inSings(c->getMateId(i));
					v[i]->setSingCell(pos,idcell);
				}
				else
					v[i]->addSing(idcell);
			}
			else
			{
				if(c->getMateId(i) >= 0)
				{
					icop = c->getMateId(i);
					pos = v[i]->inSings(icop);
					while((icop >= 0)&&(icop != idcell))
					{
						cop = this->mesh->getCell(icop);
						icop = cop->getMateId(cop->getVertexIndex(idv[i]));
						if(icop < 0)
							v[i]->delSing(pos);
					}
				}
			}
		}
	}
	else // is triangular
	{
		for(i = 0; i < 3; i++)
		{
			s = v[i]->getSing();

			while (s)
			{
				icop = s->getCell();
				cop = this->mesh->getCell(icop);
				if(((cop->getVertexId(3) == -1)?(cop->getVertexId((cop->getVertexIndex(idv[i]) + 2)%3)):(cop->getVertexId((cop->getVertexIndex(idv[i]) + 3)%4))) == idv[(i+1)%3])
				{
					idEdge = this->mesh->addEdge();
					c->setEdgeId(i, idEdge);
					cop->setEdgeId(cop->getVertexIndex(idv[(i+1)%3]), idEdge);
					c->setMateId(i, icop);
					cop->setMateId(cop->getVertexIndex(idv[(i+1)%3]), idcell);

					s = NULL;
				}
				else
					s = s->getNext();
			}
		}

		for(i = 0; i < 3; i++)
		{
			if (c->getMateId((i+2)%3) < 0)
			{
				if(c->getMateId(i) >= 0)
				{
					pos = v[i]->inSings(c->getMateId(i));
					v[i]->setSingCell(pos,idcell);
				}
				else
					v[i]->addSing(idcell);
			}
			else
			{
				if(c->getMateId(i) >= 0)
				{
					icop = c->getMateId(i);
					pos = v[i]->inSings(icop);
					while((icop >= 0)&&(icop != idcell))
					{
						cop = this->mesh->getCell(icop);
						icop = cop->getMateId(cop->getVertexIndex(idv[i]));
						if(icop < 0)
							v[i]->delSing(pos);
					}
				}
			}
		}
	}
}

/* Not tested */
template <class _Traits> void mfMeshHybridSurface<_Traits>::delCell(ids idcell MF_DMUTEXV)
{
	int i,pos;
	sCell *cop, *c = this->mesh->getCell(idcell);
	sVertex *v[4] = { this->mesh->getVertex(c->getVertexId(0)), this->mesh->getVertex(c->getVertexId(1)), this->mesh->getVertex(c->getVertexId(2)), this->mesh->getVertex(c->getVertexId(3))};
	ids icop;
	int numEdge = c->getNumberEdgesInCell();

	for(i = 0; i < numEdge; i++)
	{
		if(numEdge == 3) // triangle
		{
			if(c->getMateId((i+2)%3) >= 0)
			{
				if(c->getMateId(i) >= 0) //i
				{
					icop = c->getMateId(i); //i
					while((icop >= 0)&&(icop != idcell))
					{
						cop = this->mesh->getCell(icop);
						icop = cop->getMateId(cop->getVertexIndex(c->getVertexId(i))); //i+2
						if(icop < 0)
							v[i]->addSing(c->getMateId(i));
						else if (icop == idcell)
							v[i]->getSing()->setCell(c->getMateId(i));
					}
				}
			}
			else
			{
				pos = v[i]->inSings(idcell);
				if(c->getMateId(i) >= 0) //i
					v[i]->setSingCell(pos,c->getMateId(i)); //i+2
				else
					v[i]->delSing(pos);
			}
		}
		else // quadrangular
		{
			if(c->getMateId((i+3)%4) >= 0)
			{
				if(c->getMateId(i) >= 0) //i
				{
					icop = c->getMateId(i); //i
					while((icop >= 0)&&(icop != idcell))
					{
						cop = this->mesh->getCell(icop);
						icop = cop->getMateId(cop->getVertexIndex(c->getVertexId(i))); //i+2
						if(icop < 0)
							v[i]->addSing(c->getMateId(i));
						else if (icop == idcell)
							v[i]->getSing()->setCell(c->getMateId(i));
					}
				}
			}
			else
			{
				pos = v[i]->inSings(idcell);
				if(c->getMateId(i) >= 0) //i
					v[i]->setSingCell(pos,c->getMateId(i)); //i+2
				else
					v[i]->delSing(pos);
			}
		}
	}

	for(i=0; i < numEdge; i++)
	{
		icop = c->getMateId(i);
		if(icop >= 0)
		{
			cop = this->mesh->getCell(icop);
			cop->setMateId(cop->getMateIndex(idcell),-1);
		}
	}

	c->setMateId(0,-1);
	c->setMateId(1,-1);
	c->setMateId(2,-1);
	if(numEdge == 4)
		c->setMateId(3,-1);
}

}

#endif
