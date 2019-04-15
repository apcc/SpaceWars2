#include <Siv3D.hpp>
#include "Config.hpp"
#include "CommonData.hpp"

// Scenes
#include "scenes/Opening.hpp"
#include "scenes/License.hpp"
#include "scenes/ControlGuidance.hpp"
#include "scenes/ScreenGuidance.hpp"
#include "scenes/SkillSelect.hpp"
#include "scenes/Countdown.hpp"
#include "scenes/Game.hpp"
#include "scenes/Finish.hpp"
#include "scenes/Ending.hpp"
#include "scenes/License.hpp"

void Main(){

	Window::SetTitle(Config::TITLE);
	Window::Resize(Config::WIDTH, Config::HEIGHT);
	Graphics::SetBackground(Color(Config::BACKGROUND));

	TextureAsset::Register(L"background", L"/7801");
	TextureAsset::Register(L"title-logo", L"/7900");
	TextureAsset::Register(L"license", L"/7910");
	FontManager::Register(L"/7701");
	FontAsset::Register(L"CicaR32", 32, L"Cica");
	FontAsset::Register(L"CicaR24", 24, L"Cica");
	FontAsset::Register(L"CicaR18", 18, L"Cica");
	FontAsset::Register(L"CicaR12", 12, L"Cica");

	SceneManager<String,CommonData> manager;
	manager.add<Opening>(L"Opening");
	manager.add<License>(L"License");
	manager.add<ControlGuidance>(L"ControlGuidance");
	manager.add<ScreenGuidance>(L"ScreenGuidance");
	manager.add<SkillSelect>(L"SkillSelect");
	manager.add<Three>(L"Three");
	manager.add<Two>(L"Two");
	manager.add<One>(L"One");
	manager.add<Game>(L"Game");
	manager.add<Finish>(L"Finish");
	manager.add<Ending>(L"Ending");


	while (System::Update()){
		manager.updateAndDraw();
	}
}
