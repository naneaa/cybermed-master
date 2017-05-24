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

CybFuzzyProbability::CybFuzzyProbability(int variables)
	: CybAssess(variables)
{
	
}

CybFuzzyProbability::CybFuzzyProbability(int variables, int nIntervals)
	: CybAssess(variables)
{
	pertinences = new CybMatrix < pair< pair<double, double>, double> >(nIntervals, variables);
	this -> nIntervals = nIntervals;
}

CybFuzzyProbability::~CybFuzzyProbability()
{
	delete pertinences;
}

CybMatrix < pair< pair<double, double>, double> >* CybFuzzyProbability::getPertinences()
{
	return pertinences;
}

void CybFuzzyProbability::setPertinences(CybMatrix < pair< pair<double, double>, double> >* pertinences)
{
	this->pertinences = pertinences;
}

int CybFuzzyProbability::getNIntervals()
{
	return nIntervals;
}

void CybFuzzyProbability::setNIntervals(int nIntervals)
{
	this->nIntervals = nIntervals;
}

double CybFuzzyProbability::getPertinence(float data, int variable)
{
	for(int l = 0; l < nIntervals; l++){
		if(l == nIntervals - 1){
			if(data >= (*this->getPertinences())[l][variable].first.first && data <= (*this->getPertinences())[l][variable].first.second)
				return (*this->getPertinences())[l][variable].second;
		} else if(data >= (*this->getPertinences())[l][variable].first.first && data < (*this->getPertinences())[l][variable].first.second)
			return (*this->getPertinences())[l][variable].second;
	}
	return 0;
}

double CybFuzzyProbability::getLogPertinence(float data, int variable)
{
	for(int l = 0; l < nIntervals; l++)
	{
		if(l == nIntervals - 1){
			if(data >= (*this->getPertinences())[l][variable].first.first && data <= (*this->getPertinences())[l][variable].first.second)
				return log((*this->getPertinences())[l][variable].second);
		} else if(data >= (*this->getPertinences())[l][variable].first.first && data < (*this->getPertinences())[l][variable].first.second)
			return log((*this->getPertinences())[l][variable].second);
	}
	return 0;
}

void CybFuzzyProbability::calcPertinences()
{	
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	
	//1st - calculate sturges
	int sturges = round(1 + (3.322*log10(size)));
	nIntervals = sturges;

	pertinences = new CybMatrix < pair< pair<double, double>, double> >(sturges, getVariablesNumber());
	
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
			
		//for(int l = 0; l < sturges; l++)
		//	cout << freq[l].first.first << " |- " << freq[l].first.second << "\t" << freq[l].second << endl;
		//cout << endl;	
		//4th - calculate relative frequencies
		for(int l = 0; l < sturges; l++){
			freq[l].second = freq[l].second/size;
			//cout << freq[l].second << endl;
		}
		
		//5th - calculate pertinences
		double maxFreq = freq[0].second;
		for(int l = 1; l < sturges; l++)
			if(maxFreq < freq[l].second)
				maxFreq = freq[l].second;
				
		for(int l = 0; l < sturges; l++)
		{
			(*pertinences)[l][i].first.first = freq[l].first.first;
			(*pertinences)[l][i].first.second = freq[l].first.second;
			if(freq[l].second == 0)
				(*pertinences)[l][i].second = 0.001;
			else
				(*pertinences)[l][i].second = freq[l].second/maxFreq;
		} /*CybMatrix < pair< pair<double, double>, double> > *pertinences;*/
	}
}
