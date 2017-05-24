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
	: CybFuzzyProbability(variables), probability(variables), N(variables)
{

}

CybFuzzyBinomialNaiveBayes::CybFuzzyBinomialNaiveBayes(int variables, int nIntervals)
	: CybFuzzyProbability(variables, nIntervals), probability(variables), N(variables)
{
	
}

CybFuzzyBinomialNaiveBayes::~CybFuzzyBinomialNaiveBayes()
{

}

vector<float> CybFuzzyBinomialNaiveBayes::getProbability()
{
	return probability;
}
	
void CybFuzzyBinomialNaiveBayes::setProbability(vector<float> probability)
{
	this->probability = probability;
}

vector<int> CybFuzzyBinomialNaiveBayes::getN()
{
	return N;
}

void CybFuzzyBinomialNaiveBayes::setN(vector<int> N)
{
	this->N = N;
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

	//previously calculates logs in order to reduce running time
	double max = data[0];
	for(int i = 1; i < getVariablesNumber(); i++)
		if(max < data[i])
			max = data[i];
		
	vector<double> logs (max, 0);	
	for(int j = 2; j < max; j++)
	{
		logs[j] = logs[j-1] + log(j);
	}

	double density = 0.0;
	for(int i = 0; i < getVariablesNumber(); i++)
		density += getLogPertinence(data[i], i) + logs[N[i]] - (logs[data[i]] 
				+ logs[N[i] - data[i]]) + (data[i] * log(probability[i])) 
				+ ((N[i] - data[i]) * log(1 - probability[i]));
		
	return density;
}

void CybFuzzyBinomialNaiveBayes::parametersEstimation()
{
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	 
	//1st - estimate N
	for(int i = 0; i < getVariablesNumber(); i++)
		for(int j = 0; j < size; j++)
			if(N[i] < data->pos(i)->operator[](j))
				N[i] = data->pos(i)->operator[](j);

	//2nd - estimate probability p
	double c1 = 0.1, c2 = 1;
	for(int i = 0; i < getVariablesNumber(); i++)
		for(int j = 0; j < size; j++)
				probability[i] += data->pos(i)->operator[](j);
	
	for(int i = 0; i < getVariablesNumber(); i++)
		probability[i] = (c1 + probability[i])/(c2 + size);

	for(int i = 0; i < getVariablesNumber(); i++)
		probability[i] = probability[i]/N[i];
}
