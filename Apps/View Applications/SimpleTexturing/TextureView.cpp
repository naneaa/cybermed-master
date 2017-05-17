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

#include "TextureView.h"

	TextureView::TextureView(CybMouse* mouse) : Cyb3DWorld(mouse)  {
		Cyb3DWorld : viewNumber = 1; //sets the visualization type
	}	

	
	void  TextureView::display()
	{
		CybParameters *cybCore = CybParameters::getInstance();
		

		double frustumAssimetry;
		static bool k = false;
	
		sVertex *v0, *v1, *v2;
		int l, index;
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0,0,0,0);
		glDrawBuffer(GL_BACK);
	
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		glMatrixMode(GL_PROJECTION);
	
		if(cybCore->modified == 1)
		{
			frustumAssimetry = cybCore->StereoProjection(-6.4, 6.4, -6.4, 6.4, 6.0, -6.0, 180, 14.5, -cybCore->getStereoMagnitude(), cybCore->getParalaxe());
			cybCore->rightFrustumLeftEye = cybCore->widthProportion*(cybCore->dfXRange/2 - frustumAssimetry);
			cybCore->leftFrustumLeftEye = cybCore->widthProportion*(-cybCore->dfXRange/2 - frustumAssimetry);
			cybCore->modified = 0;
		}
		glLoadIdentity();
	
		glFrustum(cybCore->leftFrustumLeftEye, cybCore->rightFrustumLeftEye, cybCore->widthProportion*cybCore->FrustumBase, cybCore->heightProportion*cybCore->FrustumTop, cybCore->dfNearClipDistance, cybCore->dfFarClipDistance);
	
		gluLookAt(0, 0, cybCore->camPosZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		if(cybCore->getNumInterators() > 0)
		{
			glPushMatrix();

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
	
		for(int j=0; j < cybCore->numLayer; j++)	
		{
			if(cybCore->habLayer[j] == 1)
			{
				//ofCellsIterator<cybTraits> cellsIterator(cybCore->mesh[j]);
				mfCellsIterator<cybSurfaceTriTraits> cellsIterator(cybCore->mesh[j]);
	
				CybVector4D<float> color = cybCore->getColor(j);

				glColor4f(color[0], color[1], color[2], color[3]);
				CybThread::lock();
				// transformations
				glTranslated(cybCore->xTrans + cybCore->layerTrans[j][0], cybCore->yTrans + cybCore->layerTrans[j][1], cybCore->zTrans + cybCore->layerTrans[j][2]);
				glScaled(cybCore->xScale * cybCore->layerSca[j][0], cybCore->yScale * cybCore->layerSca[j][1], cybCore->zScale * cybCore->layerSca[j][2]);
				glTranslated(cybCore->cX, cybCore->cY, cybCore->cZ);
				glRotated(cybCore->getXAngle() + cybCore->layerRot[j][0],1,0,0);
				glRotated(cybCore->getYAngle() + cybCore->layerRot[j][1],0,1,0);
				glRotated(cybCore->getZAngle() + cybCore->layerRot[j][2],0,0,1);
				glTranslated(-cybCore->cX, -cybCore->cY, -cybCore->cZ);

                                
	
				     glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[j]);

	            CybThread::unlock();

glBindTexture(GL_TEXTURE_2D, cybCore->texture[0]);
	glEnable(GL_TEXTURE_2D);
				for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
				{
	
					v0 = cybCore->mesh[j]->getVertex(cellsIterator->getVertexId(0));
					v1 = cybCore->mesh[j]->getVertex(cellsIterator->getVertexId(1));
					v2 = cybCore->mesh[j]->getVertex(cellsIterator->getVertexId(2));
	
					glBegin(getViewMode()); //Mesh drawing
					glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
					glTexCoord2f(0.0f, 0.0f);glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));
	
					glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
	
					glTexCoord2f(1.0f, 0.0f);glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));
	
					glTexCoord2f(1.0f, 1.0f);glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
	
					glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}

	/**-------------------------------TESTE COM TEXTURAS------------------------------------**/
/*	glBindTexture(GL_TEXTURE_2D, cybCore->texture[0]);
	glEnable(GL_TEXTURE_2D);	
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-34,-34,0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(34,-34,0);		
		glTexCoord2f(1.0f, 1.0f);glVertex3f(34,34,0);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-34,34,0);
	glEnd();
*/
				glLoadIdentity();
			}
		}
	
	
		if(!k)
		{
			cybCore->transforChange = true;
			k = true;
		}
	
	
		glLoadIdentity();
	
		glutSwapBuffers();
	
	}
