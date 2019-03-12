#include <Siv3D.hpp>
#include "Config.hpp"
#include "CommonData.hpp"

// Scenes
#include "scenes/Opening.hpp"
#include "scenes/ControlGuidance.hpp"
#include "scenes/ScreenGuidance.hpp"
#include "scenes/SkillSelect.hpp"
#include "scenes/Game.hpp"
#include "scenes/Finish.hpp"
#include "scenes/Ending.hpp"


Font CicaR32;
enum Mode gamemode;

void Main(){

	Window::SetTitle(Config::TITLE);
	Window::Resize(Config::WIDTH, Config::HEIGHT);
	Graphics::SetBackground(Color(Config::BACKGROUND));

	TextureAsset::Register(L"background", L"/7801");
	FontManager::Register(L"/7701");
	FontAsset::Register(L"CicaR32", 32, L"Cica");

	SceneManager<String,CommonData> manager;
	manager.add<Opening>(L"Opening");
	manager.add<ControlGuidance>(L"ControlGuidance");
	manager.add<ScreenGuidance>(L"ScreenGuidance");
	manager.add<SkillSelect>(L"SkillSelect");
	manager.add<Game>(L"Game");
	manager.add<Finish>(L"Finish");
	manager.add<Ending>(L"Ending");


	while (System::Update()){
		manager.updateAndDraw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
