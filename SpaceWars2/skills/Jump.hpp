#pragma once
#include <Siv3D.hpp>
#include "Bullet.hpp"
#include "../CommonData.hpp"


class Jump final : public Bullet {
private:
	int frameCount = 0;
	bool isLInvalid = false;
	bool isRInvalid = false;
	static bool isLDoing;
	static bool isRDoing;
	Circle getShape() { return Circle(pos, 0); }
public:
	Jump(Vec2 _pos, bool _isLeft) : Bullet(_pos, _isLeft) {
		(isLeft ? Data::LPlayer : Data::RPlayer).changeSpeed(200);
		SoundAsset(L"jump").setVolume(Config::masterVolume*Config::effectSoundVolume);
		SoundAsset(L"jump").playMulti(0.8);

		if (!(isLeft ? isLDoing : isRDoing)){
			(isLeft ? isLInvalid : isRInvalid) = true;
			frameCount = System::FrameCount() % 1000;
		} else {
			(isLeft ? isLDoing : isRDoing) = true;
		}
	}
	~Jump() {
		(isLeft ? Data::LPlayer : Data::RPlayer).changeSpeed(8);

		if (isLeft ? isLInvalid : isRInvalid)
			(isLeft ? isLDoing : isRDoing) = false;
	}

	bool update(Vec2 _myPos, Vec2 _oppPos) override;
	void draw() override;
	bool isVisible() override;
	int getDamage(Circle _circle) override;
};
