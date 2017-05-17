// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// *****************************************************************

#ifndef CybViewHMD_H
#define CybViewHMD_H

#include "cyb3DWorld.h"

/**
@class		CybViewHMD 
@file		CybViewHMD.h 
@short
	Double window visualization

	NOTE: Requires Twinview to work properly, for more information on the subject, please visit < http://www.nvidia.com/object/feature_twinview.html >
	

@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version 1.0
@date 2012, February
 */


class CybViewHMD : public Cyb3DWorld
{

	public:

	CybViewHMD(CybMouse* mouse = NULL);
	void setResolution(int, int);
	void swapWindowsPositions(void);

	protected:
	
	void display();
	void displayRight();
	void displayLeft();


};

#endif //CybViewHMD_H


