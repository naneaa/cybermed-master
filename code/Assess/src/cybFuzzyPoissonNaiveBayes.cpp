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

#include "cybFuzzyPoissonNaiveBayes.h"

CybFuzzyPoissonNaiveBayes::CybFuzzyPoissonNaiveBayes(int variables)
	: CybFuzzyProbability(variables), parameters(variables)
{

}

CybFuzzyPoissonNaiveBayes::CybFuzzyPoissonNaiveBayes(int variables, int nIntervals)
	: CybFuzzyProbability(variables), parameters(variables)
{
	pertinences = new CybMatrix < pair< pair<double, double>, double> >(nIntervals, variables);
	this -> nIntervals = nIntervals;
}

CybFuzzyPoissonNaiveBayes::~CybFuzzyPoissonNaiveBayes()
{

}

vector<float> CybFuzzyPoissonNaiveBayes::getParameters()
{
	return parameters;
}

void CybFuzzyPoissonNaiveBayes::setParameters(vector<float> parameters)
{
	this->parameters = parameters;
}

void CybFuzzyPoissonNaiveBayes::training()
{
	//1st - calculate pertinences
	calcPertinences();
	
	//2nd - estimate parameters
	parametersEstimation();
}

double CybFuzzyPoissonNaiveBayes::assessment(CybVectorND<float>* auxdata)
{
	float* data = auxdata->toArray();
	
	//previously calculates logs in order to reduce running time
	vector<double> logs (getVariablesNumber(), 0);
	double max = data[0];
	for(int i = 1; i < getVariablesNumber(); i++)
		if(max < data[i])
			max = data[i];
		
	double aux = 0;	
	for(int j = 2; j < max; j++)
	{
		aux += log(j);
		for(int i = 0; i < getVariablesNumber(); i++)
			if(data[i] == j)
				logs[i] = aux;
	}
	
	double density = 0;		
	for(int i = 0; i < getVariablesNumber(); i++)
		density += log(getParameters()[i])*data[i] - getParameters()[i] - logs[data[i]] + getLogPertinence(data[i], i);
	
	return density;
}

void CybFuzzyPoissonNaiveBayes::parametersEstimation()
{
	mfList<CybVectorND<float>*>* data = this->getData();
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
		parameters[i] = mean[i];
	}
}
