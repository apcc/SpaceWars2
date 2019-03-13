#pragma once
#include <Siv3D.hpp>
#include <vector>
#include "../Config.hpp"

#include "../skills/Bullet.hpp"
#include "../skills/Shot.hpp"

enum MainSkill {
	SHOT,
	GRENADE,
	LASER,
	CRUSHER,
};
enum SubSkill {
	JUMP,
	SHIELD,
	MISSILE,
	BOMB,
};
enum SpecialSkill {
	JUDGMENT_TIME,
	LOCK_ON,
	SUMMON_PARTNER,
	INVERSION_RECOVERY,
};

class Player {
private:
	Vec2 pos = {};			// pos
	bool isLeft = true;		// 左右
	int selectedType = 0;	// skillSelectの選択中項目

	int HP = 0;				// 体力


public:

	MainSkill whatMainSkill = SHOT;
	SubSkill whatSubSkill = JUMP;
	SpecialSkill whatSpecialSkill = JUDGMENT_TIME;

	void doMainSkill(std::vector<Bullet*>& bullets);
	void doSubSkill(std::vector<Bullet*>& bullets);
	void doSpacialSkill(std::vector<Bullet*>& bullets);
	
	void init(Vec2 pos, bool isLeft);
	Circle circle();
	void receiveDamage(int damage);
	bool isHPRunOut();
	void update(std::vector<Bullet*> &bullets);
	void skillSelect();
	void drawShip();
	void drawGauge();
};
