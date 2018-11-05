#pragma once
#include <Siv3D.hpp>
#include "../Config.hpp"

enum MainSkill {
	Shot,
	Grenade,
	Laser,
	Crusher,
};
enum SubSkill {
	Jump,
	Shield,
	Missile,
	Bomb,
};
enum SpecialSkill {
	JudgmentTime,
	LockOn,
	SummonPartner,
	InversionRecovery,
};

class Player {
	private:
	int32 posX;
	int32 posY;
	bool isLeft;
	Circle ship;

	public:
	MainSkill whatMainSKill;
	SubSkill whatSubSkill;
	SpecialSkill whatSpecialSKill;

	class Skill {
		public:

		void Shot(Player&);
		void Grenade(Player&);
		void Laser(Player&);
		void Crusher(Player&);

		void Jump(Player&);
		void Shield(Player&);
		void Missile(Player&);
		void Bomb(Player&);

		void JudgmentTime(Player&);
		void LockOn(Player&);
		void SummonPartner(Player&);
		void InversionRecovery(Player&);
	};

	void DoMainSkill();
	void DoSubSkill();
	void DoSpacialSkill();

	void Init(int32, int32, bool);
	void Control();
	void DrawShip();
};
