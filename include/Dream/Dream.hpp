#ifndef _DREAM_HPP_
#define _DREAM_HPP_

#include "psocket.hpp"
#include <Sharun/Sharun.hpp>
#include "thread.hpp"
#include "Fixed_Thread.hpp"
#include "DB.hpp"
#include "TeraCrypt.hpp"
#include "network.hpp"
#include "version.hpp"


float	getDistance(float, float, float, float, float, float);
float	getDistance_2D(float*, float*);
float	getDistance_3D(float*, float*);


float	Stamina(player*);
float	Stamina_power(player*);
float	Stamina_defense(player*);
float	Stamina_owerturnPower(player*);
float	Stamina_owerturnRcpt(player*);

extern float	HP_MOD[CLASS_MAX][LV_Max+1];

#endif // _DREAM_HPP_
