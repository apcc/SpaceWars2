#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"CommonData.hpp"

class Game : public SceneManager<String,CommonData>::Scene {
private:
	Font CicaR32;
	int y = 0;
	bool mode = false;
public:
	void init() override;
	void update() override;
	void draw() const override;
};


//////// 変数 ////////

struct Ship {
	int32 x;
	int32 y;
	int32 angle;
	int32 hp;
	int32 power;
	int32 temperature;
};

extern Ship leftShip;
extern Ship rightShip;

//////// 関数 ////////

void InitShip ();
