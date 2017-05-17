// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2016 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include "cybAssess.h"
#include "cybMatrix.h"

#ifndef _CYB_ProbabilityFuzzyParameters_H_
#define _CYB_ProbabilityFuzzyParameters_H_

/**
 * @class	CybProbabilityFuzzyParameters
 * @file	cybProbabilityFuzzyParameters.h
 * @short	The base class for all Bucley's Fuzzy Probability assess methods.
 *
 * This is base class for all assess methods based on Bucley's 
 * Fuzzy Probability implemented for the CyberMed System.
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.1.1
 * @date	2016, September
 * 
 */

class CybProbabilityFuzzyParameters : public CybAssess
{	
protected:
	CybMatrix< pair<double, double> > parameters;
	int alphaCuts; // min = 12 comeca 0.01 termina 1.0
	
public:
	
	/**
	 * Constructor.
	 */
	CybProbabilityFuzzyParameters(int, int);
	
	/**
	 * Destructor.
	 */
	~CybProbabilityFuzzyParameters();
		
	CybMatrix< pair<double, double> > getFuzzyParameters();

	void setFuzzyParameters(CybMatrix< pair<double, double> >);
	
	int getAlphaCuts();
	
	void setAlphaCuts(int);

	virtual void training() = 0;

	virtual double assessment(CybVectorND<float>*) = 0;
	
protected:

	virtual void parametersEstimation() = 0;
};

#endif /*_CYB_ProbabilityFuzzyParameters_H_*/
