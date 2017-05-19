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

#include "cybFuzzyExponentialNaiveBayesIO.h"

	
CybFuzzyExponentialNaiveBayesIO::CybFuzzyExponentialNaiveBayesIO(const char* file_name) : CybAssessIO(file_name, ".cyba_FENB")
{
	
}

CybFuzzyExponentialNaiveBayesIO::~CybFuzzyExponentialNaiveBayesIO()
{
	
}
		
void CybFuzzyExponentialNaiveBayesIO::write(void* fenbwork)
{
	CybFuzzyExponentialNaiveBayes* fenb = (CybFuzzyExponentialNaiveBayes*) fenbwork;
	
	ofstream fout(this->getFile()); 
	
	if(fout.fail())
	{
		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
		
	fout << "##" << fenb->getVariablesNumber() << endl; 
	
	fout << "##" << fenb->getNIntervals() << endl; 

	fout << "\nPertinences\n";
	fout << "**" << endl;
	
	for(int i = 0; i < fenb->getVariablesNumber(); i++)
	{
		for(int j = 0; j < fenb->getNIntervals(); j++)
		{
			fout << "[" << (*fenb->getPertinences())[j][i].first.first << ", " << 
				(*fenb->getPertinences())[j][i].first.second << "]:" << 
				(*fenb->getPertinences())[j][i].second << endl;
		}
		fout << "**" << endl;
	}
	
	fout << "\nParameters\n";
	fout << "**" << endl;
	
	for(int i = 0; i < fenb->getVariablesNumber(); i++)
	{
		fout << fenb->getParameters()[i] << endl;	
	}
	
	fout << "**" << endl;
	
	fout.close();
}
	
void* CybFuzzyExponentialNaiveBayesIO::read()
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

	CybFuzzyExponentialNaiveBayes* fenb = new CybFuzzyExponentialNaiveBayes(variables);

	while(c != '[')
		fin >> c;
		
	CybMatrix < pair< pair<double, double>, double> > auxPert(variables, nIntervals);
	
	for(int i = 0; i < variables; i++)
	{
		for(int j = 0; j < nIntervals; j++)
		{
			double a = 0, b = 0, d = 0;
			fin >> a >> c >> b >> c >> c >> d >> c;
			 
			auxPert[j][i].first.first = a;
			auxPert[j][i].first.second = b;
			auxPert[j][i].second = d;		
		}
	}
	
	fenb->setPertinences(&auxPert);
	
	while(c != '[')
		fin >> c;
		
	CybVectorND<float> auxPar(variables);
	
	for(int i = 0; i < variables; i++)
	{
			float a = 0;
			fin >> a;

			auxPar[i] = a;		
	}
	

	fin.close();
		
	return (void*) fenb;
}		

