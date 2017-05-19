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

#ifndef _CYB_FuzzyExponentialNaiveBayes_H_
#define _CYB_FuzzyExponentialNaiveBayes_H_

/**
 * @class	CybFuzzyExponentialNaiveBayes
 * @file	CybFuzzyExponentialNaiveBayes.h
 * @short	.
 *
 * .
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.1.1
 * @date	2017, May
 * 
 */
 
class CybFuzzyExponentialNaiveBayes : public CybFuzzyProbability
{	

	private:
		CybVectorND<float> parameters;

	public:
	/**
	 * Constructor.
	 */
	CybFuzzyExponentialNaiveBayes(int);
	
	/**
	 * Destructor.
	 */
	~CybFuzzyExponentialNaiveBayes();
	
	CybVectorND<float> getParameters();
	
	void setParameters(CybVectorND<float>);

	virtual void training();

	virtual double assessment(CybVectorND<float>*);
	
	protected:
	
	void parametersEstimation();



};

#endif
