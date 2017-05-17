// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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

#include "cybOBBDrawer.h"

CybOBBDrawer::CybOBBDrawer(CybVector3D<double>* matrix, CybVector3D<double>& center, CybVector3D<double>& sizes)
{
		CybMatrix<double>* baseOBB = new CybMatrix<double>(3,3);
		baseOBB->setMatrix(matrix);
		CybMatrix<double>* baseCanon = new CybMatrix<double>(3,3);
		baseCanon->setIdentity();

		//Calculating the transformation matrix from the canonic base to the OBB base.
		canonToOBB = &(getTransformationMatrix(*baseCanon, *baseOBB));

		//Calculating the transformation matrix from the OBB base to the canonic base.
		OBBToCanon = &(getTransformationMatrix(*baseOBB, *baseCanon));


		//Projecting center and sizes
		CybMatrix<double>* c2 = new CybMatrix<double>(1,3);
		CybMatrix<double>* s2 = new CybMatrix<double>(1,3);
		c2->setMatrix(center);
		s2->setMatrix(sizes);
		centerMatrix = c2;
		sizesMatrix = s2;
		*centerMatrix = ((*c2) * (*OBBToCanon));
		for(int i = 0; i < 3; ++i){
			CybMatrix<double> auxPos(1,3), auxNeg(1,3);
			auxPos[0][i] = center[i] + sizes[i];
			auxNeg[0][i] = center[i] - sizes[i];
			auxPos = auxPos * (*OBBToCanon);
			auxNeg = auxNeg * (*OBBToCanon);
			(*sizesMatrix)[0][i] = (auxPos[0][i] - auxNeg[0][i])/2.0;
		}

		//Initializing transformation vectors.
		scale(1,1,1);
		translation(0,0,0);
		rotation(0,0,0);
		
		CybBoxHolder::getInstance()->addBox(this);

		delete baseOBB;
		delete baseCanon;
}

void CybOBBDrawer::drawBox()
{
	CybVector3D<double> center((*centerMatrix)(0,0), (*centerMatrix)(0,1), (*centerMatrix)(0,2));
	CybVector3D<double> sizes((*sizesMatrix)(0,0), (*sizesMatrix)(0,1), (*sizesMatrix)(0,2));
	glPushMatrix();
	glTranslated(translation[0], translation[1], translation[2]);
      	glScaled(scale[0], scale[1], scale[2]);
	glRotated(rotation[0],1,0,0);
	glRotated(rotation[1],0,1,0);
	glRotated(rotation[2],0,0,1);
	glColor3d(0,0,1);
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
	glEnd();
	glPopMatrix();
}

CybMatrix<double>* CybOBBDrawer::getCenter()
{
	return centerMatrix;
}

CybVector3D<double>& CybOBBDrawer::getScale()
{
	return scale;
}

CybMatrix<double>* CybOBBDrawer::getSizes()
{
	return sizesMatrix;
}

CybMatrix<double>& CybOBBDrawer::getTransformationMatrix(CybMatrix<double>& initial, CybMatrix<double>& goal)
{
	CybMatrix<double>* aux = new CybMatrix<double>(initial.getDimension2(), initial.getDimension1());
	*aux = initial.transpose();
	CybMatrix<double>* results = new CybMatrix<double>(goal.getDimension1(), goal.getDimension2());
	for(int i = 0; i < goal.getDimension1(); ++i){
		CybMatrix<double>* sisMat = new CybMatrix<double>(goal.getDimension1(), goal.getDimension2() + 1);
		for(int j = 0; j < sisMat->getDimension1(); ++j){
			for(int k = 0; k < sisMat->getDimension2(); ++k){
				if(k != sisMat->getDimension1()) (*sisMat)[j][k] = (*aux)(j,k);
				else (*sisMat)[j][k] = goal[i][j];
			}
		}
		double* r = solveSystem(*sisMat);
		for(int l = 0; l < goal.getDimension2(); ++l) (*results)(i,l) = r[l]; 
	}
	results->transpose();
	return *results;
}

CybVector3D<double>& CybOBBDrawer::getTranslation()
{
	return translation;
}

void CybOBBDrawer::setCenter(CybMatrix<double>* center)
{
	*(this->centerMatrix) = ((*center) * (*OBBToCanon));
}

void CybOBBDrawer::setScale(CybVector3D<double>& scale)
{
	this->scale = scale;
}

void CybOBBDrawer::setSizes(CybMatrix<double>* sizes)
{
	this->sizesMatrix = sizes;
}

void CybOBBDrawer::setTranslation(CybVector3D<double>& translation)
{
	this->translation = translation;
}

double* CybOBBDrawer::solveSystem(CybMatrix<double>& matrix)
{
	double* results = new double[3];
	matrix.toUpperTriangular();
	results[2] = matrix[2][3]/matrix[2][2];
        results[1] = (matrix[1][3] + (-1 * results[2] * matrix[1][2]))/ matrix[1][1];
        results[0] = (matrix[0][3] + (-1 * results[2] * matrix[0][2]) + (-1 * results[1] * matrix[0][1]))/matrix[0][0];
        return results;
}

void CybOBBDrawer::updateLocalRotation(CybVector3D<double>& newCenter, CybVector3D<double>& newSizes)
{
	CybMatrix<double> nc(newCenter);
	*centerMatrix = (nc * (*OBBToCanon));
	for(int i = 0; i < 3; ++i){
		CybMatrix<double> auxPos(1,3), auxNeg(1,3);
		auxPos[0][i] = newCenter[i] + newSizes[i];
		auxNeg[0][i] = newCenter[i] - newSizes[i];
		auxPos = auxPos * (*OBBToCanon);
		auxNeg = auxNeg * (*OBBToCanon);
		(*sizesMatrix)[0][i] = (auxPos[0][i] - auxNeg[0][i])/2.0;
	}
}	

void CybOBBDrawer::updateLocalScale(CybVector3D<double>& newCenter, CybVector3D<double>& newSizes)
{
	CybMatrix<double> auxC(newCenter);
	CybMatrix<double> auxS(newSizes);
	auxC = auxC * (*OBBToCanon);
	*centerMatrix = auxC;
	for(int i = 0; i < 3; ++i){
		CybMatrix<double> auxPos(1,3), auxNeg(1,3);
		auxPos[0][i] = auxC[0][i] + newSizes[i];
		auxNeg[0][i] = auxC[0][i] - newSizes[i];
		auxPos = auxPos * (*OBBToCanon);
		auxNeg = auxNeg * (*OBBToCanon);
		(*sizesMatrix)[0][i] = (auxPos[0][i] - auxNeg[0][i])/2.0;
	}
}

void CybOBBDrawer::updateLocalTranslation(CybVector3D<double>& newCenter)
{
	CybMatrix<double> aux(newCenter);
	aux = aux * (*OBBToCanon);
	*centerMatrix = aux;
}

CybVector3D<double>& CybOBBDrawer::updateGlobalRotation(int axis, double angle)
{
	CybVector3D<double>* newCenter = new CybVector3D<double>();
	CybMatrix<double> auxC = (*centerMatrix);
	double radAng = PI * angle / 180.0;
	double seno = sin(radAng);
	double cosseno = cos(radAng);
	if(axis == 0){
		rotation[0] = angle;
		double rotVecX[9] = {1,0,0,0, cosseno, -seno, 0, seno, cosseno};
		CybMatrix<double> rotMatX(3,3,rotVecX);
		auxC = auxC * rotMatX;		
	}else if(axis == 1){
		rotation[1] = angle;
		double rotVecY[9] = {cosseno, 0, seno, 0, 1, 0, -seno, 0, cosseno};
		CybMatrix<double> rotMatY(3,3,rotVecY);
		auxC = auxC * rotMatY;
	}else{
		rotation[2] = angle;
		double rotVecZ[9] = {cosseno, -seno, 0, seno, cosseno, 0, 0, 0, 1};
		CybMatrix<double> rotMatZ(3,3,rotVecZ);
		auxC = auxC * rotMatZ;
	}	
	auxC = auxC * (*canonToOBB);
	for(int i = 0; i < 3; ++i) (*newCenter)[i] = auxC[0][i];
	return *newCenter;
		
}

void CybOBBDrawer::updateGlobalScale(CybVector3D<double>& globScale)
{
	scale = globScale;
}	

void CybOBBDrawer::updateGlobalTranslation(CybVector3D<double>& globTrans)
{
	translation = globTrans;
}


