#pragma once
#include <Siv3D.hpp>
#include <vector>
#include "../Config.hpp"

#include "./Bullet.hpp"

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
	int32 posX;
	int32 posY;
	bool isLeft;
	Circle ship;
	int selectedType;

	int HP;				//体力
	int temperature;	//Overheat管理
	int charge;			//SpecialSkill管理
	int coolDown;		//SubSkill管理


	public:
	MainSkill whatMainSkill;
	SubSkill whatSubSkill;
	SpecialSkill whatSpecialSkill;

	void DoMainSkill();
	void DoSubSkill();
	void DoSpacialSkill();

	void UpdateMainSkill();
	void UpdateSubSkill();
	void UpdateSpecialSkill();

	void DrawMainSkill();
	void DrawSubSkill();
	void DrawSpecialSkill();

	void Init(int32, int32, bool);
	void Control();
	void SkillSelect();
	void DrawShip();
	void DrawGauge();
};
