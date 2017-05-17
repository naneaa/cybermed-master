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

#include "cybPoissonFuzzyParametersIO.h"

	
CybPoissonFuzzyParametersIO::CybPoissonFuzzyParametersIO(const char* file_name) : CybAssessIO(file_name, ".cyba_PNBFP")
{
	
}

CybPoissonFuzzyParametersIO::~CybPoissonFuzzyParametersIO()
{
	
}
		
void CybPoissonFuzzyParametersIO::write(void* pfpwork)
{
	CybPoissonFuzzyParameters* pfp = (CybPoissonFuzzyParameters*) pfpwork;
	
	ofstream fout(this->getFile()); 
	
	if(fout.fail())
	{
		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
		
	fout << "##" << pfp->getVariablesNumber() << endl; 
	
	fout << "##" << pfp->getAlphaCuts() << endl;
	
	fout << "\nParameters\n";
	fout << "**" << endl;
	
	for(int i = 0; i < pfp->getVariablesNumber(); i++)
	{
		for(int j = 0; j < pfp->getAlphaCuts(); j++)
		{
			fout << "[" << pfp->getFuzzyParameters()[j][i].first << ", " << pfp->getFuzzyParameters()[j][i].second << "]" << endl;
		}
		fout << "**" << endl;
	}
	
	fout.close();
}
	
void* CybPoissonFuzzyParametersIO::read()
{
	ifstream fin(this->getFile());
	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo de entrada " << this->getFile() << endl;
		exit(0);
	}
	
	char c;
	int variables;
	int cuts;
	double v1, v2;
	
	fin >> c >> c >> variables >> c >> c >> cuts;

	CybPoissonFuzzyParameters* pfp = new CybPoissonFuzzyParameters(variables, cuts);

	while(c != '[')
		fin >> c;
		
	CybMatrix< pair<double, double> > auxPar(cuts+1, variables);
	
	for(int i = 0; i < variables; i++)
	{
		for(int j = 0; j < cuts; j++)
		{
			double a = 0, b = 0;
			fin >> a >> c >> b >> c >> c;
			 
			auxPar[j][i].first = a;
			auxPar[j][i].second = b;		
		}
		fin >> c >> c;	
	}
	
	pfp->setFuzzyParameters(auxPar);

	fin.close();
		
	return (void*) pfp;
}		

