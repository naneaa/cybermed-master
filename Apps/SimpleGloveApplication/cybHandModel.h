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

#ifndef CYBHANDMODEL_H_
#define CYBHANDMODEL_H_

/**
	@class CybHandModel
	@file cybHandModel.h 
	@short
			
		This class is a CybModel. This Model is a hand that receives values for the fingers rotation.
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2011, October
*/

#include <string>
#include <cybermed/cybModel.h>
//#include <cybermed/cybGlove.h>
//#include <cybermed/cybUpdateModel.h> ja herda
#include <cybermed/cybDevice.h>

using namespace std;

class CybHandModel: public CybModel {
	
	public:
		/** Construcor */	
		CybHandModel();
		/** Draw the model
		@param void
		@return void
		*/
		virtual void draw();

		
		/** sets how the model should be updated
		@param string
		@return void
		*/
		virtual void setUpdateModel(string type);
		/** update the array eixo
		@param floar []
		@return void
		*/
		void setEixos(float eixos[]);		
		
	private:
		float eixo[18]; //values used by the model for the fingers rotation
		
};

#endif
