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

#include "cybFuzzyBinomialNaiveBayes.h"

CybFuzzyBinomialNaiveBayes::CybFuzzyBinomialNaiveBayes(int variables)
	: CybFuzzyProbability(variables), parameters(variables)
{

}

CybFuzzyBinomialNaiveBayes::CybFuzzyBinomialNaiveBayes(int variables, int nIntervals)
	: CybFuzzyProbability(variables), parameters(variables)
{
	pertinences = new CybMatrix < pair< pair<double, double>, double> >(nIntervals, variables);
	this -> nIntervals = nIntervals;
}

CybFuzzyBinomialNaiveBayes::~CybFuzzyBinomialNaiveBayes()
{

}

vector<float>& CybFuzzyBinomialNaiveBayes::getParameters()
{
	return parameters;
}

void CybFuzzyBinomialNaiveBayes::setParameters(vector<float>& parameters)
{
	this->parameters = parameters;
}

void CybFuzzyBinomialNaiveBayes::training()
{
	//1st - calculate pertinences
	calcPertinences();
	
	//2nd - estimate parameters
	parametersEstimation();
}

double CybFuzzyBinomialNaiveBayes::assessment(CybVectorND<float>* auxdata)
{
	float* data = auxdata->toArray();

	double density = 0.0;
	for(int i = 0; i < getVariablesNumber(); i++)
		density += 0.0;
	
		
	return density;
}

void CybFuzzyBinomialNaiveBayes::parametersEstimation()
{
	//estimate

	/*mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	 
	//1st - calculate mean
	vector<double> mean(getVariablesNumber(), 0);
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		for(int j = 0; j < size; j++)
		{
			mean[i] += data->pos(i)->operator[](j);
		}
		mean[i] /= size;
	}

	//2nd - calculate lambda
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		parameters[i] = 1/mean[i];
	}*/
}
