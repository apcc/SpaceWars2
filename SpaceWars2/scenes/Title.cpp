#include "Title.hpp"

int Title::selecting = 0;

void Title::init(){
	Data::LPlayer.init(Vec2(  80, Config::HEIGHT/2), true);  //円の半径
	Data::RPlayer.init(Vec2(1200, Config::HEIGHT/2), false); //WIDTH-円の半径
}

void Title::update(){
	changeScene(Debug::InputFnKey(), 250);

	if (Data::KeyUp.repeat(20, true) && selecting > 0)
		--selecting;
	if (Data::KeyDown.repeat(20, true) && selecting < 3)
		++selecting;

	if (Data::KeyEnter.repeat(20)) {
		switch(selecting) {
		case 0:
			changeScene(L"ControlGuidance", 500);
			break;

		case 1:
			changeScene(L"SkillSelect", 500);
			break;

		case 2:
			changeScene(L"License", 500);
			break;

		case 3:
			System::Exit();
			break;

		default:
			LOG_ERROR(L"Title画面で意図しない値 \"", selecting, L"\" が参照されました。");
		}
	}

}

void Title::draw() const{
	TextureAsset(L"background").resize(Window::Size()).draw();
	TextureAsset(L"title-logo").drawAt(Window::Center().x, 150);

	Circle(1180, 1080, 760).drawFrame(5, 5, Color(L"#00bfff"));

	const String name[4] = { L"START", L"GAME", L"LICENSE", L"EXIT" };
	for (auto i : step(4)) {
		TextureAsset(i == selecting ? L"title-button" : L"title-button-hidden").draw(950, 400 + 70 * i);
		SmartUI::Get(S28)(name[i]).draw({ 980, 398 + 70 * i }, (i == selecting ? Color(L"#fff") : Color(L"#ccc")));
	}

	Rect(0, 690, 220, 30).draw(ColorF(L"#000").setAlpha(0.5));
	CicaR::Get(C12)(Config::VERSION, L" / ", Config::VER_NUM).draw({ 10, 695 });

	Vec2 buttonPos(1165, 692);

	buttonPos.x += (int)TextureAsset(L"cross_24").draw(buttonPos, Alpha(200)).w + 5;
	buttonPos.x += (int)TextureAsset(L"stick_24").draw(buttonPos, Alpha(200)).w + 10;
	buttonPos.x += (int)CicaR::Get(C12)(L"/").draw(buttonPos, Alpha(200)).w + 10;
	buttonPos.x += (int)TextureAsset(L"buttonA_24").draw(buttonPos, Alpha(200)).w + 6;
}
