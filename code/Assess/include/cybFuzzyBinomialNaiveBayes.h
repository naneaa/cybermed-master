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

#ifndef _CYB_FuzzyBinomialNaiveBayes_H_
#define _CYB_FuzzyBinomialNaiveBayes_H_

/**
 * @class	CybFuzzyBinomialNaiveBayes
 * @file	CybFuzzyBinomialNaiveBayes.h
 * @short	.
 *
 * .
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.1.1
 * @date	2017, May
 * 
 */
 
class CybFuzzyBinomialNaiveBayes : public CybFuzzyProbability
{	

	private:
		vector<float> probability;

		/** Parameter N from the Binomial Distribution **/
		vector<int> N; 

	public:
	/**
	 * Constructor.
	 */
	CybFuzzyBinomialNaiveBayes(int);

	CybFuzzyBinomialNaiveBayes(int, int);
	
	/**
	 * Destructor.
	 */
	~CybFuzzyBinomialNaiveBayes();
	
	vector<float> getProbability();
	
	void setProbability(vector<float>);

	vector<int> getN();
	
	void setN(vector<int>);

	virtual void training();

	virtual double assessment(CybVectorND<float>*);
	
	protected:
	
	void parametersEstimation();



};

#endif
