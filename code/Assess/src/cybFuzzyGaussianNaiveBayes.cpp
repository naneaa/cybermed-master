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

#include "cybFuzzyGaussianNaiveBayes.h"

CybFuzzyGaussianNaiveBayes::CybFuzzyGaussianNaiveBayes(int variables)
	: CybFuzzyProbability(variables), mean(variables), stdDev(variables)
{

}

CybFuzzyGaussianNaiveBayes::~CybFuzzyGaussianNaiveBayes()
{

}

vector<float>& CybFuzzyGaussianNaiveBayes::getMean()
{
	return mean;
}
	
void CybFuzzyGaussianNaiveBayes::setMean(vector<float>& mean)
{
	this->mean = mean;
}

vector<float>& CybFuzzyGaussianNaiveBayes::getStdDev()
{
	return stdDev;
}
	
void CybFuzzyGaussianNaiveBayes::setStdDev(vector<float>& stdDev)
{
	this->stdDev = stdDev;
}

void CybFuzzyGaussianNaiveBayes::training()
{
	//1st - calculate pertinences
	calcPertinences();
	
	//2nd - estimate parameters
	parametersEstimation();
}

double CybFuzzyGaussianNaiveBayes::assessment(CybVectorND<float>* auxdata)
{
	float* data = auxdata->toArray();
	
	double density = 0;		
	for(int i = 0; i < getVariablesNumber(); i++)
		density += log(1/stdDev[i]) - (pow(data[i] - mean[i], 2)/(2 * pow(stdDev[i], 2))) + getLogPertinence(data[i], i);
	
	return density;
}

void CybFuzzyGaussianNaiveBayes::parametersEstimation()
{
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	 
	//1st - calculate mean
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
		for(int j = 0; j < size; j++)
		{
			stdDev[i] += pow(data->pos(i)->operator[](j) - mean[i], 2);
		}
		stdDev[i] /= (size - 1);
	}
}
