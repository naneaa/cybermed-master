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
#include "myViewMono.h"
#include <iostream>
#include <cybermed/cyb5DTGlove.h>


	
	
void MyViewMono::keyboard(unsigned char key, int x, int y) {
		CybParameters *cybCore = CybParameters::getInstance();
		CybInterator *interator;
		Cyb5DTGlove *glove;
		
		switch (key) {
			/*Stop the auto calibrate*/
			case '1': 
				interator = cybCore->getInterator(0);
				glove = dynamic_cast<Cyb5DTGlove *>(interator->getDevice());
				glove->setAutoCalibrate(false);
				std::cout << "Auto calibrate disabled!" << std::endl;
				break;	
			
			/*Reset the calibration*/
			case '2': 
				interator = cybCore->getInterator(0);
				glove = dynamic_cast<Cyb5DTGlove *>(interator->getDevice());
				glove->resetCalibration();
				std::cout << "Calibration reseted!" << std::endl;
				break;	
				
			/*Save the Calibration*/	
			case '3':
				interator = cybCore->getInterator(0);
				glove = dynamic_cast<Cyb5DTGlove *>(interator->getDevice());
				glove->saveCalibration("calibration.cal");
				std::cout << "Calibration saved!" << std::endl;
				break;	
				
			/*Load the Calibration*/	
			case '4':
				interator = cybCore->getInterator(0);
				glove = dynamic_cast<Cyb5DTGlove *>(interator->getDevice());
				glove->loadCalibration("calibration.cal");
				std::cout << "Calibration loaded!" << std::endl;
				break;	
			}		
}
