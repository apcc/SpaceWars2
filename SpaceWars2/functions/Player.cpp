#pragma once
#include "Player.hpp"

#define PLAYER_SPEED 10

void Player::Init(int32 _x, int32 _y, bool _isLeft){	
	posX = _x;
	posY = _y;
	isLeft = _isLeft;
}

void Player::Control(){
	Rect tmpZoon;

	if(isLeft){
		tmpZoon = Rect(0, 0, Config::Width / 2, Config::Height);
		if(Input::KeyD.pressed && tmpZoon.contains(Circle(posX + PLAYER_SPEED, posY, 40)))			posX += PLAYER_SPEED;
		if(Input::KeyA.pressed && tmpZoon.contains(Circle(posX - PLAYER_SPEED, posY, 40)))			posX -= PLAYER_SPEED;
		if(Input::KeyW.pressed && tmpZoon.contains(Circle(posX, posY - PLAYER_SPEED, 40)))			posY -= PLAYER_SPEED;
		if(Input::KeyS.pressed && tmpZoon.contains(Circle(posX, posY + PLAYER_SPEED, 40)))			posY += PLAYER_SPEED;
	}else{
		tmpZoon = Rect(Config::Width/2, 0, Config::Width / 2, Config::Height);
		if(Input::KeySemicolon.pressed && tmpZoon.contains(Circle(posX + PLAYER_SPEED, posY, 40)))	posX += PLAYER_SPEED;
		if(Input::KeyK.pressed && tmpZoon.contains(Circle(posX - PLAYER_SPEED, posY, 40)))			posX -= PLAYER_SPEED;
		if(Input::KeyO.pressed && tmpZoon.contains(Circle(posX, posY - PLAYER_SPEED, 40)))			posY -= PLAYER_SPEED;
		if(Input::KeyL.pressed && tmpZoon.contains(Circle(posX, posY + PLAYER_SPEED, 40)))			posY += PLAYER_SPEED;
	}
	ship = Circle(posX, posY, 40);
}