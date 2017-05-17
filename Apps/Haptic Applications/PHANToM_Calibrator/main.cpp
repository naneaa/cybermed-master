#include <cybermed/cybHaptics.h>
#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybHapticInterator.h>
#include <GL/glut.h>
#include "MenuHandler.h"

int main(int argc, char** argv)
{

	cout <<"*********************************************************************************"<< endl;
	cout <<"* Phantom Calibrator                                      						 "<< endl;
	cout <<"* Click with right button to display and select phantom properties			     "<< endl;
	cout <<"* Press 1 to increment the property 											 "<< endl;
	cout <<"* Press 0 to decrement the property												 "<< endl;
	cout <<"* Press p to print the current properties values								 "<< endl;
	cout <<"*********************************************************************************"<< endl;
	
	char *fileName = "esfera.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	
	CybViewMono view(MenuHandler::getUniqueInstance());
	
	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	CybInterator* interator = CybHapticInterator::getInterator();

	interator->create(0);

	data.loadInteratorModel(0, 0, "esfera.wrl");

	data.startInterator(0, 0);

	/*Load the model from VRML file (layerID, fileName)*/
	/* Read Mesh File */
	mfWrlReader<cybSurfaceTriTraits> in;	/**< Acess the OF Vrml reader*/

	sMesh *mesh = new sMesh[numLayer];
	//for(int i = 0; i < numLayer; i++)

	in.read(&mesh[0], fileName);

	//data.readColor(fileName, 0);

	/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(mesh);
	//data.loadModel(0, fileName);
	
	interator->setColor(1, 0, 0, 1);
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	/*Gets the Phantom device*/
	CybOpenHPhantom* phantom = (CybOpenHPhantom*)interator->getDevice();
	phantom->createHapticLayers(1, true);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);
	cybCore->createMaterialPropertyContext(numLayer);
	phantom->createAmbientProperty();
	phantom->enableHapticMaterialProperty();
	phantom->enableHapticLayerMaterial(0);
	
	//Set the window name
	view.setWindowName("Simple Visualization");

	//Habilita menu
	cybCore->setMenuOn();
	//Desabilita teclado
	cybCore->setKeyboardOff();

	
	/*Initialize visualization*/
	view.init();
	
}

