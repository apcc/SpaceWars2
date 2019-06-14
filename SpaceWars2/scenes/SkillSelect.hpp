#pragma once
#include "Include.hpp"
#include "../functions/SkillDescription.hpp"
#include "../skills/Bullet.hpp"
#include "../skills/Shot.hpp"
#include "../skills/Grenade.hpp"
#include "../skills/VLaser.hpp"
#include "../skills/Reflection.hpp"
#include "../skills/Flame.hpp"
#include "../skills/Jump.hpp"
#include "../skills/Shield.hpp"
#include "../skills/Missile.hpp"
#include "../skills/Bomb.hpp"
#include "../skills/LockOn.hpp"
#include "../skills/SummonPartner.hpp"
#include "../skills/InversionRecovery.hpp"

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:
	static bool isLoaded;
	static SkillDescriptManager skillDescriptionManager;

	int nextStageTime = 0;
	bool LReady = false;
	bool RReady = false;
	Texture rotatedDescription[4];
	Vec2 playerPos[2][2] = {};
	bool moveToUp[2][2] = {};
	int skillsDisplayed[2][3] = {}; //[isLeft][skillType]
	int skillTypeDisplayed[2] = {}; //[isLeft]
	int blackOutTime[2] = {};
	bool goingToBlackOut[2] = {};
	int BLACKOUT_TIME = 6;
	std::vector<Bullet*> bullets[2];
	int coolDownTime[2] = {};
	double shrinkRate = 0;
	Rect bulletArea[2] = {};
	int judgmentTime[2] = {};
	int playerHP[2] = {};
	int timerCount[2] = {};
	Vec2 shrinkVec2(Vec2, int) const;
	void drawHPGauge(bool _isLeft, int HP) const;

	Circle getHitCircle(Vec2 _pos, bool isLeft) {
		if (skillTypeDisplayed[isLeft] == 1 && skillsDisplayed[isLeft][1] == 1) {
			return Circle(_pos, 200 * shrinkRate);
		}
		return Circle(_pos, 30 * 0.4);
	}

public:
	void init() override;
	void update() override;
	void draw() const override;

	~SkillSelect() {
		for (auto isLeft : step(2)) {
			for (auto i : bullets[isLeft]) delete i;
			bullets[isLeft].clear();
		}
	}
};
