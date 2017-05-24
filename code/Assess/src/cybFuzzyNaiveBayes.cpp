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

#include "cybFuzzyNaiveBayes.h"

CybFuzzyNaiveBayes::CybFuzzyNaiveBayes(int variables)
	: CybFuzzyProbability(variables)
{

}


CybFuzzyNaiveBayes::CybFuzzyNaiveBayes(int variables, int nIntervals)
	: CybFuzzyProbability(variables, nIntervals)
{
	probability = new CybMatrix < pair< pair<double, double>, double> >(nIntervals, variables);
}


CybFuzzyNaiveBayes::~CybFuzzyNaiveBayes()
{

}

CybMatrix < pair< pair<double, double>, double> >* CybFuzzyNaiveBayes::getProbability()
{
	return probability;
}

double CybFuzzyNaiveBayes::getLogProbability(float data, int variable)
{
	for(int l = 0; l < nIntervals; l++)
	{
		if(l == nIntervals - 1){
			if(data >= (*this->getProbability())[l][variable].first.first && data <= (*this->getProbability())[l][variable].first.second)
				return log((*this->getProbability())[l][variable].second);
		} else if(data >= (*this->getProbability())[l][variable].first.first && data < (*this->getProbability())[l][variable].first.second)
			return log((*this->getProbability())[l][variable].second);
	}
	return 0;
}

void CybFuzzyNaiveBayes::setProbability(CybMatrix < pair< pair<double, double>, double> >* probability)
{
	this->probability = probability;
}

void CybFuzzyNaiveBayes::training()
{
	//1st - calculate pertinences
	calcPertinences();
	
	//2nd - estimate parameters
	parametersEstimation();
}

double CybFuzzyNaiveBayes::assessment(CybVectorND<float>* auxdata)
{
	float* data = auxdata->toArray();

	double density = 0.0;
	for(int i = 0; i < getVariablesNumber(); i++)
		density += getLogProbability(data[i], i) + getLogPertinence(data[i], i);
	
	return density;
}

void CybFuzzyNaiveBayes::parametersEstimation()
{
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	 
	//1st - calculate sturges
	int sturges = round(1 + (3.322*log10(size)));

	probability = new CybMatrix < pair< pair<double, double>, double> >(sturges, getVariablesNumber());
	
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		//2nd - get max and min
		float max = data->pos(i)->operator[](0);
		float min = data->pos(i)->operator[](0);
		
		for(int j = 1; j < size; j++){
			if(max < data->pos(i)->operator[](j))
				max = data->pos(i)->operator[](j);
			if(min > data->pos(i)->operator[](j))
				min = data->pos(i)->operator[](j);
		}
		
		//3rd - calculate frequencies	
		vector < pair < pair < double, double >, double > > freq(sturges);
		double step = (max - min)/sturges;
		
		for(int l = 0; l < sturges; l++)
		{
			freq[l].first.first = min + step * l;
			freq[l].first.second = freq[l].first.first + step;
		}
		
		for(int l = 0; l < sturges; l++)
			freq[l].second = 0;
		
		for(int j = 0; j < size; j++)
			for(int l = 0; l < sturges; l++){
				if(l == sturges - 1){
					if(data->pos(i)->operator[](j) >= freq[l].first.first && data->pos(i)->operator[](j) <= freq[l].first.second)
						freq[l].second += 1;
				}else if(data->pos(i)->operator[](j) >= freq[l].first.first && data->pos(i)->operator[](j) < freq[l].first.second)
					freq[l].second += 1;
			}

		//4th - calculate relative frequencies
		for(int l = 0; l < sturges; l++){
			(*probability)[l][i].first.first = freq[l].first.first;
			(*probability)[l][i].first.second = freq[l].first.second;
			(*probability)[l][i].second = freq[l].second/size;
		}
	}
}
	

