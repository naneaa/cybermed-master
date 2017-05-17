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
#include <cybermed/cybDefaultCollaboration.h>
#include <cybermed/cybUDPServer.h>
#include <cybermed/cybCollaborationIntegrant.h>



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

int main(int argc, char *argv[]) {

	if(argc != 2){
		cout << "Error: Invalid number of arguments!" << endl;
		cout << "Please, place collaboration creator ip address." << endl;
		cout << "Stopping app..." << endl;
		return -1;
	}

	CybCollaboration* cybCollaboration = new CybDefaultCollaboration(5000, UNICAST_UDP);	
	//CybCollaboration* cybCollaboration = new CybDefaultCollaboration(5001, MULTICAST, "224.0.0.1");

	//TrafficMonitor *traffic = new TrafficMonitor(cybCollaboration, 10);
	//traffic->init();

	char *fileName = "monkey.wrl";
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	CybViewMono view;


	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();        

	cybCollaboration->setDataObtainer(&data);
	cybCollaboration->setModelFactory(new InteratorModelFactory());
	cybCollaboration->joinCollab(string("testes"), InteratorModelFactory::SPHERE, argv[1], 5001);

	CybInterator* interator = cybCollaboration->getInterator();

	data.loadInteratorModel(0, 0, "esfera.wrl");
	data.startInterator(0, 0);

	interator->setColor(1, 0, 0, 1);

	/*Load the model from VRML file (layerID, fileName)*/
	mfReaderModel<cybSurfaceTriTraits> in;	/**< Acess the OF Vrml reader*/

	sMesh *mesh = new sMesh[numLayer];
	//for(int i = 0; i < numLayer; i++)

	in.read(&mesh[0], fileName);
	
	data.loadModel(mesh);
	data.readColor(fileName, 0);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);
	cybCore->setLayerScale(0, 0.5, 0.5, 0.5);

	//Set the window name
	view.setWindowName("Simple Visualization");

	cout << "viewInit() " << endl;

	/*Initialize visualization*/
	view.init();



}
