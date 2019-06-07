#include <Siv3D.hpp>
#include "Config.hpp"
#include "CommonData.hpp"
#include "functions/Asset.hpp"

// Scenes
#include "scenes/Title.hpp"
#include "scenes/License.hpp"
#include "scenes/ControlGuidance.hpp"
#include "scenes/ScreenGuidance.hpp"
#include "scenes/SkillSelect.hpp"
#include "scenes/Game.hpp"

void Main(){

	Window::SetTitle(Config::TITLE);
	Window::Resize(Config::WIDTH, Config::HEIGHT);
	Graphics::SetBackground(Color(Config::BACKGROUND));

	TextureAsset::Register(L"background", L"/7801");
	TextureAsset::Register(L"title-logo", L"/7900");
	TextureAsset::Register(L"title-button", L"/7901");
	TextureAsset::Register(L"title-button-hidden", L"/7902");
	TextureAsset::Register(L"license", L"/7910");
	TextureAsset::Register(L"controller", L"/7950");
	TextureAsset::Register(L"gauge", L"/7960");
	TextureAsset::Register(L"github-light", L"/7970");
	TextureAsset::Register(L"keyboard", L"/7980");
	TextureAsset::Register(L"l-player", L"/7990");
	TextureAsset::Register(L"r-player", L"/7991");
	TextureAsset::Register(L"fire", L"/7995");
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
	TextureAsset::Register(L"buttonA_64", L"/8600");
	TextureAsset::Register(L"buttonB_64", L"/8601");
	TextureAsset::Register(L"buttonX_64", L"/8602");
	TextureAsset::Register(L"buttonY_64", L"/8603");
	TextureAsset::Register(L"buttonLB_64", L"/8610");
	TextureAsset::Register(L"buttonRB_64", L"/8611");
	TextureAsset::Register(L"buttonLT_64", L"/8612");
	TextureAsset::Register(L"buttonRT_64", L"/8613");
	TextureAsset::Register(L"stick_64", L"/8620");
	TextureAsset::Register(L"cross_64", L"/8621");

	SoundAsset::Register(L"shot", L"/9000");
	SoundAsset::Register(L"grenade1", L"/9010");
	SoundAsset::Register(L"grenade2", L"/9011");
	SoundAsset::Register(L"laser", L"/9020");
	SoundAsset::Register(L"reflection", L"/9030");
	SoundAsset::Register(L"flame", L"/9040");
	SoundAsset::Register(L"jump", L"/9100");
	SoundAsset::Register(L"shield", L"/9110");
	SoundAsset::Register(L"missile", L"/9120");
	SoundAsset::Register(L"bomb", L"/9130");
	SoundAsset::Register(L"JT", L"/9200");
	SoundAsset::Register(L"LO", L"/9210");
	SoundAsset::Register(L"SP", L"/9220");
	SoundAsset::Register(L"IR", L"/9230");

	FontManager::Register(L"/7700");
	FontManager::Register(L"/7701");
	FontManager::Register(L"/7702");
	SmartUI::Register();
	SmartB::Register();
	CicaR::Register();
	Letters::Register();

	SceneManager<String,CommonData> manager;
	manager.add<Title>(L"Title");
	manager.add<License>(L"License");
	manager.add<ControlGuidance>(L"ControlGuidance");
	manager.add<ScreenGuidance>(L"ScreenGuidance");
	manager.add<SkillSelect>(L"SkillSelect");
	manager.add<Game>(L"Game");


	while (System::Update()){
		manager.updateAndDraw();
		Debug::DebugModeWarning();
	}
}
