#pragma once
#include "Player.hpp"

#define SPEED 3

void Player::Init(int32 _x, int32 _y, bool _isLeft){	
	posX = _x;
	posY = _y;
	isLeft = _isLeft;
}

void Player::Control(){
	int32 tmpX = 0, tmpY = 0;
	Rect tmpZoon;
	tmpX = this->posX;
	tmpY = this->posY;

	if(this->isLeft){
		tmpZoon = Rect(0, 0, Config::Width / 2, Config::Height);
		if(Input::KeyD.pressed && tmpZoon.contains(Circle(this->posX + SPEED, this->posY, 40)))			this->posX += SPEED;
		if(Input::KeyA.pressed && tmpZoon.contains(Circle(this->posX - SPEED, this->posY, 40)))			this->posX -= SPEED;
		if(Input::KeyW.pressed && tmpZoon.contains(Circle(this->posX, this->posY - SPEED, 40)))			this->posY -= SPEED;
		if(Input::KeyS.pressed && tmpZoon.contains(Circle(this->posX, this->posY + SPEED, 40)))			this->posY += SPEED;
	}else{
		tmpZoon = Rect(Config::Width/2, 0, Config::Width / 2, Config::Height);
		if(Input::KeySemicolon.pressed && tmpZoon.contains(Circle(this->posX + SPEED, this->posY, 40)))	this->posX += SPEED;
		if(Input::KeyK.pressed && tmpZoon.contains(Circle(this->posX - SPEED, this->posY, 40)))			this->posX -= SPEED;
		if(Input::KeyO.pressed && tmpZoon.contains(Circle(this->posX, this->posY - SPEED, 40)))			this->posY -= SPEED;
		if(Input::KeyL.pressed && tmpZoon.contains(Circle(this->posX, this->posY + SPEED, 40)))			this->posY += SPEED;
	}
	this->ship = Circle(this->posX, this->posY, 40);
}