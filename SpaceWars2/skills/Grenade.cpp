#include "./Grenade.hpp"

bool Grenade::update(Vec2 _myPos, Vec2 _oppPos) {
	if (fuse == 0) return true;
	if (fuse <= EXPLODE_TIMING) vel.set(0,0);
	if (fuse == EXPLODE_TIMING) {
		SoundAsset(L"grenade2").setVolume(Config::masterVolume*Config::cursolSoundVolume);
		SoundAsset(L"grenade2").playMulti();
		}
	--fuse;
	return Bullet::update(_myPos, _oppPos);
}

void Grenade::draw(){
	if(fuse<=EXPLODE_TIMING){
		getShape().draw(ColorF(L"#ff8800").setAlpha(((double)fuse) / EXPLODE_TIMING));
	}
	else {
		if (isLeft)TextureAsset(L"mainBullet1").resize(30, 30).drawAt(pos);
		else TextureAsset(L"mainBullet1").resize(30, 30).mirror().drawAt(pos);
		//	getShape().draw(Color(L"#ff0000"));
	}
}

bool Grenade::isVisible(){
	return getShape().intersects(Rect(0, 0, Config::WIDTH + 1, Config::HEIGHT + 1));
}

int Grenade::getDamage(Circle _circle){
	if(_circle.intersects(this->getShape())){
		if (fuse > EXPLODE_TIMING) {
			this->explode();
			return 60;
		}
		if(fuse == EXPLODE_TIMING)
			return (int)(((EXPLODE_RADIUS + 60) - pos.distanceFrom(_circle.center)) / (EXPLODE_RADIUS + 60) * 40);
		return 0;
	}
	return 0;
}

void Grenade::explode(){
	fuse = EXPLODE_TIMING;
}
