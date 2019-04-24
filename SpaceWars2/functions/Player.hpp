#pragma once
#include <Siv3D.hpp>
#include "../skills/Bullet.hpp"
#include "./XInput.hpp"
#include "./KeyRepeat.hpp"

enum MainSkill {
	SHOT,
	GRENADE,
	LASER,
	REFLECTION,
	FLAME,

	MAIN_NUM,
};
enum SubSkill {
	JUMP,
	SHIELD,
	MISSILE,
	BOMB,

	SUB_NUM,
};
enum SpecialSkill {
	JUDGMENT_TIME,
	LOCK_ON,
	SUMMON_PARTNER,
	INVERSION_RECOVERY,

	SPECIAL_NUM,
};

class Player {
private:
	Vec2 pos = {};			// pos
	bool isLeft = true;		// 左右
	int selectedType = 0;	// skillSelectの選択中項目
	int speed = 0;

	int requireCharge[4] = { 400, 400, 400, 400 };

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
	int HP;				// 体力
	int temperature;	// MainSkill抑制
	int coolDownTime;	// SubSkill抑制
	int charge;			// SpecialSkill抑制

	bool inRecovery;
	static bool inJudgmentTime;
	const static int JT_TIME = 180;
	int judgmentLife = -1;	// JudgmentTimeの残り時間

	MainSkill whatMainSkill = SHOT;
	SubSkill whatSubSkill = JUMP;
	SpecialSkill whatSpecialSkill = JUDGMENT_TIME;

	int mainSkillCnt;
	int subSkillCnt;
	int specialSkillCnt;

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
	int skillSelect();
	void drawShip();
	void drawGauge();
};
