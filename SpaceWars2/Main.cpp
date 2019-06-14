#include <Siv3D.hpp>
#include "Config.hpp"
#include "CommonData.hpp"
#include "functions/Asset.hpp"
#include "functions/Utils.hpp"

// Scenes
#include "scenes/Title.hpp"
#include "scenes/License.hpp"
#include "scenes/ControlGuidance.hpp"
#include "scenes/ScreenGuidance.hpp"
#include "scenes/SkillSelect.hpp"
#include "scenes/Game.hpp"

void Main() {

	Window::SetTitle(Config::TITLE);
	Window::Resize(Config::WIDTH, Config::HEIGHT);
	Graphics::SetBackground(Color(Config::BACKGROUND));

	TextureAsset::Register(L"background"  , L"/7000");
	TextureAsset::Register(L"title-logo"  , L"/7100");
	TextureAsset::Register(L"title-button", L"/7110");
	TextureAsset::Register(L"title-button-hidden", L"/7111");
	TextureAsset::Register(L"license"     , L"/7200");
	TextureAsset::Register(L"buttonA_24"  , L"/7800");
	TextureAsset::Register(L"buttonB_24"  , L"/7801");
	// TextureAsset::Register(L"buttonX_24"  , L"/7802");
	// TextureAsset::Register(L"buttonY_24"  , L"/7803");
	TextureAsset::Register(L"buttonLB_24", L"/7810");
	TextureAsset::Register(L"buttonRB_24", L"/7811");
	TextureAsset::Register(L"buttonLT_24", L"/7812");
	TextureAsset::Register(L"buttonRT_24", L"/7813");
	TextureAsset::Register(L"stick_24"   , L"/7820");
	TextureAsset::Register(L"cross_24"   , L"/7821");
	TextureAsset::Register(L"buttonA_64" , L"/7900");
	TextureAsset::Register(L"buttonB_64" , L"/7901");
	// TextureAsset::Register(L"buttonX_64"  , L"/7902");
	// TextureAsset::Register(L"buttonY_64"  , L"/7903");
	TextureAsset::Register(L"buttonLB_64", L"/7910");
	TextureAsset::Register(L"buttonRB_64", L"/7911");
	// TextureAsset::Register(L"buttonLT_64" , L"/7912");
	// TextureAsset::Register(L"buttonRT_64" , L"/7913");
	TextureAsset::Register(L"stick_64"   , L"/7920");
	// TextureAsset::Register(L"cross_64"    , L"/7921");

	SoundAsset::Register(L"BGM"    , L"/9100");
	SoundAsset::Register(L"click1" , L"/9200");
	SoundAsset::Register(L"click2" , L"/9201");
	SoundAsset::Register(L"cursor1", L"/9210");
	SoundAsset::Register(L"move1"  , L"/9220");

	FontManager::Register(L"/6000");
	FontManager::Register(L"/6010");
	FontManager::Register(L"/6020");
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

	SoundAsset(L"BGM").setLoop(true);
	SoundAsset(L"BGM").setVolume(Config::MASTER_VOLUME * Config::BGM_VOLUME);
	SoundAsset(L"BGM").play();

	while (System::Update()){
		manager.updateAndDraw();
		Debug::DebugModeWarning();
		Utils::ChangeFullScreen();
	}
}
