// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2016 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
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

#include "cybFuzzyNaiveBayesIO.h"

	
CybFuzzyNaiveBayesIO::CybFuzzyNaiveBayesIO(const char* file_name) : CybAssessIO(file_name, ".cyba_FNB")
{
	
}

CybFuzzyNaiveBayesIO::~CybFuzzyNaiveBayesIO()
{
	
}
		;
void CybFuzzyNaiveBayesIO::write(void* fnbwork)
{
	CybFuzzyNaiveBayes* fnb = (CybFuzzyNaiveBayes*) fnbwork;
	
	ofstream fout(this->getFile(), ofstream::out); 
	
	if(fout.fail())
	{
		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
		
	fout << "##" << fnb->getVariablesNumber() << endl; 
	
	fout << "##" << fnb->getNIntervals() << endl; 

	fout << "\nPertinences\n";
	fout << "**" << endl;
	
	for(int i = 0; i < fnb->getVariablesNumber(); i++)
	{
		for(int j = 0; j < fnb->getNIntervals(); j++)
		{
			fout << "[" << (*fnb->getPertinences())[j][i].first.first << ", " << 
				(*fnb->getPertinences())[j][i].first.second << "]:" << 
				(*fnb->getPertinences())[j][i].second << endl;
		}
		fout << "**" << endl;
	}
	
	fout << "\nProbability\n";
	fout << "**" << endl;
	
	for(int i = 0; i < fnb->getVariablesNumber(); i++)
	{
		for(int j = 0; j < fnb->getNIntervals(); j++)
		{
			fout << "[" << (*fnb->getProbability())[j][i].first.first << ", " << 
				(*fnb->getProbability())[j][i].first.second << "]:" << 
				(*fnb->getProbability())[j][i].second << endl;
		}
		fout << "**" << endl;
	}
	
	fout.close();
}
	
void* CybFuzzyNaiveBayesIO::read()
{
	ifstream fin(this->getFile());
	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo de entrada " << this->getFile() << endl;
		exit(0);
	}
	
	char c;
	int variables, nIntervals;
	
	fin >> c >> c >> variables >> c >> c >> nIntervals;
	
	CybFuzzyNaiveBayes* fnb = new CybFuzzyNaiveBayes(variables, nIntervals);
	
	while(c != '[')
		fin >> c;
		
	CybMatrix < pair< pair<double, double>, double> > *auxPert = new CybMatrix < pair< pair<double, double>, double> > (nIntervals, variables);
	
	for(int i = 0; i < variables; i++)
	{
		for(int j = 0; j < nIntervals; j++)
		{
			double a = 0, b = 0, d = 0;
			fin >> a >> c >> b >> c >> c >> d >> c;
			
			(*auxPert)[j][i].first.first = a;
			(*auxPert)[j][i].first.second = b;
			(*auxPert)[j][i].second = d;		
		}
		fin >> c >> c; 
	}
	
	fnb->setPertinences(auxPert);

	while(c != '[')
		fin >> c;
		
	CybMatrix < pair< pair<double, double>, double> > *auxProb = new CybMatrix < pair< pair<double, double>, double> > (nIntervals, variables);
	
	for(int i = 0; i < variables; i++)
	{
		for(int j = 0; j < nIntervals; j++)
		{
			double a = 0, b = 0, d = 0;
			fin >> a >> c >> b >> c >> c >> d >> c;
			
			(*auxProb)[j][i].first.first = a;
			(*auxProb)[j][i].first.second = b;
			(*auxProb)[j][i].second = d;		
		}
		fin >> c >> c; 
	}
	
	fnb->setProbability(auxProb);
	
	fin.close();
		
	return (void*) fnb;
}		

