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

CybFuzzyProbability::CybFuzzyProbability(int variables)
	: CybAssess(variables)
{
	
}

CybFuzzyProbability::~CybFuzzyProbability()
{
	delete pertinences;
}

CybMatrix< pair<double, double> > CybFuzzyProbability::getPertinences()
{
	return pertinences;
}

void CybFuzzyProbability::setPertinences(CybMatrix< pair<double, double> > pertinences)
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

void CybFuzzyProbability::calcPertinences(float* auxdata)
{
	int size = auxdata->size();
	
	// adicionar loop for(int i = 0; i < getVariablesNumber(); i++) ao redor
	// pegar dados assim:
	/*
		mfList<CybVectorND<float>*>* data = this->getData();
		int size = data->pos(0)->getDimension();
	*/
	
	//1st - calculate sturges
	int sturges = 1 + (3.322*log(size));
	
	//2nd - get max and min
	float max = auxdata->pos(0);
	float min = auxdata->pos(0);
	
	for(int i = 1; i < size; i++){
		if(max < auxdata[i])
			max = auxdata[i];
		if(min > auxdata[i])
			min = auxdata[i];
	}
	
	//3rd - calculate frequencies and relative frequencies	
	CybVector< pair< pair<double, double>, double> > freq(sturges);
	double step = (max - min)/sturges;
	
	for(int i = 0, i < sturges; i++){
		freq[i].first.first = min + step * i;
		freq[i].first.second = freq[i].first + step;
	}
	
	for(int i = 0, i < sturges; i++)
		freq[i].second = 0;

	for(int j = 0, j < size; j++)
		for(int i = 0, i < sturges; i++)
			if(auxdata[j] >= req[i].first.first && auxdata[j] < req[i].first.second)
				freq[i].second += 1;
			
	for(int i = 0, i < sturges; i++)
		freq[i].second /= freq[i].second/size;
	
	//4th - calculate pertinences
	double maxFreq = freq[0].second;
	for(int i = 1; i < size; i++)
		if(maxFreq < freq[i].second)
			maxFreq = freq[i].second;
		
	for(int i = 0, i < sturges; i++)
		for(int i = 0, i < sturges; i++)
		freq[i].second /= freq[i].second/maxFreq;  
	
}
