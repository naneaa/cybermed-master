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

#ifndef CYBVIEWSHUTTER_H
#define CYBVIEWSHUTTER_H

#include "cyb3DWorld.h"


/**
@class		CybViewShutter 
@file		cybViewShutter.h 
@short
	Visualization methods class that include shutter stereo
	

@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version 1.0
@date 2007, July
 */
 
class CybViewShutter: public Cyb3DWorld
{
public:

	/**
	* Constructor
	*
	* @param CybMouse* mouse The CybMouse object associated with this visualization.
	*
	*/
	CybViewShutter(CybMouse* mouse = NULL);
	/**	Initializes the visualization, creates the window and draws the objects.
	@param int viewing_type
	@param sMesh mesh
	@return void
	*/

protected:
	/**	Display function.
	@param void
	@return void
	*/
	void display();
};

#endif /* CYBVIEWSHUTTER_H */
