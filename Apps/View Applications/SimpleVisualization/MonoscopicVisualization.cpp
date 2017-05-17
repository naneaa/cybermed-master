/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>

#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>

#include <cybermed/cybMouseInterator.h>

int main(int argc, char** argv)
{
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	CybViewMono view;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	CybInterator* interator = CybMouseInterator::getInterator();

	data.loadInteratorModel(interator->getId(), 0, "esfera.wrl");

	data.startInterator(interator->getId(), 0);

	//interator->setColor(1, 1, 0, 1);

	/* Read Mesh File */
	mfWrlReader<cybSurfaceTriTraits> in;	/**< Acess the OF Vrml reader*/
	sMesh *mesh = new sMesh[numLayer];
	in.read(&mesh[0], fileName);

	data.readColor(fileName, 0);

	/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(mesh);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//Set the window name
	view.setWindowName("Simple Visualization");

	/*Initialize visualization*/
	view.init();
}
