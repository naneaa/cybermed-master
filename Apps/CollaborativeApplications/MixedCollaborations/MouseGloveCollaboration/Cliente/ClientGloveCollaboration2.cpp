/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybGloveCollaboration.h>

#include <cybermed/cybGlove.h>
#include <cybermed/cybModel.h>
#include "cybHandModel.h"
#include <cybermed/cybRemoteModelFactory.h>

using namespace std;

class MyFactory : public CybRemoteModelFactory {
	public:
		CybRemoteModel *getModel(int id) {			
			switch (id) {				
				case 0:
					return new CybRemoteModel("esfera.wrl");
					break;
				case 1:
					return new CybRemoteModel(new CybHandModel());
					break;
			}		
		}
};

int main(int argc, char** argv)
{
	char *fileName = "esfera.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;
	CybModel *model = new CybHandModel();
	
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure	
	CybViewMono view;
	//Access the parameters information of scene and graphical objects
	CybGloveCollaboration* cybCollaboration = new CybGloveCollaboration(5000, UNICAST_UDP);
	cybCollaboration->setPortName("/dev/usb/hiddev0");
	
	CybParameters *cybCore = CybParameters::getInstance();
	//Em caso de ser outra porta
	/*Cyb5DTGlove *glove = dynamic_cast<Cyb5DTGlove *>(interator->getDevice());
	glove->setPort("/dev/usb/hiddev0");*/
	//CybInterator* mouseInterator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);	
	//interator->create(0);
	data.loadInteratorModel(0, model);
	data.startInterator(0, 0); //<- Não precisa para modelos tipo CybModel
	/*Load the model from VRML file (layerID, fileName)*/
	
	mfReaderModel<cybSurfaceTriTraits> in(fileName);	/**< Acess the OF Vrml reader*/

	sMesh *mesh = new sMesh[numLayer];
	//for(int i = 0; i < numLayer; i++)

	in.read(&mesh[0]);
	
	data.loadModel(mesh);	
	//Hand Position
	
	
	cybCore->setSceneEditable(true);
	cybCore->setLayerRotation(0, 100, 90, 0);
	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1, 0, 0, 1);
	cybCore->setLayerScale(0, 1.6, 1.6, 1.6);
	
	//Set the window name
	view.setWindowName("Simple Glove Application");
	
	/*Initialize visualization*/
	view.init();
	
}
