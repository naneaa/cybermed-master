/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

//#include <cybermed/cybCore.h>
#include <cybermed/cybCollaborationPerformance.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybHapticCollaboration.h>
#include <cybermed/cybHapticAssistedCollab.h>
#include <cybermed/cybRemoteModelFactory.h>
#include <cybermed/mf/mfReaderModel.h>

#include "cybHandModel.h"

class InteratorModelFactory : public CybRemoteModelFactory {
	public:
		enum NameModel {SPHERE, MONKEY, NEDDLE, HAND};
		CybRemoteModel *getModel(int id) {			
			switch (id) {				
				case 0:
					return new CybRemoteModel("esfera.wrl");
					break;
				case 1:
					return new CybRemoteModel("monkey.wrl");
					break;
				
				case 2: return new CybRemoteModel("agulha_unida-2.wrl");
					break;				
				
				case 3: return new CybRemoteModel(new CybHandModel());
					break;				

			}		
		}
};


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

	//CybHapticCollaboration* cybCollaboration = new CybHapticCollaboration(5001, MULTICAST, "224.0.0.1");
	CybHapticCollaboration* cybCollaboration = new CybHapticCollaboration(5001, UNICAST_UDP);
	
	TrafficMonitor *traffic = new TrafficMonitor(cybCollaboration, 60);
	//traffic->init();
	
	//char *fileName = "Bacia - Osso.wrl"; //Model name
	char *fileName = "monkey.wrl";
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	CybViewMono view;
	cout << "ViewMono Created" << endl;

	cybCollaboration->setDataObtainer(&data);
        cybCollaboration->setModelFactory(new InteratorModelFactory());

	cybCollaboration->createCollaboration(InteratorModelFactory::SPHERE);
        

	data.loadInteratorModel(0, 0, "esfera.wrl");
	data.startInterator(0, 0);

	CybInterator* interator = cybCollaboration->getInterator();
	CybOpenHPhantom* phantom = (CybOpenHPhantom*)interator->getDevice();
	phantom->createHapticLayers(1, true);

	interator->setColor(1, 0, 0, 1);

	/*Load the model from VRML file (layerID, fileName)*/

	mfReaderModel<cybSurfaceTriTraits> in;  /**< Acess the OF Vrml reader*/

        sMesh *mesh = new sMesh[numLayer];
        //for(int i = 0; i < numLayer; i++)

        in.read(&mesh[0], fileName);

        data.loadModel(mesh);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	cout << "startParameters()" << endl;

	//cybCollaboration->getInterator()->setColor(1, 0, 0, 1);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);

	//Set the window name
	view.setWindowName("Simple Visualization");
	cout << "setWindowName()" << endl;

	/*Initialize visualization*/
	view.init();
}



