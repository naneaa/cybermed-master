#include "cybGaussianIO.h"

CybGaussianIO::CybGaussianIO(char* file_name) : CybAssessIO(file_name, ".cyba_Gaussian")
{
	
}
		
void CybGaussianIO::write(void* GaussianObject)
{
	CybGaussian* Gaussian = (CybGaussian*) GaussianObject;
	
	ofstream fout(this->getFile()); 
	
		if(fout.fail())
		{
			cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
			cout << flush;
			exit(0);
		}
		
	fout << "##" << Gaussian->getVariablesNumber(); 
	
	fout << "\n\nPrior Probability [ " << Gaussian->getPrioriProbability() << " ]";
		
	fout << "\n\nMean" << "\n[\n";
	

	for(int i=0; i < Gaussian->getVariablesNumber(); i++)
	{
		fout << Gaussian->getMean(i); 
	
			if(i < Gaussian->getVariablesNumber()-1)
				fout << ",\n";
	}
		fout << "\n]\n\n";
		
			fout << "Precision Matrix\n[\n";
		
			for(int i=0; i < Gaussian->getVariablesNumber(); i++)
			{
				for(int j=0; j < Gaussian->getVariablesNumber(); j++)
					fout << Gaussian->getCovariance()[i* Gaussian->getVariablesNumber() + j] << " ";
				fout << "\n";
			}
		fout << "]";	
	fout.close();
}
	
void* CybGaussianIO::read()
{
	//cout << "entrou" << endl;
	ifstream fin(this->getFile());
	//cout << "passou" << endl;
	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
		exit(0);
	}
	
	char c = 'a';
	int number = 0;
	float mean;
	int count = 0;
	float prob = 1.0;
	
	fin >> c;
	fin >> c;
	fin >> number;
	
	
	while(c != '[')
		fin >> c;
	
	fin >> prob;
	
	fin >> c;

	CybGaussian* Gaussian = new CybGaussian(number, prob);
	
	while(c != '[')
		fin >> c;
	
	while(c != ']')
	{
		fin >> mean;
		fin >> c;
	
		Gaussian->setMean(mean, count++);	
	}	

	while(c != '[')
		fin >> c;	
	
	float* matrix = new float[Gaussian->getVariablesNumber()*Gaussian->getVariablesNumber()];
	
	for(int i=0; i < Gaussian->getVariablesNumber()*Gaussian->getVariablesNumber(); i++)
		fin >> matrix[i];
	
	Gaussian->setCovariance(matrix);
	
	Gaussian->checkVariables();
	
	fin.close();
	
	return (void*) Gaussian;
}		
