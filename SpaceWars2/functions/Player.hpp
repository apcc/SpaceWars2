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

	void DoMainSkill(std::vector<Bullet*>& bullets);
	void DoSubSkill(std::vector<Bullet*>& bullets);
	void DoSpacialSkill(std::vector<Bullet*>& bullets);

	//int  UpdateMainSkill(Circle rivalCircle);
	void UpdateSubSkill();
	void UpdateSpecialSkill();

	// void DrawMainSkill();
	void DrawSubSkill();
	void DrawSpecialSkill();

	void Init(Vec2 pos, bool isLeft);
	Circle circle();
	void receiveDamage(int damage);
	bool isHPRunOut();
	void Update(std::vector<Bullet*> &bullets);
	void SkillSelect();
	void DrawShip();
	void DrawGauge();
};
