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

#include "cybFuzzyBetaNaiveBayes.h"

CybFuzzyBetaNaiveBayes::CybFuzzyBetaNaiveBayes(int variables)
	: CybFuzzyProbability(variables), alpha(variables), beta(variables)
{

}

CybFuzzyBetaNaiveBayes::CybFuzzyBetaNaiveBayes(int variables, int nIntervals)
	: CybFuzzyProbability(variables, nIntervals), alpha(variables), beta(variables)
{
	
}

CybFuzzyBetaNaiveBayes::~CybFuzzyBetaNaiveBayes()
{

}

void CybFuzzyBetaNaiveBayes::setAlpha(vector<float> alpha)
{
	this->alpha = alpha;
}

vector<float> CybFuzzyBetaNaiveBayes::getAlpha()
{
	return alpha;
}

void CybFuzzyBetaNaiveBayes::setBeta(vector<float> beta)
{
	this->beta = beta;
}

vector<float> CybFuzzyBetaNaiveBayes::getBeta()
{
	return beta;
}

void CybFuzzyBetaNaiveBayes::training()
{
	//1st - calculate pertinences
	calcPertinences();
	
	//2nd - estimate parameters
	parametersEstimation();
}

double CybFuzzyBetaNaiveBayes::assessment(CybVectorND<float>* auxdata)
{
	float* data = auxdata->toArray();

	double density = 0.0;
	for(int i = 0; i < getVariablesNumber(); i++)
		density += getLogPertinence(data[i], i) + log(tgamma(alpha[i] + beta[i]))
				- (log(tgamma(alpha[i])) + log(tgamma(beta[i]))) + ((alpha[i] - 1) * log(data[i])) 
				+ ((beta[i] - 1) * log(1 - data[i]));
		
	return density;
}

void CybFuzzyBetaNaiveBayes::parametersEstimation()
{
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();

	//1st - calculate mean
	vector<float> mean(getVariablesNumber());
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		for(int j = 0; j < size; j++)
		{
			mean[i] += data->pos(i)->operator[](j);
		}
		mean[i] /= size;
	}

	//2nd - calculate standard deviation
	vector<float> variance(getVariablesNumber());
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		for(int j = 0; j < size; j++)
		{
			variance[i] += pow(data->pos(i)->operator[](j) - mean[i], 2);
		}
		variance[i] /= (size - 1);
	}

	for(int i = 0; i < getVariablesNumber(); i++)
	{
		variance[i] = (size - 1) * (variance[i] / size); //fator de correcao populacional
	}

	//1st - estimate alpha
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		alpha[i] = mean[i]*(((mean[i] * (1 - mean[i]))/variance[i]) - 1);
	}	
	
	//2nd - estimate beta
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		beta[i] = (alpha[i]/mean[i]) - alpha[i];
	}	
	
	
	
}
