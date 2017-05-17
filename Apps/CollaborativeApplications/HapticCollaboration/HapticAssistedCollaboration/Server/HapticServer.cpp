/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/


//#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybHapticAssistedCollab.h>

#include "../../../InteratorModelFactory.h"

class TrafficMonitor : public CybThread {

private: CybCollaboration *collab;
	 int collectTime; 	
	 int time;

public:	TrafficMonitor(CybCollaboration *collab, int collectTime) {		
		this->collab = collab;
		this->collectTime = collectTime;
		time = 0;
	}

	void run() {
		this->setTime(1000);			
		cout << time << endl;

		if (time > collectTime) {
			collab->getCollaborationPerformance()->reportPerformance();
			delete collab;	
		}		
		time++;
	}	
};


int main() {

	CybHapticAssistedCollab* cybCollaboration = new CybHapticAssistedCollab(5001, UNICAST_UDP);
	//CybHapticAssistedCollab* cybCollaboration = new CybHapticAssistedCollab(5001, MULTICAST, "224.0.0.1");

	
	TrafficMonitor *traffic = new TrafficMonitor(cybCollaboration, 90);		
	//traffic->init();
	
	char *fileName = "monkey.wrl";
	
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	cybCollaboration->setDataObtainer(&data);

	cybCollaboration->createCollaboration(InteratorModelFactory::NEDDLE);
        cybCollaboration->setModelFactory(new InteratorModelFactory());

	CybInterator* interator = cybCollaboration->getInterator();
	CybOpenHPhantom* phantom = (CybOpenHPhantom*)interator->getDevice();
	phantom->createHapticLayers(1, true);


	data.loadInteratorModel(0, 0, "agulha_unida2.wrl");
	data.startInterator(0, 0);

	interator->setColor(1, 0, 0, 1);

	CybViewMono view;

	cout << "ViewMono Created" << endl;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	/*Load the model from VRML file (layerID, fileName)*/
	sMesh *mesh = new sMesh[numLayer];
	mfReaderModel<cybSurfaceTriTraits> in;
	in.read(&mesh[0], fileName);
	data.readColor(fileName, 0);
	data.loadModel(mesh);
	cout << "loadModel()" << endl;

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	cout << "startParameters()" << endl;

	//cybCollaboration->getInterator()->setColor(1, 0, 0, 1);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//Set the window name
	view.setWindowName("Simple Visualization");
	cout << "setWindowName()" << endl;

	/*Initialize visualization*/
	view.init();

}



