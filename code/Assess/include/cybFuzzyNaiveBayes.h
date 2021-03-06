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

#include "cybFuzzyProbability.h"

#ifndef _CYB_FuzzyNaiveBayes_H_
#define _CYB_FuzzyNaiveBayes_H_

/**
 * @class	CybFuzzyNaiveBayes
 * @file	CybFuzzyNaiveBayes.h
 * @short	.
 *
 * .
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.1.1
 * @date	2017, May
 * 
 */
 
class CybFuzzyNaiveBayes : public CybFuzzyProbability
{	

	private:

	CybMatrix < pair< pair<double, double>, double> > *probability;

	public:
	/**
	 * Constructor.
	 */
	CybFuzzyNaiveBayes(int);

	CybFuzzyNaiveBayes(int, int);
	
	/**
	 * Destructor.
	 */
	~CybFuzzyNaiveBayes();
	
	CybMatrix < pair< pair<double, double>, double> >* getProbability();
	
	void setProbability(CybMatrix < pair< pair<double, double>, double> >*);

	double getLogProbability(float, int);

	virtual void training();

	virtual double assessment(CybVectorND<float>*);
	
	protected:
	
	void parametersEstimation();



};

#endif
