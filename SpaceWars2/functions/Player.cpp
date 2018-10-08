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
	Rect tmpZoon;// = Rect(0, 0, 0, 0);
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
	/*if(this->isLeft){
		if(Input::KeyD.pressed)			this->posX += SPEED;
		else if(Input::KeyA.pressed)	this->posX -= SPEED;
		if(Input::KeyW.pressed)			this->posY -= SPEED;
		else if(Input::KeyS.pressed)	this->posY += SPEED;
		tmpZoon = Rect(0, 0, Config::Width / 2, Config::Height);
	}else{
		if(Input::KeySemicolon.pressed)	this->posX += SPEED;
		else if(Input::KeyK.pressed)	this->posX -= SPEED;
		if(Input::KeyO.pressed)			this->posY -= SPEED;
		else if(Input::KeyL.pressed)	this->posY += SPEED;
		tmpZoon = Rect(Config::Width/2, 0, Config::Width / 2, Config::Height);
	}
	this->ship = Circle(this->posX, this->posY, 40);
	if(tmpZoon.contains(this->ship) == false){
		this->posX = tmpX;
		this->posY = tmpY;
	}*/
}