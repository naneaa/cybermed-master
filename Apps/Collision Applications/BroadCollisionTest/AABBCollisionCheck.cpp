/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
//#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybMouseInterator.h>
#include <cybermed/cybAABB.h>
#include <cybermed/cybCollisionManager.h>
#include <cybermed/mf/mfWrlReader.h>
#include <string>
#include <cstring>
#include <iostream>


using namespace std;


int main(int argv, char **argc)
{
	string s1 = "monkey.wrl"; //model name
	char* filename = const_cast<char*>(s1.c_str());
	int numLayer = 1; //number of layers used in this application
	int numInterator = 1;
	
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator); // Transfer the OF data to the CybParameters structure
	CybViewMono view; // Monoscopic Visualization
//	CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);
	CybInterator* interator = CybMouseInterator::getInterator();

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	// =============
	// Read Mesh File 
	mfWrlReader<cybSurfaceTriTraits> in;
	sMesh *mesh = new sMesh[numLayer];
	in.read(&mesh[0], filename);
	data.readColor(filename, 0);
	data.loadModel(mesh);
	//===========
	
	//Load the model from VRML file (layerID, fileName)
	//data.loadModel(0, filename);
	string s2 = "agulha_unida.wrl";
	char *aux = const_cast<char*>(s2.c_str());
	data.loadInteratorModel(0,0, aux);
	data.startInterator(0,0);
	interator->setColor(0,1,0,1);

	//Initialize the meshes parameters
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//Set the window name
	string s3 = "Teste";
	char *aux2 = const_cast<char*>(s3.c_str());
	view.setWindowName(aux2);

	//Create a materrial property context, used by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);

	//Creating the AABBs
	CybAABB *caixaInter = new CybAABB(0,0,true, true);
	CybAABB *caixaModel = new CybAABB(0,0,false, true);
	caixaInter->describeBox();
	caixaModel->describeBox();
	caixaInter->addTest(caixaModel);
	caixaModel->addTest(caixaInter);
	
	//Creating the Collision Manager objects.
	CybCollisionManager* colMan1 = new CybCollisionManager(caixaInter, true);
	CybCollisionManager* colMan2 = new CybCollisionManager(caixaModel, false);

	//Initializing boxes and managers
	caixaInter->init();
	caixaModel->init();
	colMan1->init();
	colMan2->init();

	//Initializing visualization
	view.init();
	
}
