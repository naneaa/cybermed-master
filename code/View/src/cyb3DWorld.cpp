// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************
 
#include "cyb3DWorld.h"


char *Cyb3DWorld::windowName = "";
CybMouse* Cyb3DWorld::mouse = NULL;
Cyb3DWorld* Cyb3DWorld::this_object = 0;
int Cyb3DWorld::viewNumber = 1;

	/** Constructor */
	Cyb3DWorld::Cyb3DWorld(CybMouse* mouse, bool stereo)
	{
		if(mouse == NULL) mouse = CybMouse::getInstance();
		else Cyb3DWorld::mouse = mouse;
			
		CybParameters *cybCore = CybParameters::getInstance();
		
		viewMode = GL_TRIANGLES;
		
		initLightsParameters();

		this_object = this;

		this->swap = false;
	
		freePos = 0;	
	
		this->stereo = stereo;
	}
	
	void Cyb3DWorld::enableWire(){
		this->viewMode = GL_LINE_LOOP;
	}
	
	void Cyb3DWorld::disableWire(){
		this->viewMode = GL_TRIANGLES;
	}
	
	bool Cyb3DWorld::isWire(){
		
		return (viewMode == GL_LINE_LOOP);
	}
	
	GLenum Cyb3DWorld::getViewMode(){
		
		return viewMode; 
	}
	
	/* The auxiliar functions make possible that derived classes override these methods */

	/** Auxiliar Drawing Function
	@param void
	@return void
	*/
	inline  void Cyb3DWorld::mainDisplay()
    	{ 
		this_object->display(); 
       	}

	/** Auxiliar Reshape Function
	@param int width
	@param int height
	@return void
	*/
	inline void Cyb3DWorld::mainReshape(int width, int height)
    	{ 
		this_object->reshape(width, height); 
       	}

	/** Auxiliar Idle Function
	@param void
	@return void
	*/
	inline void Cyb3DWorld::mainIdle()
    	{ 
		this_object->glutIdle(); 
       	}

	/** Auxiliar Keyboard Function
	@param unsigned char key
	@param int x
	@param int y
	@return void
	*/
	inline void Cyb3DWorld::mainKeyboard(unsigned char key, int x, int y)
    	{ 
		this_object->keyboard(key, x, y); 
       	}

	/** Auxiliar Special Key Function
	@param int key
	@param int x
	@param int y
	@return void
	*/
	inline void Cyb3DWorld::mainSpecialKey(int key, int x, int y)
    	{ 
		this_object->specialKey(key, x, y); 
       	}

	/** Auxiliar Mouse Function
	@param int button
	@param int state
	@param int x
	@param int y
	@return void
	*/
	inline void Cyb3DWorld::mainMouseFunc(int button, int state, int x, int y)
    	{ 
		this_object->mouseFunc(button, state, x, y); 
       	}

	/** Auxiliar Mouse Motion Function
	@param int x
	@param int y
	@return void
	*/
	inline void Cyb3DWorld::mainMouseMotionFunc(int x, int y)
    	{ 
		this_object->mouseMotionFunc(x, y); 
       	}

	/** Auxiliar Passive Mouse Motion Function
	@param int key
	@param int x
	@param int y
	@return void
	*/
	inline void Cyb3DWorld::mainMousePassiveMotionFunc(int x, int y)
    	{ 
		this_object->mousePassiveMotionFunc(x, y); 
       	}

	inline int Cyb3DWorld::ImageLoad(char *filename, Image *image) {
		FILE *file;
		unsigned long size;                 // size of the image in bytes.
		unsigned long i;                    // standard counter.
		unsigned short int planes;          // number of planes in image (must be 1) 
		unsigned short int bpp;             // number of bits per pixel (must be 24)
		char temp;                          // temporary color storage for bgr-rgb conversion.
		
		// make sure the file is there.
		if ((file = fopen(filename, "rb"))==NULL)
		{
			printf("File Not Found : %s\n",filename);
			return 0;
		}
		
		// seek through the bmp header, up to the width/height:
		fseek(file, 18, SEEK_CUR);
		
		// read the width
		if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
			printf("Error reading width from %s.\n", filename);
			return 0;
		}
		printf("Width of %s: %lu\n", filename, image->sizeX);
		
		// read the height 
		if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
			printf("Error reading height from %s.\n", filename);
			return 0;
		}
		printf("Height of %s: %lu\n", filename, image->sizeY);
		
		// calculate the size (assuming 24 bits or 3 bytes per pixel).
		size = image->sizeX * image->sizeY * 3;
		
		// read the planes
		if ((fread(&planes, 2, 1, file)) != 1) {
			printf("Error reading planes from %s.\n", filename);
			return 0;
		}
		if (planes != 1) {
			printf("Planes from %s is not 1: %u\n", filename, planes);
			return 0;
		}
		
		// read the bpp
		if ((i = fread(&bpp, 2, 1, file)) != 1) {
			printf("Error reading bpp from %s.\n", filename);
			return 0;
		}
		if (bpp != 24) {
			printf("Bpp from %s is not 24: %u\n", filename, bpp);
			return 0;
		}
			
		// seek past the rest of the bitmap header.
		fseek(file, 24, SEEK_CUR);
		
		// read the data. 
		image->data = (char *) malloc(size);
		if (image->data == NULL) {
			printf("Error allocating memory for color-corrected image data");
			return 0;	
		}
		
		if ((i = fread(image->data, size, 1, file)) != 1) {
			printf("Error reading image data from %s.\n", filename);
			return 0;
		}
		
		for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
			temp = image->data[i];
			image->data[i] = image->data[i+2];
			image->data[i+2] = temp;
		}
		
		// we're done.
		return 1;
	}

	// Load Bitmaps And Convert To Textures
	inline void Cyb3DWorld::loadBMPTexture(char* path, int idTex) {	
		CybParameters *cybCore = CybParameters::getInstance();

		// Load Texture
		Image *image;
		
		// allocate space for texture
		image = (Image *) malloc(sizeof(Image));
		if (image == NULL) {
			printf("Error allocating space for image");
			exit(0);
		}

		if (!ImageLoad(path, image)) {
			exit(1);
		}        

		// Create Texture	
		glGenTextures(1, &(cybCore->texture[idTex]));
		glBindTexture(GL_TEXTURE_2D, cybCore->texture[idTex]);   // 2d texture (x and y size)
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
		
		// 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
		// border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
	};


	/**	Initializes the visualization, creates the window and draws the objects.
	@param  void
	@return void
	*/
	void Cyb3DWorld::init()
	{
		CybParameters *cybCore = CybParameters::getInstance();
		//CybInterator *interator = CybInterator::getInstance();
		int p[1] = { 1 };
		char **config = new char*[2];
		config[0] = windowName;
		config[1] = NULL;
		

		cybCore->viewType = viewNumber;

		/*for(int i=0; i < cybCore->getNumInterators();i++)
			cybCore->hapticsPlugged[i] = false;*/
			//cybCore->hapticsPlugged[i] = interator->hapticsStatus;
			
		if(viewNumber != 5){

			glutInit(p, config);

			if(stereo)
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO );
			else
				glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

			glutInitWindowSize(cybCore->Resx, cybCore->Resy);
			glutInitWindowPosition(50, 50);

			glutCreateWindow(windowName);

			/*If texturing is active*/
			if(cybCore->nTextures) {
				for(int j=0; j < cybCore->nTextures; j++)
					loadBMPTexture(cybCore->texName[j],j);
				//glEnable(GL_TEXTURE_2D);                    // Enable texture mapping.
	    	}
        	glutDisplayFunc(mainDisplay); 
			glutReshapeFunc(mainReshape);
			glutIdleFunc(mainIdle);
		
			if(cybCore->isKeyboardEnable()) { 
				glutKeyboardFunc(mainKeyboard);
				glutSpecialFunc(mainSpecialKey);
			}		
			glutMouseFunc(mainMouseFunc);
			glutMotionFunc(mainMouseMotionFunc);
			glutPassiveMotionFunc(mainMousePassiveMotionFunc);
			loadObjects();
			glutMainLoop();
			
		}else{
		
			glutInit(p, config);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			
			if(!defResolution){
				std::cout << "Warning: Resolution has not been defined!. Using default 800x600 Resolution." << std::endl;
			}
		
			glutInitWindowSize(horResolution, verResolution);
			
			/*If texturing is active*/
			if(cybCore->nTextures) {
				for(int j=0; j < cybCore->nTextures; j++)
					loadBMPTexture(cybCore->texName[j],j);
				//glEnable(GL_TEXTURE_2D);                    // Enable texture mapping.
	    	}
			
			
			//Left Window
			if(swap){
				glutInitWindowPosition(horResolution, 0);
			}else{
				glutInitWindowPosition(0, 0);
			}

			leftWindow = glutCreateWindow(windowName);
			glutSetWindow(leftWindow);

        	glutDisplayFunc(mainDisplay); 
			glutReshapeFunc(mainReshape);
			glutIdleFunc(mainIdle);
		
			if(cybCore->isKeyboardEnable()) { 
				glutKeyboardFunc(mainKeyboard);
				glutSpecialFunc(mainSpecialKey);
			}		
			glutMouseFunc(mainMouseFunc);
			glutMotionFunc(mainMouseMotionFunc);
			glutPassiveMotionFunc(mainMousePassiveMotionFunc);
			
			
			//Right Window
			
			if(swap){
				glutInitWindowPosition(0, 0);
			}else{
				glutInitWindowPosition(horResolution, 0);
			}
			
			rightWindow = glutCreateWindow(windowName);
			glutSetWindow(rightWindow);

        	glutDisplayFunc(mainDisplay); 
			glutReshapeFunc(mainReshape);
			glutIdleFunc(mainIdle);
		
			if(cybCore->isKeyboardEnable()) { 
				glutKeyboardFunc(mainKeyboard);
				glutSpecialFunc(mainSpecialKey);
			}		
			glutMouseFunc(mainMouseFunc);
			glutMotionFunc(mainMouseMotionFunc);
			glutPassiveMotionFunc(mainMousePassiveMotionFunc);
			loadObjects2();
			glutMainLoop();
			
		}
		
	}

	/**	Set ambient light
	@param float r
	@param float g
	@param float b
	@param float a
	@return void
	*/
	void Cyb3DWorld::setAmbientLight(float r, float g, float b, float a)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		cybCore->ambientLight[0] = r;
		cybCore->ambientLight[1] = g;
		cybCore->ambientLight[2] = b;
		cybCore->ambientLight[3] = a;
	}

	/**	Set diffuse light
	* Sets the diffuse light values for the light identified by light id.
	@param int light_id
	@param float r
	@param float g
	@param float b
	@param float a
	@return void
	*/
	void Cyb3DWorld::setDiffuseLight(int light, float r, float g, float b, float a)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		if(light >= 6)
		{
			cout << "Error. There can only be up to 6 lights." << endl;
			exit(0);
		}
		cybCore->diffuseLight[light][0] = r;
		cybCore->diffuseLight[light][1] = g;
		cybCore->diffuseLight[light][2] = b;
		cybCore->diffuseLight[light][3] = a;
	}

	/**	Set position of light sources.
	* Sets the position of light values for the light identified by light id.
	@param int light_id
	@param float x
	@param float y
	@param float z
	@param float w
	@return void
	*/
	void Cyb3DWorld::setLightPosition(int light, float x, float y, float z, float w)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		if(light >= 6)
		{
			cout << "Error. There can only be up to 6 lights.\n" << endl;
			exit(0);
		}
		cybCore->positionLight[light][0] = x;
		cybCore->positionLight[light][1] = y;
		cybCore->positionLight[light][2] = z;
		cybCore->positionLight[light][3] = w;
	}

	/**	Set number of light sources.
	@param int number_of_lights
	@return void
	*/
	void Cyb3DWorld::setNLights(int n)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		if(n > 6)
		{
			cout << "Error. There can only be up to 6 lights.\n" << endl;
			exit(0);
		}
		cybCore->nLights = n;
	}

	/**	Set specular light
	* Sets the specular light values for the light identified by light id.
	@param int light_id
	@param float r
	@param float g
	@param float b
	@param float a
	@return void
	*/
	void Cyb3DWorld::setSpecularLight(int light, float r, float g, float b, float a)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		if(light >= 6)
		{
			cout << "Error. There can only be up to 6 lights.\n" << endl;
			exit(0);
		}
		cybCore->specularLight[light][0] = r;
		cybCore->specularLight[light][1] = g;
		cybCore->specularLight[light][2] = b;
		cybCore->specularLight[light][3] = a;
	}

	/** Function that sets the texture file's name. To next version
	@param char *texture_file
	@return void
	*/
	void Cyb3DWorld::setTextureFile(char *textureFile){}

	/**	Function that sets the graphic window's name
	@param char *window
	@return void
	*/
	void Cyb3DWorld::setWindowName(char *window) {	windowName = window;	}
	
	char *Cyb3DWorld::getWindowName() {	return windowName;	}


	/**	Display function.
	There's no renderization of the graphical objects in this method. It should be overrided at derived classes
	@param void
	@return void
	*/

         void Cyb3DWorld::display()
	{
		CybParameters *cybCore = CybParameters::getInstance();
		double frustumAssimetry;
		static bool k = false;
		
		sVertex *v0, *v1, *v2;
		int l;

		glColorMask(1,1,1,1);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0,0,0,0);
		glDrawBuffer(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Left Eye
		if(cybCore->viewType == 4)
			glDrawBuffer(GL_BACK_LEFT);

		glMatrixMode(GL_PROJECTION);

		if(cybCore->modified == 1)
		{
			frustumAssimetry = cybCore->StereoProjection(-6.4, 6.4, -6.4, 6.4, 6.0, -6.0, 180, 14.5, -cybCore->getStereoMagnitude(), cybCore->getParalaxe());
			cybCore->rightFrustumLeftEye = cybCore->widthProportion*(cybCore->dfXRange/2 - frustumAssimetry);
			cybCore->leftFrustumLeftEye = cybCore->widthProportion*(-cybCore->dfXRange/2 - frustumAssimetry);
			if(cybCore->viewType != 2 && cybCore->viewType !=3) //redundant
				cybCore->modified = 0;
		}
		glLoadIdentity();

		glFrustum(cybCore->leftFrustumLeftEye, cybCore->rightFrustumLeftEye, cybCore->widthProportion*cybCore->FrustumBase, cybCore->heightProportion*cybCore->FrustumTop, cybCore->dfNearClipDistance, cybCore->dfFarClipDistance);

		if((cybCore->viewType == 2) || (cybCore->viewType == 3))
			glTranslated(-cybCore->dfXMidpoint - cybCore->dfStereoCameraOffset, 0, 0);

		gluLookAt(0, 0, cybCore->camPosZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		for(int j=0; j < cybCore->numLayer; j++)
		{
			if(cybCore->habLayer[j] == 1)
			{
				// graphical transforms
				glTranslated(cybCore->xTrans + cybCore->layerTrans[j][0], cybCore->yTrans + cybCore->layerTrans[j][1], cybCore->zTrans + cybCore->layerTrans[j][2]);
				glScaled(cybCore->xScale * cybCore->layerSca[j][0], cybCore->yScale * cybCore->layerSca[j][1], cybCore->zScale * cybCore->layerSca[j][2]);
				glTranslated(cybCore->cX, cybCore->cY, cybCore->cZ);
				glRotated(cybCore->getXAngle() + cybCore->layerRot[j][0],1,0,0);
				glRotated(cybCore->getYAngle() + cybCore->layerRot[j][1],0,1,0);
				glRotated(cybCore->getZAngle() + cybCore->layerRot[j][2],0,0,1);
				glTranslated(-cybCore->cX, -cybCore->cY, -cybCore->cZ);
		
				glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[j]);

				glLoadIdentity();
			}
		}

		if(!k)
		{
			cybCore->transforChange = true;
			k = true;
		}

		glFlush();
		glLoadIdentity();

		glutSwapBuffers();
	}

	/**	Function that calls the glutPostRedisplay function while the system is in idle state.
	@param void
	@return void
	*/
         void Cyb3DWorld::glutIdle()
         {
        	/*
			#ifdef CYBHAPTICS_H
        	 CybInterator::getInstance()->hapticDevice.IdleHaptics();
			#endif
			*/
		if(viewNumber == 5){
			glutSetWindow(leftWindow);
			glutPostRedisplay();
			glutSetWindow(rightWindow);
		}
        	 glutPostRedisplay();
         }

	/**	Initializes the lights' default values
	@param void
	@return void
	*/
	void Cyb3DWorld::initLightsParameters()
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		int i;

		cybCore->nLights = 1;

		// Initialize diffuseLight and specularLight:
		for(i=0; i<6; i++)
		{
			cybCore->diffuseLight[i][0] = 1;
			cybCore->diffuseLight[i][1] = 1;
			cybCore->diffuseLight[i][2] = 1;
			cybCore->diffuseLight[i][3] = 1;

			cybCore->specularLight[i][0] = 1;
			cybCore->specularLight[i][1] = 1;
			cybCore->specularLight[i][2] = 1;
			cybCore->specularLight[i][3] = 1;
		}

		// Initialize ambient light
		cybCore->ambientLight[0] = 0.5;
		cybCore->ambientLight[1] = 0.5;
		cybCore->ambientLight[2] = 0.5;
		cybCore->ambientLight[3] = 0.5;

		// initialize positionLight:
		cybCore->positionLight[0][0] = 0;
		cybCore->positionLight[0][1] = 1;
		cybCore->positionLight[0][2] = 0;
		cybCore->positionLight[0][3] = 0;

		cybCore->positionLight[1][0] = 1;
		cybCore->positionLight[1][1] = 0;
		cybCore->positionLight[1][2] = 0;
		cybCore->positionLight[1][3] = 0;

		cybCore->positionLight[2][0] = 0;
		cybCore->positionLight[2][1] = 0;
		cybCore->positionLight[2][2] = 1;
		cybCore->positionLight[2][3] = 0;

		cybCore->positionLight[3][0] = 0;
		cybCore->positionLight[3][1] = -1;
		cybCore->positionLight[3][2] = 0;
		cybCore->positionLight[3][3] = 0;

		cybCore->positionLight[4][0] = -1;
		cybCore->positionLight[4][1] = 0;
		cybCore->positionLight[4][2] = 0;
		cybCore->positionLight[4][3] = 0;

		cybCore->positionLight[5][0] = 0;
		cybCore->positionLight[5][1] = 0;
		cybCore->positionLight[5][2] = -1;
		cybCore->positionLight[5][3] = 0;
	}

	/**	Keyboard interaction function
	@param unsigned char key
	@param int x
	@param int y
	@return void
	*/
	void Cyb3DWorld::keyboard(unsigned char key, int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		CybVector4D<float> color;
		switch (key)
		{
			case 'p':	cybCore->initParameters();
					cybCore->transforChange = true;
			break;

			case 't':	cybCore->xScale = cybCore->xScale / 1.1;
					cybCore->transforChange = true;
			break;
			case 'g':	cybCore->xScale = cybCore->xScale * 1.1;
					cybCore->transforChange = true;
			break;
			case 'y':	cybCore->yScale = cybCore->yScale / 1.1;
					cybCore->transforChange = true;
			break;
			case 'h':	cybCore->yScale = cybCore->yScale * 1.1;
					cybCore->transforChange = true;
			break;
			case 'u':	cybCore->zScale = cybCore->zScale / 1.1;
					cybCore->transforChange = true;
			break;
			case 'j':	cybCore->zScale = cybCore->zScale * 1.1;
					cybCore->transforChange = true;
			break;
			
			case 'n':	cybCore->setParalaxe(cybCore->getParalaxe() - 0.005);
					cybCore->modified = 1;
			break;
			case 'm':	cybCore->setParalaxe(cybCore->getParalaxe() + 0.005);
					cybCore->modified = 1;
			break;
			case 'v':	cybCore->setStereoMagnitude(cybCore->getStereoMagnitude() - 0.01);
					cybCore->modified = 1;
			break;
			case 'b':	cybCore->setStereoMagnitude(cybCore->getStereoMagnitude() + 0.01);
					cybCore->modified = 1;
			break;
			
			/*case 'w':	cybCore->xAngle = cybCore->xAngle + 5;
				break;
			case 's':	cybCore->xAngle = cybCore->xAngle - 5;
				break;
			case 'e':	cybCore->yAngle = cybCore->yAngle + 5;
				break;
			case 'd':	cybCore->yAngle = cybCore->yAngle - 5;
				break;
			case 'r':	cybCore->zAngle = cybCore->zAngle + 5;
				break;
			case 'f':	cybCore->zAngle = cybCore->zAngle - 5;
				break;*/

			case '0':	cybCore->objChosen = 0;
			break;
			case '1':	cybCore->objChosen = 1;
			break;
			case '2':	cybCore->objChosen = 2;
			break;
			case '3':	cybCore->objChosen = 3;
			break;
			case '4':	cybCore->objChosen = 4;
			break;
			case '5':	cybCore->objChosen = 5;
			break;
			case '6':	cybCore->objChosen = 6;
			break;
			case '7':	cybCore->objChosen = 7;
			break;
			case '8':	cybCore->objChosen = 8;
			break;
			case '9':	cybCore->objChosen = 9;
			break;

			case 'a':	cybCore->habLayer[cybCore->objChosen] = 1;
			break;
			case 'd':	cybCore->habLayer[cybCore->objChosen] = 0;
			break;

			// Active mouse interaction
			case 'i':	if(cybCore->isInteractionEnable())
					{
						//if(!cybCore->phantomOn)
						//{
						cybCore->mouseOn = true;
						CybMouseInteraction* mouseInteraction = CybMouseInteraction::getInstance();
						CybInterator* mouseInterator = mouseInteraction->getMouseInterator();
						if (mouseInterator != NULL) {
							mouseInterator->setEnabled(true);
						}


						glutDetachMenu(GLUT_RIGHT_BUTTON);
							
						glutSetCursor(GLUT_CURSOR_NONE);
						CybParameters::setCollisionStatus(true);
						//}
						/*else
							cout << "Error! Mouse interaction cannot be started at the "
							<< "same time that the phatom is activated. \n"
							<< "Deactivate the phatom first. \n";*/
					}
			break;

			// Deactive mouse interaction
			case 'k': 
				if(cybCore->isInteractionEnable())
					{
						cybCore->mouseOn = false;
						CybMouseInteraction* mouseInteraction = CybMouseInteraction::getInstance();
						CybInterator* mouseInterator = mouseInteraction->getMouseInterator();
						if (mouseInterator != NULL) {
							mouseInterator->setEnabled(false);
						}
						glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
						CybParameters::setCollisionStatus(false);
					}
			break;

			// alpha
			case '-':
						color = cybCore->getColor(cybCore->objChosen);
						if(color[3] > 0.1) {
						   color[3] -= 0.1;
						   cybCore->setColor(cybCore->objChosen, color);
						}
			break;
			case '+':
				color = cybCore->getColor(cybCore->objChosen);
				if(color[3] < 1) {
					color[3] += 0.1;
					cybCore->setColor(cybCore->objChosen, color);
				}
			break;

			// exit
			case 27:	exit(0);
			break;
		}

		glutPostRedisplay();
	}

	/**	Ilumination initializer function.
	@param void
	@return void
	*/
	 void Cyb3DWorld::lights()
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		// luz pontual 0:
		glLightfv(GL_LIGHT0, GL_DIFFUSE,  cybCore->diffuseLight[0].toArray());
		glLightfv(GL_LIGHT0, GL_SPECULAR, cybCore->specularLight[0].toArray());
		glLightfv(GL_LIGHT0, GL_POSITION, cybCore->positionLight[0].toArray());
		// luz pontual 1:
		glLightfv(GL_LIGHT1, GL_DIFFUSE, cybCore->diffuseLight[1].toArray());
		glLightfv(GL_LIGHT1, GL_SPECULAR, cybCore->specularLight[1].toArray());
		glLightfv(GL_LIGHT1, GL_POSITION, cybCore->positionLight[1].toArray());
		// luz pontual 2:
		glLightfv(GL_LIGHT2, GL_DIFFUSE, cybCore->diffuseLight[2].toArray());
		glLightfv(GL_LIGHT2, GL_SPECULAR, cybCore->specularLight[2].toArray());
		glLightfv(GL_LIGHT2, GL_POSITION, cybCore->positionLight[2].toArray());
		// luz pontual 3:
		glLightfv(GL_LIGHT3, GL_DIFFUSE, cybCore->diffuseLight[3].toArray());
		glLightfv(GL_LIGHT3, GL_SPECULAR, cybCore->specularLight[3].toArray());
		glLightfv(GL_LIGHT3, GL_POSITION, cybCore->positionLight[3].toArray());
		// luz pontual 4:
		glLightfv(GL_LIGHT4, GL_DIFFUSE, cybCore->diffuseLight[4].toArray());
		glLightfv(GL_LIGHT4, GL_SPECULAR, cybCore->specularLight[4].toArray());
		glLightfv(GL_LIGHT4, GL_POSITION, cybCore->positionLight[4].toArray());
		// luz pontual 5:
		glLightfv(GL_LIGHT5, GL_DIFFUSE, cybCore->diffuseLight[5].toArray());
		glLightfv(GL_LIGHT5, GL_SPECULAR, cybCore->specularLight[5].toArray());
		glLightfv(GL_LIGHT5, GL_POSITION, cybCore->positionLight[5].toArray());

		// Light model ambient:
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, cybCore->ambientLight.toArray());

		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		glShadeModel(GL_SMOOTH);

		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


		// Enable lights
		switch( cybCore->nLights )
		{
			case 6: glEnable(GL_LIGHT5);
			case 5: glEnable(GL_LIGHT4);
			case 4: glEnable(GL_LIGHT3);
			case 3: glEnable(GL_LIGHT2);
			case 2: glEnable(GL_LIGHT1);
			case 1: glEnable(GL_LIGHT0);
				break;
			default:
				glEnable(GL_LIGHT0);
				break;
		}
	}

	/**	Function called by the glutMouseFunc function.
	@param int button
	@param int state
	@param int x
	@param int y
	@return void
	*/
	void Cyb3DWorld::mouseFunc(int button, int state, int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();		
		CybMouseInteraction *mouseInteraction = CybMouseInteraction::getInstance();
		CybMouseInterator* mouseInterator = mouseInteraction->getMouseInterator();

		if (mouseInterator != NULL && mouseInterator->isEnabled()) {
			mouseInteraction->mouseInteraction(button, state, x, y);
		} else	{
			Cyb3DWorld::mouse->mouse(button, state, x, y);
		}
	}

	/**	Function called by the glutMotionFunc function.
	@param int x
	@param int y
	@return void
	*/
	void Cyb3DWorld::mouseMotionFunc(int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();	
		CybMouseInteraction *mouseInteraction = CybMouseInteraction::getInstance();
		CybMouseInterator* mouseInterator = mouseInteraction->getMouseInterator();

		if (mouseInterator != NULL && mouseInterator->isEnabled()) {
			mouseInteraction->mouseMoveInteraction(x, y);
		} else {
			Cyb3DWorld::mouse->mouseMove(x, y);
		}
	}

	/**	Function called by the glutPassiveMotionFunc function.
	@param int x
	@param int y
	@return void
	*/
	void Cyb3DWorld::mousePassiveMotionFunc(int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		CybMouseInteraction *mouseInteraction = CybMouseInteraction::getInstance();
		CybMouseInterator* mouseInterator = mouseInteraction->getMouseInterator();

		if (mouseInterator != NULL) {
			if (mouseInterator->isEnabled())
			{
				mouseInteraction->mousePassiveMoveInteraction(x, y);
			}
		}
	}

	/**	Reshapes the objects when window is resized.
	@param int width
	@param int height
	@return void
	*/
	void Cyb3DWorld::reshape(int width, int height)	// adjust
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		cybCore->Resx = width;
		cybCore->Resy = height;
		if(width > height)
		{
			cybCore->widthProportion = (float) width/height;
			cybCore->heightProportion = 1;
			cybCore->modified = 1;
		}
		else if(width == height)
		{
			cybCore->widthProportion = 1;
			cybCore->heightProportion = 1;
			cybCore->modified = 1;
		}
		else
		{
			cybCore->widthProportion = 1;
			cybCore->heightProportion = (float) height/width;
			cybCore->modified = 1;
		}
		glViewport(0, 0, (GLint) width, (GLint) height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
/*
		#ifdef CYBHAPTICS_H
		if(cybCore->phantomOn) // Update haptic scene
		{
			CybInterator::getInstance()->updateHaptics();
		}
		#endif
*/
	}

	/**	Special key interaction function
	@param int key
	@param int x
	@param int y
	@return void
	*/
	void Cyb3DWorld::specialKey(int key, int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();
		
		if (key == GLUT_KEY_RIGHT)
		{
			cybCore->xTrans = cybCore->xTrans + 1;
			cybCore->transforChange = true;
		}
		if (key == GLUT_KEY_LEFT)
		{
			cybCore->xTrans = cybCore->xTrans - 1;
			cybCore->transforChange = true;
		}

		if (key == GLUT_KEY_UP)
		{
			cybCore->yTrans = cybCore->yTrans + 1;
			cybCore->transforChange = true;
		}
		if (key == GLUT_KEY_DOWN)
		{
			cybCore->yTrans = cybCore->yTrans - 1;
			cybCore->transforChange = true;
		}

		if (key == GLUT_KEY_PAGE_UP)
		{
			cybCore->zTrans = cybCore->zTrans + 1;
			cybCore->transforChange = true;
		}
		if (key == GLUT_KEY_PAGE_DOWN)
		{
			cybCore->zTrans = cybCore->zTrans - 1;
			cybCore->transforChange = true;
		}

		glutPostRedisplay();
	}

	void Cyb3DWorld::loadObjects(){
	
	CybParameters *cybCore = CybParameters::getInstance();
	sVertex *v0, *v1, *v2;	
	
	for(int j=0; j < cybCore->numLayer; j++)	
		{		
				
		objects[freePos] = glGenLists(1);
			
		glNewList(objects[freePos], GL_COMPILE);
		
		freePos++;
				
			int l = 0;
			mfCellsIterator<cybSurfaceTriTraits> itc(cybCore->mesh[j]);
			for(itc.initialize(), l = 0; itc.notFinish(); ++itc, l++)
				{
					
					v0 = cybCore->mesh[j]->getVertex(itc->getVertexId(0));
					v1 = cybCore->mesh[j]->getVertex(itc->getVertexId(1));
					v2 = cybCore->mesh[j]->getVertex(itc->getVertexId(2));
	
					glBegin(getViewMode());
					glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
					glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));
	
					glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
					glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));
	
					glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
					glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}
			
			glEndList();
			
			}	
		
	}
	
	void Cyb3DWorld::loadObjects2(){
	
	CybParameters *cybCore = CybParameters::getInstance();
	sVertex *v0, *v1, *v2;	
	
	for(int j=0; j < cybCore->numLayer; j++)	
		{		
		
		for(int i = 0; i < 2; i++) {
		
		if(i == 0) glutSetWindow(rightWindow);
		else glutSetWindow(leftWindow);
		
		objects[freePos] = glGenLists(1);
			
		glNewList(objects[freePos], GL_COMPILE);
		
		freePos++;
				
			int l = 0;
			mfCellsIterator<cybSurfaceTriTraits> itc(cybCore->mesh[j]);
			for(itc.initialize(), l = 0; itc.notFinish(); ++itc, l++)
				{
					
					v0 = cybCore->mesh[j]->getVertex(itc->getVertexId(0));
					v1 = cybCore->mesh[j]->getVertex(itc->getVertexId(1));
					v2 = cybCore->mesh[j]->getVertex(itc->getVertexId(2));
	
					glBegin(getViewMode());
					glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
					glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));
	
					glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
					glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));
	
					glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
					glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}
			
			glEndList();
			
			}
		}
		
	}

//	#ifdef CYBHAPTICS_H
	/**	Function responsible for drawing interator object when haptics is habilitated.
	@param void
	@return void
	*/
/*
	void Cyb3DWorld::drawHapticsCursor()
	{

	 	CybParameters *cybCore = CybParameters::getInstance();
		
		static const double kCursorRadius = 0.5;
		static const double kCursorHeight = 1.5;
		static const int kCursorTess = 15;
		double currentPosition[3], lastPosition[3];
		HLdouble proxyxform[16];
		static bool calcIsNeed = true;
		static GLuint gCursorDisplayList = 0;
		int index = cybCore->activeInterator;	// Interator object actived
		int l;
		sVertex *v0, *v1, *v2;
		
		
		GLUquadricObj *qobj = 0;

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
		glPushMatrix();

		if (!gCursorDisplayList)
		{
			gCursorDisplayList = glGenLists(1);
			glNewList(gCursorDisplayList, GL_COMPILE);
			qobj = gluNewQuadric();


			if(CybInterator::getInstance()->objectType == 0) // interator object from file
			{
				mfCellsIterator<cybTraits> cellsIterator(cybCore->interatorMesh[index]);
				glColor4f(cybCore->interatorColor[index][0], cybCore->interatorColor[index][1], cybCore->interatorColor[index][2], cybCore->interatorColor[index][3]);

				// transformations
				glScaled(cybCore->interatorSca[index][0], cybCore->interatorSca[index][1], cybCore->interatorSca[index][2]);
				glTranslated(cybCore->interatorTrans[index][0], cybCore->interatorTrans[index][1], cybCore->interatorTrans[index][2]);

				glTranslated(-cybCore->interatorStartPosition[index][0], -cybCore->interatorStartPosition[index][1], -cybCore->interatorStartPosition[index][3]);

				glRotated(cybCore->interatorRot[index][0],1,0,0);
				glRotated(cybCore->interatorRot[index][1],0,1,0);
				glRotated(cybCore->interatorRot[index][2],0,0,1);
				glTranslated(cybCore->interatorStartPosition[index][0], cybCore->interatorStartPosition[index][1], cybCore->interatorStartPosition[index][3]);

				for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
				{
					v0 = cybCore->interatorMesh[index]->getVertex(cellsIterator->getVertexId(0));
					v1 = cybCore->interatorMesh[index]->getVertex(cellsIterator->getVertexId(1));
					v2 = cybCore->interatorMesh[index]->getVertex(cellsIterator->getVertexId(2));

					glBegin(GL_TRIANGLES);
						glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
						glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));

						glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
						glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));

						glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
						glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}
			}
			else if(CybInterator::getInstance()->objectType == 2 | CybInterator::getInstance()->objectType == 1)
			{
				CybInterator *interator = CybInterator::getInstance();
				glBegin(GL_QUADS);
					glVertex3f(interator->dimensionHeight, -interator->dimensionWidth, 0);
					glVertex3f(0, -interator->dimensionWidth, 0);
					glVertex3f(0, interator->dimensionWidth, 0);
					glVertex3f(interator->dimensionHeight, interator->dimensionWidth, 0);
				glEnd();

				if(interator->objectType == 2)
				{
					glBegin(GL_QUADS);
					    glVertex3f(0, 0, interator->dimensionWidth);
						glVertex3f(0, 0, -interator->dimensionWidth);
						glVertex3f(interator->dimensionHeight, 0, -interator->dimensionWidth);
						glVertex3f(interator->dimensionHeight, 0, interator->dimensionWidth);
					glEnd();
				}
			}
			else
			{
				glTranslated(0, 0, 0);
				glutSolidSphere(CybInterator::getInstance()->dimensionWidth, 10, 10);
			}

			gluDeleteQuadric(qobj);
			glEndList();
		}

		// Get the proxy transform in world coordinates.
		CybInterator::getInstance()->hapticDevice.getProxyTransformationMatrix(proxyxform);
		
		CybInterator::getInstance()->hapticDevice.getCurrentProxyPosition(currentPosition);
		CybInterator::getInstance()->hapticDevice.getLastProxyPosition(lastPosition);
		
		glMultMatrixd(proxyxform);

		// Apply the local cursor scale factor.
		glScaled(CybInterator::getInstance()->hapticDevice.getHapticScaleFactor(), CybInterator::getInstance()->hapticDevice.getHapticScaleFactor(), CybInterator::getInstance()->hapticDevice.getHapticScaleFactor());

		if(calcIsNeed )
		{
 			CybInterator::getInstance()->objectPosition[0] = currentPosition[0];
 			CybInterator::getInstance()->objectPosition[1] = currentPosition[1];
 			CybInterator::getInstance()->objectPosition[2] = currentPosition[2];
 			
			glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[0]);;
 			calcIsNeed = false;
		}
		else
			calcIsNeed = true;

		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.0, 0.5, 1.0);

		glCallList(gCursorDisplayList);

		glPopMatrix();
		glPopAttrib();

	}
	#endif /*End phantom code */

//	#ifdef CYBTRACKER_H
	/**	Function responsible for drawing interator object when tracker is enable.
	@param void
	@return void
	*/
/*
	void Cyb3DWorld::drawTrackerCursor()
	{

		CybParameters *cybCore = CybParameters::getInstance();
		
		static const double kCursorRadius = 0.5;
		static const double kCursorHeight = 1.5;
		static const int kCursorTess = 15;
		float currentPosition[3];
		float initialPosition[3] = {0,0,0};
		GLfloat  matrix[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		static bool calcIsNeed = true;
		static GLuint gCursorDisplayList = 0;
		int index = cybCore->activeInterator;	// Interator object actived
		int l;
		sVertex *v0, *v1, *v2;
		
		GLUquadricObj *qobj = 0;

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
		glPushMatrix();

		if (!gCursorDisplayList)
		{
			gCursorDisplayList = glGenLists(1);
			glNewList(gCursorDisplayList, GL_COMPILE);
			qobj = gluNewQuadric();


			if(CybInterator::getInstance()->objectType == 0) // interator object from file
			{
				mfCellsIterator<cybTraits> cellsIterator(cybCore->interatorMesh[index]);
				glColor4f(cybCore->interatorColor[index][0], cybCore->interatorColor[index][1], cybCore->interatorColor[index][2], cybCore->interatorColor[index][3]);

				// transformations
				glScaled(cybCore->interatorSca[index][0], cybCore->interatorSca[index][1], cybCore->interatorSca[index][2]);
				glTranslated(cybCore->interatorTrans[index][0], cybCore->interatorTrans[index][1], cybCore->interatorTrans[index][2]);

				glTranslated(-cybCore->interatorStartPosition[index][0], -cybCore->interatorStartPosition[index][1], -cybCore->interatorStartPosition[index][3]);

				glRotated(cybCore->interatorRot[index][0],1,0,0);
				glRotated(cybCore->interatorRot[index][1],0,1,0);
				glRotated(cybCore->interatorRot[index][2],0,0,1);
				glTranslated(cybCore->interatorStartPosition[index][0], cybCore->interatorStartPosition[index][1], cybCore->interatorStartPosition[index][3]);

				for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
				{
					v0 = cybCore->interatorMesh[index]->getVertex(cellsIterator->getVertexId(0));
					v1 = cybCore->interatorMesh[index]->getVertex(cellsIterator->getVertexId(1));
					v2 = cybCore->interatorMesh[index]->getVertex(cellsIterator->getVertexId(2));

					glBegin(GL_TRIANGLES);
						glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
						glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));

						glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
						glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));

						glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
						glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
					glEnd();
				}
			}
			else if(CybInterator::getInstance()->objectType == 2 | CybInterator::getInstance()->objectType == 1)
			{
				CybInterator *interator = CybInterator::getInstance();
				glBegin(GL_QUADS);
					glVertex3f(interator->dimensionHeight, -interator->dimensionWidth, 0);
					glVertex3f(0, -interator->dimensionWidth, 0);
					glVertex3f(0, interator->dimensionWidth, 0);
					glVertex3f(interator->dimensionHeight, interator->dimensionWidth, 0);
				glEnd();

				if(interator->objectType == 2)
				{
					glBegin(GL_QUADS);
						glVertex3f(0, 0, interator->dimensionWidth);
						glVertex3f(0, 0, -interator->dimensionWidth);
						glVertex3f(interator->dimensionHeight, 0, -interator->dimensionWidth);
						glVertex3f(interator->dimensionHeight, 0, interator->dimensionWidth);
					glEnd();
				}
			}
			else
			{
				glTranslated(0, 0, 0);
				glutSolidSphere(CybInterator::getInstance()->dimensionWidth, 10, 10);
			}

			gluDeleteQuadric(qobj);
			glEndList();
		}

		// Get the proxy transform in world coordinates.
		CybInterator::getInstance()->trackerDevice.getMatrix(matrix);
		CybInterator::getInstance()->trackerDevice.getInitialPosition(initialPosition);
		CybInterator::getInstance()->trackerDevice.getPosition(currentPosition);


		glTranslatef(initialPosition[0],initialPosition[1],initialPosition[2]-1);
		glMultMatrixf(matrix);

		// Apply the local cursor scale factor.
		/*glScaled(CybInterator::getInstance()->hapticDevice.getHapticScaleFactor(),
				CybInterator::getInstance()->hapticDevice.getHapticScaleFactor(),
				CybInterator::getInstance()->hapticDevice.getHapticScaleFactor());
	        */
/*		if(calcIsNeed )
		{
 			CybInterator::getInstance()->objectPosition[0] = currentPosition[0] + initialPosition[0];
 			CybInterator::getInstance()->objectPosition[1] = currentPosition[1] + initialPosition[1];
 			CybInterator::getInstance()->objectPosition[2] = currentPosition[2] + initialPosition[2];
 			
			glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[0]);
 			calcIsNeed = false;
		}
		else
			calcIsNeed = true;
		
		


		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.0, 0.5, 1.0);

		glCallList(gCursorDisplayList);

		glPopMatrix();
		glPopAttrib();
	}
	#endif /*End tracker code */

