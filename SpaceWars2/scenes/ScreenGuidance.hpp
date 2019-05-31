#pragma once
#include "Include.hpp"
#include "Game.hpp"


enum Stat {
	FULL,
	HP,
	TEMPERATURE,
	OVER_HEAT,
	CHARGE,
	LETS_GO,

	COUNT
};

class ScreenGuidance final : public SceneManager<String,CommonData>::Scene {
private:
	Stat status = FULL;
	const Texture gaugePic = Texture(Image(L"/7960").scale(1.5));

	const Array<Array<Point>> shadowPos = {
	{ { 0, 0 }, { 0, 0 } }, // FULL
	{ { 180, 48 }, { 600, 48 } }, // HP
	{ { 315, 85 }, { 480, 48 } }, // TEMPERATURE
	{ { 180, 85 }, {  90, 48 } }, // OVER_HEAT
	{ { 45, 30 }, { 120, 120 } }, // CHARGE
	{ { 0, 0 }, { 0, 0 } }, // LETS_GO
	};
	const Array<Color> frameColor = {
		Color(L"#fff"), // FULL
		Color(L"#f66"), // HP
		Color(L"#2f8"), // TEMPERATURE
		Color(L"#bbf"), // OVER_HEAT
		Color(L"#ff2"), // CHARGE
		Color(L"#fff"), // LETS_GO
	};
	const Array<String> description = {
		L"画面上部に表示されているのがプレイヤーの情報です。\nAボタン/Enterで次に進みます。",
		L"赤いゲージがHPを表しています。\n先にHPが0になった方が負けです。",
		L"緑のゲージは機体の温度を表示しています。\nmainSkillを使用し続けるとゲージの色が変わり、\n温度が高くなりすぎると発射できなくなります。",
		L"青い数字はsubSkillのクールダウンを表しています。\nクールダウン中はsubSkillを使えません。",
		L"黄色いリングはチャージを表しています。\nダメージを受けると段々溜まっていって、\n100％まで溜まると強力なspecialSkillを発動できます。",
		L"説明はここまでです。\nskillによって温度がどれくらい上がりやすいか、\n等が違うのでいろいろ試してみてください。"
	};

	template<typename T>
	static void rightAlign(Font _font, T _text, int _x, int _y, Color _color = Color(L"#fff"));

public:
	void init() override;
	void update() override;
	void draw() const override;
};
