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
	Vec2 pos;
	bool isLeft;
	int selectedType;

	int HP;				//体力
	int temperature;	//Overheat管理
	int charge;			//SpecialSkill管理
	int coolDown;		//SubSkill管理


public:

	MainSkill whatMainSkill;
	SubSkill whatSubSkill;
	SpecialSkill whatSpecialSkill;

	void doMainSkill(std::vector<Bullet*>& bullets);
	void doSubSkill(std::vector<Bullet*>& bullets);
	void doSpacialSkill(std::vector<Bullet*>& bullets);

	//int  UpdateMainSkill(Circle rivalCircle);
	void updateSubSkill();
	void updateSpecialSkill();

	// void DrawMainSkill();
	void drawSubSkill();
	void drawSpecialSkill();

	void init(Vec2 pos, bool isLeft);
	Circle circle();
	void receiveDamage(int damage);
	bool isHPRunOut();
	void update(std::vector<Bullet*> &bullets);
	void skillSelect();
	void drawShip();
	void drawGauge();
};
