#include <Siv3D.hpp>
#include "Config.hpp"
#include "CommonData.hpp"

// Scenes
#include "scenes/Opening.hpp"
#include "scenes/License.hpp"
#include "scenes/ControlGuidance.hpp"
#include "scenes/ScreenGuidance.hpp"
#include "scenes/SkillSelect.hpp"
#include "scenes/Game.hpp"
#include "scenes/Ending.hpp"

void Main(){

	Window::SetTitle(Config::TITLE);
	Window::Resize(Config::WIDTH, Config::HEIGHT);
	Graphics::SetBackground(Color(Config::BACKGROUND));

	TextureAsset::Register(L"background", L"/7801");
	TextureAsset::Register(L"title-logo", L"/7900");
	TextureAsset::Register(L"license", L"/7910");
	TextureAsset::Register(L"buttonA_24", L"/8500");
	TextureAsset::Register(L"buttonB_24", L"/8501");
	TextureAsset::Register(L"buttonX_24", L"/8502");
	TextureAsset::Register(L"buttonY_24", L"/8503");
	TextureAsset::Register(L"buttonLB_24", L"/8510");
	TextureAsset::Register(L"buttonRB_24", L"/8511");
	TextureAsset::Register(L"buttonLT_24", L"/8512");
	TextureAsset::Register(L"buttonRT_24", L"/8513");
	TextureAsset::Register(L"stick_24", L"/8520");
	TextureAsset::Register(L"cross_24", L"/8521");
	FontManager::Register(L"/7700");
	FontManager::Register(L"/7701");
	FontManager::Register(L"/7702");
	FontAsset::Register(L"Smart32", 32, L"03SmartFont-Proportional");
	FontAsset::Register(L"Smart28", 28, L"03SmartFont-Proportional");
	FontAsset::Register(L"Smart12", 12, L"03SmartFont-Proportional");
	FontAsset::Register(L"SmartB12", 12, L"03SmartFont-Proportional", FontStyle::Bold);
	FontAsset::Register(L"CicaR32", 32, L"Cica");
	FontAsset::Register(L"CicaR18", 18, L"Cica");
	FontAsset::Register(L"CicaR12", 12, L"Cica");
	FontAsset::Register(L"Letters18", 18, L"Letters Laughing");
	FontAsset::Register(L"Letters12", 12, L"Letters Laughing");
	FontAsset::Register(L"Letters10", 10, L"Letters Laughing");
	FontAsset::Register(L"Letters7", 7, L"Letters Laughing");

	SceneManager<String,CommonData> manager;
	manager.add<Opening>(L"Opening");
	manager.add<License>(L"License");
	manager.add<ControlGuidance>(L"ControlGuidance");
	manager.add<ScreenGuidance>(L"ScreenGuidance");
	manager.add<SkillSelect>(L"SkillSelect");
	manager.add<Game>(L"Game");
	manager.add<Ending>(L"Ending");


	while (System::Update()){
		manager.updateAndDraw();
	}
}
