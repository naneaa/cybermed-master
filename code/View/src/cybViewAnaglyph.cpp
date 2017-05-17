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

#include "cybViewAnaglyph.h"
	 
	CybViewAnaglyph::CybViewAnaglyph() 
	{							
		Cyb3DWorld : viewNumber = 2; //sets the visualization number
	}
	
	
	void CybViewAnaglyph::display()
	{
	
		CybParameters *cybCore = CybParameters::getInstance();
		//CybInterator *interator = CybInterator::getInstance();
	
		double frustumAssimetry;
		sVertex *v0, *v1, *v2;
		int l;
		int index;
		static bool k = false;
	
		glColorMask(1,1,1,1);
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0,0,0,0);
		glDrawBuffer(GL_BACK);
	
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		// Left Eye
	
		glMatrixMode(GL_PROJECTION);
	
	
		// left camera -1
		if(cybCore->modified == 1)
		{
			cout << "Paralaxe " << cybCore->getParalaxe() << endl;
			frustumAssimetry = cybCore->StereoProjection(-6.4, 6.4, -6.4, 6.4, 6.0, -6.0, 180, 14.5, -cybCore->getStereoMagnitude(), cybCore->getParalaxe());
			cybCore->rightFrustumLeftEye = cybCore->widthProportion*(cybCore->dfXRange/2 - frustumAssimetry);
			cybCore->leftFrustumLeftEye = cybCore->widthProportion*(-cybCore->dfXRange/2 - frustumAssimetry);
		}
	
		glLoadIdentity();
	
		glFrustum(cybCore->leftFrustumLeftEye, cybCore->rightFrustumLeftEye, cybCore->widthProportion*cybCore->FrustumBase, cybCore->heightProportion*cybCore->FrustumTop, cybCore->dfNearClipDistance, cybCore->dfFarClipDistance);
	
		glTranslated(-cybCore->dfXMidpoint - cybCore->dfStereoCameraOffset, 0, 0);
	
		gluLookAt(0, 0, cybCore->camPosZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glClear(GL_DEPTH_BUFFER_BIT);
		glColorMask(1,0,0,1);
		glColor4f(1, 0, 0, 1);
		
		glTranslated(cybCore->getParalaxe(),0,0);
	
		//If there is one or more interators, draw.
		if(cybCore->getNumInterators() > 0)
		{
			glPushMatrix();
	
			glEnable(GL_TEXTURE_2D);

			//Interator objects
			int numInterators = cybCore->getNumInterators();
			for (int i = 0; i < numInterators; i++) {
				CybInterator* interator = cybCore->getInterator(i);

				interator->drawInterator();
			}
			glPopMatrix();
			glLoadIdentity();
		}

		lights();
		
		glTranslated(cybCore->getParalaxe(),0,0);

		for(int j=0; j < cybCore->numLayer; j++)	
		{
			if(cybCore->habLayer[j] == 1)
			{
				mfCellsIterator<cybSurfaceTriTraits> itc(cybCore->mesh[j]);
	
				//  red object
				glColor4f(1, 0, 0, cybCore->getColor(j)[3]);
	
				// transformations
				glTranslated(cybCore->xTrans + cybCore->layerTrans[j][0], cybCore->yTrans + cybCore->layerTrans[j][1], cybCore->zTrans + cybCore->layerTrans[j][2]);
				glScaled(cybCore->xScale * cybCore->layerSca[j][0], cybCore->yScale * cybCore->layerSca[j][1], cybCore->zScale * cybCore->layerSca[j][2]);
				glTranslated(cybCore->cX, cybCore->cY, cybCore->cZ);
				glRotated(cybCore->getXAngle() + cybCore->layerRot[j][0],1,0,0);
				glRotated(cybCore->getYAngle() + cybCore->layerRot[j][1],0,1,0);
				glRotated(cybCore->getZAngle() + cybCore->layerRot[j][2],0,0,1);
				glTranslated(-cybCore->cX, -cybCore->cY, -cybCore->cZ);
	
				glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[j]);
	
				if(cybCore->isDeformableLayer(j))
				for(itc.initialize(), l = 0; itc.notFinish(); ++itc, l++)
				{
					v0 = cybCore->mesh[j]->getVertex(itc->getVertexId(0));
					v1 = cybCore->mesh[j]->getVertex(itc->getVertexId(1));
					v2 = cybCore->mesh[j]->getVertex(itc->getVertexId(2));
	
					glBegin(getViewMode());
					glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
					glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));
	
					glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
					glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));
	
					glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
					glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}
				else glCallList(objects[j]);
				glLoadIdentity();
			}
		}
	
		glFlush();
		glLoadIdentity();
	
		// right camera 1
	
		// blue object
		glClear(GL_DEPTH_BUFFER_BIT);
	
		// Left Eye
	
		glMatrixMode(GL_PROJECTION);
	
	
		if(cybCore->modified == 1)	
		{
			cybCore->rightFrustumRightEye = cybCore->widthProportion*(cybCore->dfXRange/2 + frustumAssimetry);
			cybCore->leftFrustumRightEye = cybCore->widthProportion*(-cybCore->dfXRange/2 + frustumAssimetry);
			cybCore->modified = 0;
		}
		glLoadIdentity();
	
		glFrustum (cybCore->leftFrustumRightEye, cybCore->rightFrustumRightEye, cybCore->widthProportion*cybCore->FrustumBase, cybCore->heightProportion*cybCore->FrustumTop, cybCore->dfNearClipDistance, cybCore->dfFarClipDistance);
	
		glTranslated(-cybCore->dfXMidpoint + cybCore->dfStereoCameraOffset, 0, 0);
	
		gluLookAt(0, 0, cybCore->camPosZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glColorMask(0,0,1,1);
		glColor4f(0, 0, 1, 1);
		
		glTranslated(-cybCore->getParalaxe(),0,0);
	
		//If there is one or more interators, draw it.
		if(cybCore->getNumInterators() > 0)
		{
			glPushMatrix();
	
			glEnable(GL_TEXTURE_2D);

			//Interator objects
			int numInterators = cybCore->getNumInterators();
			for (int i = 0; i < numInterators; i++) {
				CybInterator* interator = cybCore->getInterator(i);
				interator->drawInterator();
			}
			glPopMatrix();
			glLoadIdentity();
		}
		
		glTranslated(-cybCore->getParalaxe(),0,0);

		for(int k=0; k<cybCore->numLayer; k++)
		{
			if(cybCore->habLayer[k] == 1)
			{
				mfCellsIterator<cybSurfaceTriTraits> itc(cybCore->mesh[k]);
	
				glColor4f(0, 0, 1, cybCore->getColor(k)[3]);
	
				// transformations
				glTranslated(cybCore->xTrans + cybCore->layerTrans[k][0], cybCore->yTrans + cybCore->layerTrans[k][1], cybCore->zTrans + cybCore->layerTrans[k][2]);
				glScaled(cybCore->xScale * cybCore->layerSca[k][0], cybCore->yScale * cybCore->layerSca[k][1], cybCore->zScale * cybCore->layerSca[k][2]);
				glTranslated(cybCore->cX, cybCore->cY, cybCore->cZ);
				glRotated(cybCore->getXAngle() + cybCore->layerRot[k][0],1,0,0);
				glRotated(cybCore->getYAngle() + cybCore->layerRot[k][1],0,1,0);
				glRotated(cybCore->getZAngle() + cybCore->layerRot[k][2],0,0,1);
				glTranslated(-cybCore->cX, -cybCore->cY, -cybCore->cZ);
	
				if(cybCore->isDeformableLayer(k))
				for(itc.initialize(); itc.notFinish(); ++itc)
				{
					v0 = cybCore->mesh[k]->getVertex(itc->getVertexId(0));
					v1 = cybCore->mesh[k]->getVertex(itc->getVertexId(1));
					v2 = cybCore->mesh[k]->getVertex(itc->getVertexId(2));
	
					glBegin(getViewMode());
					glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
					glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));
	
					glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
					glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));
	
					glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
					glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}
				else glCallList(objects[k]);
				glLoadIdentity();
			}
		}
	
		if(!k)
		{
			cybCore->transforChange = true;
			k = true;
		}
	
		glFlush();
		glLoadIdentity();
	
		glutSwapBuffers();
	}
