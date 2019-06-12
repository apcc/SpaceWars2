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
	int nextStageTime = 0;
	bool LReady = false;
	bool RReady = false;
	Vec2 playerPos[2][2];
	bool movetoUp[2][2] = {};
	int skillsDisplayed[2][3] = {}; //[isLeft][skillType]
	int skillTypeDisplayed[2] = {}; //[isLeft]
	int blackOutTime[2] = {};
	bool goingTowhiteout[2] = {};
	int BLACKOUT_TIME = 6;
	std::vector<Bullet*> bullets[2];
	int coolDownTime[2] = {};
	double shrinkRate;
	Rect bulletArea[2] = {};
	int judgementTime[2] = {};
	Vec2 shrinkVec2(Vec2, int) const;

	static SkillDescriptManager skillDescriptManager;
public:
	void init() override;
	void update() override;
	void draw() const override;

	~SkillSelect() {
		for (int isLeft = 0; isLeft < 2; isLeft++) {
			for (auto i : bullets[isLeft]) delete i;
			bullets[isLeft].clear();
		}
	}
};
