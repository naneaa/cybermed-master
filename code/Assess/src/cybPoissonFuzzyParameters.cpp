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

#include "cybPoissonFuzzyParameters.h"

CybPoissonFuzzyParameters::CybPoissonFuzzyParameters(int variablesNumber, int alpha_cuts)
	: CybProbabilityFuzzyParameters(variablesNumber, alpha_cuts)
{
	
}

CybPoissonFuzzyParameters::~CybPoissonFuzzyParameters()
{
	
}


void CybPoissonFuzzyParameters::training()
{
	parametersEstimation();
}

double CybPoissonFuzzyParameters::assessment(CybVectorND<>* auxdata)
{
	//previously calculates logs in order to reduce running time
	float* data = auxdata->toArray();
	vector<double> logs (getVariablesNumber(), 0);
	double max = data[0];
	for(int i = 1; i < getVariablesNumber(); i++)
		if(max < data[i])
			max = data[i];
		
	double aux = 0;	
	for(int j = 2; j < max; j++)
	{
		aux += log(j);
		for(int i = 0; i < getVariablesNumber(); i++)
			if(data[i] == j)
				logs[i] = aux;
	}
	
	//calculates the densitys by variable and alpha-cut
	CybMatrix< pair<double, double> > density(alphaCuts, getVariablesNumber());
	
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		for(int j = 0; j < alphaCuts; j++)
		{
			double lambda_min = parameters[j][i].first;
			double lambda_max = parameters[j][i].second;
						
			double aux1 = data[i]*(log(lambda_min)) - lambda_min - logs[data[i]];
			double aux2 = data[i]*(log(lambda_max)) - lambda_max - logs[data[i]];
		
			density[j][i].first = aux1 < aux2 ? aux1 : aux2;
			density[j][i].second = aux1 > aux2 ? aux1 : aux2;	
		}
	}
	
	//calculates total density for this data by its alpha-cuts
	vector< pair<double, double> > totalDensity(alphaCuts);
	
	if(getVariablesNumber() == 0)
	{
		for(int j = 0; j < alphaCuts; j++)
		{
			totalDensity[j].first = density[j][0].first;
			totalDensity[j].second = density[j][0].second;
		}
	} else {
		for(int i = 0; i < getVariablesNumber(); i++)
		{
			for(int j = 0; j < alphaCuts; j++)
			{
				totalDensity[j].first = ((totalDensity[j].first + density[j][i].first)/2);
                totalDensity[j].second = ((totalDensity[j].second + density[j][i].second)/2);
			}
		}
	}
	
	//calculates the sum of the densitys in order to defuzzyfi
	double sum = 0;
	for(int j = 0; j < alphaCuts; j++)
	{
		sum += (totalDensity[j].first + totalDensity[j].second)/2;
	}
	sum /= alphaCuts;
		
	return sum;
}

void CybPoissonFuzzyParameters::parametersEstimation()
{
	mfList<CybVectorND<float>*>* data = this->getData();
	int size = data->pos(0)->getDimension();
	 
	//1st - calculate mean
	vector<double> mean(getVariablesNumber(), 0);
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		for(int j = 0; j < size; j++)
		{
			mean[i] += data->pos(i)->operator[](j);
		}
		mean[i] /= size;
	}
	
	//2nd - calculate lambda
	for(int i = 0; i < getVariablesNumber(); i++)
	{
		double alpha = 0.01;
		double step = (1.0 - 0.01)/alphaCuts;
		for(int j = 0; j <= alphaCuts; j++)
		{
			float n = normalinversa(1 - alpha/2);
			double aux_min = (sqrt(size) * mean[i]) / (sqrt(size) + n);
			double aux_max	= (sqrt(size) * mean[i]) / (sqrt(size) - n);		
			
			parameters[j][i].first = aux_min < aux_max ? aux_min : aux_max;
			parameters[j][i].second = aux_min > aux_max ? aux_min : aux_max;

			cout << "V: " << i + 1 << " alpha: " << alpha << " [" << parameters[j][i].first << ", " << parameters[j][i].second << "]" << endl;
			alpha += step;
		}
	}
	
}

//Função para aproximação da normal cumulativa inversa.
float CybPoissonFuzzyParameters::normalinversa(float pe){

    //Declaração das variáveis
    float a[4]= {2.5066282,-18.6150006,41.3911977,-25.4410605};
    float b[4]= {-8.4735109,23.0833674,-21.0622410,3.1308291};
    float c[4]= {-2.7871893,-2.2979648,4.8501413,2.3212128};
    float d[2]= {3.5438892,1.6370678};
    float que,abs_que,q2,rq,aux,Ap_Inv_N_2;

    //printf("Digite o valor da probabildiade\n");
    //scanf("%f",&pe);

    if(pe<0 || pe>1)
    {

        cout << "\nA Probabilidade nao pode ser menor que zero ou maior que 1.\n";

    }
    else if(pe>0 && pe<1)
    {

        que=pe-0.5;

        //Valor Absoluto do que
        if(que>0)
        {
            abs_que=que;
        }
        else
        {
            abs_que=-que;
        }



        if(abs_que<=0.42)
        {
            q2=que*que;
            aux=que*(((a[3]*q2+a[2])*q2+a[1])*q2+a[0]);
            Ap_Inv_N_2= aux / ((((b[3]*q2+b[2])*q2+b[1])*q2+b[0])*q2+1);
        }
        else
        {
            if(que<0)
            {
                rq=sqrt(-log(pe));
            }
            else
            {
                rq=sqrt(-log(1-pe));
            }

            aux=(((c[3]*rq+c[2])*rq+c[1])*rq+c[0]);
            aux=aux/((d[1]*rq+d[0])*rq+1);

            if(que>=0)
            {
                Ap_Inv_N_2=aux;
            }
            else
            {
                Ap_Inv_N_2=-aux;
            }

        }


    }
    else if(pe==0)
    {
        Ap_Inv_N_2=-3;

    }
    else
    {
        Ap_Inv_N_2=3;
    } //Fim da verificação de 0<pe<1


    return(Ap_Inv_N_2);
}





