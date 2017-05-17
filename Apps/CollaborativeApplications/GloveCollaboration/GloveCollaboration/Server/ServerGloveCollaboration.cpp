/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include "myViewMono.h"
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybGloveCollaboration.h>
#include <cybermed/cybGlove.h>
#include "cybHandModel.h"
#include "cybHandModel_Remote.h"
#include <cybermed/cybRemoteModelFactory.h>

using namespace std;

class MyFactory : public CybRemoteModelFactory {
	public:
		CybRemoteModel *getModel(int id) {			
			return new CybRemoteModel(new CybHandModel_Remote());
		}
};

int main() {

	CybGloveCollaboration* cybCollaboration = new CybGloveCollaboration(5001, UNICAST_UDP);
	cybCollaboration->setPortName("/dev/usb/hiddev0"); //you can set the port 	
		
	int numLayer = 1;
	int numInterator = 1;
	
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer,numInterator);

	MyViewMono view;
	
	CybParameters *cybCore = CybParameters::getInstance();
	
	cybCollaboration->setDataObtainer(&data);
	
	cybCollaboration->createCollaboration(1);
	MyFactory *pMyFactory = new MyFactory();
	cybCollaboration->setModelFactory(pMyFactory);
	
	
	//Glove Initialization
	CybInterator* glove = (CybInterator*) cybCollaboration->getInterator();
	if (glove == NULL) {
		cout << "interador é nulo!" << endl;
		return 1;
	}
	
	glove->setScale(0.8, 0.8, 0.8);
	glove->setTranslation(-25, 0, 0);
	glove->setRotation(0, 0, 180);

	data.loadInteratorModel(0, new CybHandModel());


	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);

	//Set the window name
	view.setWindowName("Glove Server");
	
	/*Initialize visualization*/
	view.init();

}



