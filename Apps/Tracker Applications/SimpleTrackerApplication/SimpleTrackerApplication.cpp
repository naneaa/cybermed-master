/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybTracker.h>
#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cyb3DWorld.h>
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybSphereTriangle.h>
#include <cybermed/cybMassSpring.h>
#include <cybermed/cybCollision.h>
#include <cybermed/cybTrackerInterator.h>

#include <cybermed/cybHaarTracker.h>

//#include "collisionCheck.h"


#include <GL/glut.h>

int main(int argc, char** argv)
{
	char *fileName = "osso5x.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 0;

	CybDataObtainer<cybTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	
	CybViewMono view;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	CybInterator *interator = CybTrackerInterator::getInterator(TRACKER_MAGNETIC_INTERATOR);	
	interator->create(0);

	cybCore->trackerOn = true;

	data.loadInteratorModel(0, 0, "esfera.wrl");
	data.startInterator(0, 0);
	
	//interator->setScale(3, 3, 3);
	interator->setColor(1, 0, 0, 1);

	((CybTracker*) interator->getDevice())->createTracker(NULL);

	//interator->setObjectType(3);

	/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(0, fileName);
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);
	
	//Set the window name
	view.setWindowName("Simple Visualization");


	//Create a materrial property context, use by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);


	//Set properties material properties to monkey skin
	cybCore->setMaterialPropertyValue(0,  STIFFNESS, 0.02);
	cybCore->setMaterialPropertyValue(0,  DAMPING, 0.02);
	
	//Create a object of collision
	CybSphereTriangle *collisionObj = new CybSphereTriangle(0, interator);
	
	//Create a object of deformation and set the collision object used
	CybMassSpring *deformationObj = new CybMassSpring(collisionObj, DEF_GO_AND_BACK);
	
	//Update the deformation properties
	deformationObj->update();
		
	//Initialize collision check thread
	deformationObj->init();


/*
	// To use collision check, use this code with:
	//
	// 	#include collisionCheck.h
	//


	//Create a materrial property context, use by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);
	
	//Passing a layerID for collision
	collisionCheck *collCheck = new collisionCheck(0);
	
	//Initialize the collison
	collCheck->getCollisionInstance()->init();
	
	//Initialize collision check thread
	collCheck->init();

*/

	/*Initialize visualization*/
	view.init();
	
}

