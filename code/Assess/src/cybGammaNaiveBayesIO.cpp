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

#include "cybGammaNaiveBayesIO.h"

	
CybGammaNaiveBayesIO::CybGammaNaiveBayesIO(const char* file_name) : CybAssessIO(file_name, ".cyba_FGamNB")
{
	
}

CybGammaNaiveBayesIO::~CybGammaNaiveBayesIO()
{
	
}
		
void CybGammaNaiveBayesIO::write(void* fgnbwork)
{
	CybGammaNaiveBayes* fgnb = (CybGammaNaiveBayes*) fgnbwork;
	
	ofstream fout(this->getFile(), ofstream::out); 
	
	if(fout.fail())
	{
		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
		
	fout << "##" << fgnb->getVariablesNumber() << endl; 
	
	fout << "\nMean\n";
	fout << "**" << endl;
	
	vector<float> auxMean = fgnb->getAlpha();
	
	for(int i = 0; i < fgnb->getVariablesNumber(); i++)
	{
		fout << auxMean[i] << endl;	
	}
	
	fout << "\nStandard Deviation\n";
	fout << "##" << endl;
	
	vector<float> auxStdDev = fgnb->getBeta();
	
	for(int i = 0; i < fgnb->getVariablesNumber(); i++)
	{
		fout << auxStdDev[i] << endl;	
	}
	
	fout << "**" << endl;
	
	
	fout.close();
}
	
void* CybGammaNaiveBayesIO::read()
{
	ifstream fin(this->getFile());
	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo de entrada. " << this->getFile() << endl;
		exit(0);
	}
	
	char c;
	int variables;
	
	fin >> c >> c >> variables;
	
	CybGammaNaiveBayes* fgnb = new CybGammaNaiveBayes(variables);

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

