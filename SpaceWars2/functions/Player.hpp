#pragma once
#include <Siv3D.hpp>
#include <vector>
#include "../Config.hpp"

#include "../skills/Bullet.hpp"

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
	JUDGEMENT_TIME,
	LOCK_ON,
	SUMMON_PARTNER,
	INVERESION_RECOVERY,
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

	std::vector<Bullet*> bullets;

	void DoMainSkill();
	void DoSubSkill();
	void DoSpacialSkill();

	int  UpdateMainSkill(Circle rivalCircle);
	void UpdateSubSkill();
	void UpdateSpecialSkill();

	void DrawMainSkill();
	void DrawSubSkill();
	void DrawSpecialSkill();

	void Init(Vec2 pos, bool isLeft);
	Circle circle();
	void receiveDamage(int damage);
	bool gameEnd();
	void Control();
	void SkillSelect();
	void DrawShip();
	void DrawGauge();
};
