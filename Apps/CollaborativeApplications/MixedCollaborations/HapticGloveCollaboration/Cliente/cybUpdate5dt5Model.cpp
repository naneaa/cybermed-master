#include <cybermed/cybGlove.h> //adicionado, testar
#include "cybHandModel.h"
#include "fglove.h" //precisa por está usando enumerações da 5DT
#include "cybUpdate5dt5Model.h" 



void CybUpdate5dt5Model::update(CybDevice *device, CybModel *models) {
	
	CybGlove *glove = dynamic_cast<CybGlove *>(device);
	CybHandModel *handModel = dynamic_cast<CybHandModel *>(models);
	
	int size = glove->getNumSensors();	
	float gloveA_scaled[size];
	float *eixo = new float[18];
	glove->getSensorScaledAll(gloveA_scaled);
	
	float angBase = 90;
	
	eixo[0] = gloveA_scaled[0] * 60; //35 //base d0
   eixo[1] = gloveA_scaled[1] * 118; //meiod0
   eixo[2] =  0.5 * -30 ; //ok //junta
   eixo[3] = gloveA_scaled[3] * angBase; //base d1
	eixo[4] = eixo[5] = gloveA_scaled[3] * 97; //meio e ponta d1
	eixo[6] = (1 - 0.5) * 25; //junta
	eixo[7] = gloveA_scaled[6] * angBase; //base d2
	eixo[8] = eixo[9] = gloveA_scaled[7] * 97; //meio e ponta d2
	eixo[10] = (1 - 0.5) * -23; //junta
	eixo[11] = gloveA_scaled[9] * angBase; //base d3
	eixo[12] = eixo[13] = gloveA_scaled[10] * 91; //meio e ponta d3
	eixo[14] = (1 - 0.5) * -30; //junta
	eixo[15] = gloveA_scaled[12] * angBase; //base d4
	eixo[16] =  eixo[17] = gloveA_scaled[13] * 98; //meio e ponta d

	
	handModel->setMatrix(eixo);
	//std::cout << "Ta funcionando" << std::endl;
	
}
