/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
//#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybMouseInterator.h>
#include <cybermed/cybDefaultCollaboration.h>
#include <cybermed/cybReceiverThread.h>
#include <cybermed/cybUDPServer.h>

#include "../../InteratorModelFactory.h"

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

	//CybDefaultCollaboration* cybCollaboration = new CybDefaultCollaboration(5001, MULTICAST, "224.0.0.1");
	CybDefaultCollaboration* cybCollaboration = new CybDefaultCollaboration(5001, UNICAST_UDP);
	
	//TrafficMonitor *traffic = new TrafficMonitor(cybCollaboration, 10);
//	traffic->init();

	char *fileName = "monkey.wrl";
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	cybCollaboration->setDataObtainer(&data);

	CybViewMono view;

	cout << "ViewMono Created" << endl;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	cybCollaboration->createCollaboration(InteratorModelFactory::SPHERE);
	cybCollaboration->setModelFactory(new InteratorModelFactory());
	cout << "COLLABORATION CREATED" << endl;

	data.loadInteratorModel(0, 0, "esfera.wrl");
	data.startInterator(0, 0);


	CybInterator* interator = cybCollaboration->getInterator();
	interator->setColor(1, 0, 0, 1);
	//	interator->setScale(0.1, 0.1, 0.1);

	/*Load the model from VRML file (layerID, fileName)*/
	sMesh *mesh = new sMesh[numLayer];
	
	mfReaderModel<cybSurfaceTriTraits> in;	/**< Acess the OF Vrml reader*/

	//for(int i = 0; i < numLayer; i++)

	in.read(&mesh[0], fileName);
	
	//data.readColor(fileName, 0);
	
		/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(mesh);
	cout << "loadModel()" << endl;

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	cout << "startParameters()" << endl;

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//Set the window name
	view.setWindowName("Simple Visualization");
	cout << "setWindowName()" << endl;

	//Create a materrial property context, use by collision, haptics and deformation
	//cybCore->createMaterialPropertyContext(numLayer);

	//cybCollaboration->getCollaborationPerformance()->reportPeformance();

	//cybCollaboration->activeCollision(true, 0);
	/*Initialize visualization*/
	view.init();
	
return 0;
	
}

