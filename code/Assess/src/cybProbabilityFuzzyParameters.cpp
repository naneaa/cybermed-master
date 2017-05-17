// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include "cybProbabilityFuzzyParameters.h"

CybProbabilityFuzzyParameters::CybProbabilityFuzzyParameters(int variables, int cuts)
	: CybAssess(variables), parameters(cuts + 1, variables)
{
	this->alphaCuts = cuts;
}

CybProbabilityFuzzyParameters::~CybProbabilityFuzzyParameters()
{
}

CybMatrix< pair<double, double> > CybProbabilityFuzzyParameters::getFuzzyParameters()
{
	return parameters;
}

void CybProbabilityFuzzyParameters::setFuzzyParameters(CybMatrix< pair<double, double> > parameters)
{
	this->parameters = parameters;
}

int CybProbabilityFuzzyParameters::getAlphaCuts()
{
	return alphaCuts;
}

void CybProbabilityFuzzyParameters::setAlphaCuts(int alphaCuts)
{
	this->alphaCuts = alphaCuts;
}
