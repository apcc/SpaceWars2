#include "./Bullet.hpp"

// true if destroyed
bool Bullet::update(){
	pos += vel;
	if(shouldBeDestroyed)
		return true;
	if(isInvisible()){
		// ウィンドウからのはみ出し
		return true;
	}
	return false;
}
