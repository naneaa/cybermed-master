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

#include "cybFuzzyGammaNaiveBayesIO.h"

	
CybFuzzyGammaNaiveBayesIO::CybFuzzyGammaNaiveBayesIO(const char* file_name) : CybAssessIO(file_name, ".cyba_FGamNB")
{
	
}

CybFuzzyGammaNaiveBayesIO::~CybFuzzyGammaNaiveBayesIO()
{
	
}
		
void CybFuzzyGammaNaiveBayesIO::write(void* fgnbwork)
{
	CybFuzzyGammaNaiveBayes* fgnb = (CybFuzzyGammaNaiveBayes*) fgnbwork;
	
	ofstream fout(this->getFile(), ofstream::out); 
	
	if(fout.fail())
	{
		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
		
	fout << "##" << fgnb->getVariablesNumber() << endl; 
	
	fout << "##" << fgnb->getNIntervals() << endl; 

	fout << "\nPertinences\n";
	fout << "**" << endl;
	
	for(int i = 0; i < fgnb->getVariablesNumber(); i++)
	{
		for(int j = 0; j < fgnb->getNIntervals(); j++)
		{
			fout << "[" << (*fgnb->getPertinences())[j][i].first.first << ", " << 
				(*fgnb->getPertinences())[j][i].first.second << "]:" << 
				(*fgnb->getPertinences())[j][i].second << endl;
		}
		fout << "**" << endl;
	}
	
	fout << "\nAlpha\n";
	fout << "**" << endl;
	
	vector<float> auxMean = fgnb->getAlpha();
	
	for(int i = 0; i < fgnb->getVariablesNumber(); i++)
	{
		fout << auxMean[i] << endl;	
	}
	
	fout << "\nBeta\n";
	fout << "##" << endl;
	
	vector<float> auxStdDev = fgnb->getBeta();
	
	for(int i = 0; i < fgnb->getVariablesNumber(); i++)
	{
		fout << auxStdDev[i] << endl;	
	}
	
	fout << "**" << endl;
	
	
	fout.close();
}
	
void* CybFuzzyGammaNaiveBayesIO::read()
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
	
	CybFuzzyGammaNaiveBayes* fgnb = new CybFuzzyGammaNaiveBayes(variables, nIntervals);
	
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
	
	fgnb->setPertinences(auxPert);

	while(c != '*')
		fin >> c;
	fin >> c;
		
	vector<float> auxMean(variables);
	
	for(int i = 0; i < variables; i++)
	{
		fin >> auxMean[i];		
	}

	fgnb->setAlpha(auxMean);
	
	while(c != '#')
		fin >> c;
	fin >> c;
		
	vector<float> auxStdDev(variables);
	
	for(int i = 0; i < variables; i++)
	{
		fin >> auxStdDev[i];		
	}

	fgnb->setBeta(auxStdDev);
	
	fin.close();
		
	return (void*) fgnb;
}		

