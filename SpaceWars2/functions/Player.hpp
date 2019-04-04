#pragma once
#include <Siv3D.hpp>
#include "../skills/Bullet.hpp"
#include "./XInput.hpp"
#include "./KeyRepeat.hpp"

enum MainSkill {
	SHOT,
	GRENADE,
	LASER,
	CRUSHER,
	HOMING,
	REFLECTION,
	FLAME,
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
	int speed = 0;

	int HP;				//体力
	int temperature;	//Overheat管理
	int charge;			//SpecialSkill管理
	int coolDown;		//SubSkill管理
	int requireCharge[3] = {40, 40, 40};

	const int PLAYER_SIZE = 30;
	int hitSize = 30;		// 当たり判定半径
	int shieldDamage = 0;	// Shieldが受けたダメージ量

	KeyRepeat KeyUp = KeyRepeat();
	KeyRepeat KeyLeft = KeyRepeat();
	KeyRepeat KeyDown = KeyRepeat();
	KeyRepeat KeyRight = KeyRepeat();

	KeyRepeat KeyMainSkill = KeyRepeat();
	KeyRepeat KeySubSkill = KeyRepeat();
	KeyRepeat KeySpecialSkill = KeyRepeat();

public:

	MainSkill whatMainSkill = SHOT;
	SubSkill whatSubSkill = JUMP;
	SpecialSkill whatSpecialSkill = JUDGMENT_TIME;

	void doMainSkill(std::vector<Bullet*>& bullets);
	void doSubSkill(std::vector<Bullet*>& bullets);
	void doSpacialSkill(std::vector<Bullet*>& bullets);
	
	void init(Vec2 _pos, bool _isLeft);
	Circle circle();	// 本体Circle
	Circle hitCircle();	// 当たり判定
	void receiveDamage(int _damage);
	void changeSpeed(int _speed);
	int changeHitSize(int _hitSize);
	bool isHPRunOut();
	void update(std::vector<Bullet*> &bullets);
	void skillSelect();
	void drawShip();
	void drawGauge();
};
