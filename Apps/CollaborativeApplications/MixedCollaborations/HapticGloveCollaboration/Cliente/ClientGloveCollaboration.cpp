/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
//#include "myViewMono.h"
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybGloveCollaboration.h>

#include <cybermed/cybGlove.h>
#include <cybermed/cybModel.h>
#include "cybHandModel.h"
#include <cybermed/cybRemoteModelFactory.h>

using namespace std;

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

int main(int argc, char** argv) {
	char *fileName = "monkey.wrl";
	if(argc != 2){
		cout << "Error: Invalid number of arguments!" << endl;
		cout << "Please, place collaboration creator ip address." << endl;
		cout << "Stopping app..." << endl;
		return -1;
	}

	CybGloveCollaboration* cybCollaboration = new CybGloveCollaboration(5000, UNICAST_UDP);
	cybCollaboration->setPortName("/dev/usb/hiddev0");

	int numLayer = 1;
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer,numInterator);

	CybViewMono view;
	
	CybParameters *cybCore = CybParameters::getInstance();
	
	cybCollaboration->setDataObtainer(&data);
	cybCollaboration->setModelFactory(new InteratorModelFactory());
	cybCollaboration->joinCollab(string("testes"), InteratorModelFactory::HAND, argv[1], 5001);	

	cout << "ViewMono Created" << endl;

	//Access the parameters information of scene and graphical objects

	data.loadInteratorModel(0, new CybHandModel());
	mfReaderModel<cybSurfaceTriTraits> in;	/**< Acess the OF Vrml reader*/

	sMesh *mesh = new sMesh[numLayer];
	//for(int i = 0; i < numLayer; i++)

	in.read(&mesh[0], fileName);
	
	data.loadModel(mesh);
	data.readColor(fileName, 0);
	cout << "loadModel()" << endl;
	
	cout << "JOIN REQUESTED" << endl;
	
	//Glove Configuration 1------------------------------------------
	CybInterator* glove = (CybInterator*) cybCollaboration->getInterator();
	if (glove == NULL) {
		cout << "interador é nulo!" << endl;
		return 1;
	}
	
	glove->setScale(0.8, 0.8, 0.8);
	glove->setTranslation(25, 0, 0);
	glove->setRotation(0, 0, 180);
	//--------------------------------------------------------------

	

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	cout << "startParameters()" << endl;

	//Set the window name
	view.setWindowName("Simple Visualization");
	cout << "setWindowName()" << endl;


	/*Initialize visualization*/
	view.init();

}



