#include <cybermed/cybFuzzyNaiveBayes.h>
#include <cybermed/cybFuzzyNaiveBayesIO.h>
#include <cybermed/cybAssessLinker.h>
#include <cybermed/cybAssessDataProvider.h>
#include <cybermed/cybInterator.h>
#include <cybermed/cybMouseInterator.h>
#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/mf/mfReader.h>
#include <iostream>

using namespace std;

CybInterator* interator;

class Provider : public CybAssessDataProvider
{

public:
	
	Provider()
	{
		CybDataObtainer<cybSurfaceTriTraits> data(1, 1);

		this->setFrequency(10);
		interator = CybMouseInterator::getInterator();
		interator->create(0);

		data.loadInteratorModel(0, 0, "esfera.wrl");
		data.startInterator(0, 0);

		interator->setColor(1, 0, 0, 1);
	}
	
	void run()
	{
		CybParameters *cybCore = CybParameters::getInstance();		
		CybVectorND<float> * data = new CybVectorND<float>(3);
		CybVector3D<float> aux;

		this->lock();
			aux = cybCore->getInterator(0)->getPosition();
			(*data)[0] = aux[0];
			(*data)[1] = aux[1];
			(*data)[2] = aux[2];
/*			(*data)[0] = cybCore->getInterator(0)->getPosition()[0];
			(*data)[1] = cybCore->getInterator(0)->getPosition()[0];
			(*data)[2] = cybCore->getInterator(0)->getPosition()[0];*/
		this->unlock();
		
		this->setData(data);
	}
};

class Linker : public CybAssessLinker
{
public:
	Linker(CybAssess* assess, 
		   CybAssessDataProvider* dataProvider,
		   CybAssessIO* io) : CybAssessLinker(assess, dataProvider, io)
		   {
				this->setFrequency(10);
				this->setCurrentMode(OBTAIN_DATA);
		   }
	
	void update()
	{
		if(this->getAssess()->getData()->size() > 50 &&
				this->current_mode != DO_NOTHING)
		{
			this->stop();
			this->setCurrentMode(TRAINING); //doing training()
			this->run();
			this->setCurrentMode(SAVE_DATA); //doing writeData()
			this->run();
			this->setCurrentMode(SAVE_ASSESS); //doing write()
			cout << "salvou" << endl;
			this->run();
			this->setCurrentMode(DO_NOTHING);
			this->stop();
		}
	}
	
};

int main() {
	
		char *fileName = "monkey.wrl"; //Model name
		int numLayer = 1; //Number of layers used in this application
		int numInterator = 0;

		// Transfer the OF data to CybParameters structure
		CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		
		
		CybViewMono view;
		
		//Access the parameters information of scene and graphical objects
		CybParameters *cybCore = CybParameters::getInstance();
		
		sMesh *mesh = new sMesh[numLayer];
		mfReaderModel<cybSurfaceTriTraits> in;
		in.read(&mesh[0], fileName);
		data.loadModel(mesh);
		cout << "loadModel()" << endl;
		/*Load the model from VRML file (layerID, fileName)*/
		//data.loadModel(0, fileName);
		
		/*Initialize the meshes parameters*/
		data.startParameters(numLayer);

		//Set the object color (layerID, r, g, b,a)
		cybCore->setColor(0,1,1,0.7,0.9);
		
		//Set the window name
		view.setWindowName("Simple Visualization");
		
		Provider * provider = new Provider();
		CybFuzzyNaiveBayes* fnb = new CybFuzzyNaiveBayes(3);
		CybFuzzyNaiveBayesIO* fnbIO = new CybFuzzyNaiveBayesIO("/root/fnbTest");
		Linker* linker = new Linker(fnb, provider, fnbIO);
		
		linker->init();
		/*Initialize visualization*/
		view.init();
		
		delete provider;
		delete fnb;
		delete fnbIO;
		delete linker;		
}
