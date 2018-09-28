#pragma once
#include<Siv3D.hpp>
#include"Game.h"

Ship leftShip;
Ship rightShip;

void InitShip (){
	leftShip.x = 0;
	leftShip.y = 0;
	leftShip.angle = 0;

	rightShip.x = 0;
	rightShip.y = 0;
	rightShip.angle = 180;
}