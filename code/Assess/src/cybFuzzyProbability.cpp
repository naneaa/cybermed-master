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

void CybFuzzyProbability::calcPertinences()
{
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	
	//1st - calculate sturges
	int sturges = 1 + 
	
	
	
	
	
}
