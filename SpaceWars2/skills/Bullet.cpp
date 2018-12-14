#include "./Bullet.hpp"

// true if destroyed
bool Bullet::update(){
	pos += vel;
	if(isInvisible()){
		// ウィンドウからのはみ出し
		return true;
	}
	return false;
}
