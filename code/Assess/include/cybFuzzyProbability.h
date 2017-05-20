// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include "cybAssess.h"
#include "cybMatrix.h"
#include <vector>

#ifndef _CYB_FuzzyProbability_H_
#define _CYB_FuzzyProbability_H_

/**
 * @class	CybFuzzyProbability
 * @file	cybFuzzyProbability.h
 * @short	The base class for all Zadeh's Fuzzy Probability assess methods.
 *
 * This is base class for all assess methods based on Zadeh's 
 * Fuzzy Probability implemented for the CyberMed System.
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.1.1
 * @date	2017, May
 * 
 */
 
class CybFuzzyProbability : public CybAssess
{	
protected:
	CybMatrix < pair< pair<double, double>, double> > *pertinences;
	int nIntervals;
	
public:
	
	/**
	 * Constructor.
	 */
	CybFuzzyProbability(int);
	
	/**
	 * Destructor.
	 */
	~CybFuzzyProbability();
	
	CybMatrix < pair< pair<double, double>, double> >* getPertinences();

	void setPertinences(CybMatrix < pair< pair<double, double>, double> >*);
	
	double getPertinence(float, int);
	
	double getLogPertinence(float, int);
	
	int getNIntervals();
	
	void setNIntervals(int);
	
	virtual void training() = 0;

	virtual double assessment(CybVectorND<float>*) = 0;
		
protected:

	void calcPertinences();
};

#endif /*_CYB_FuzzyProbability_H_*/
