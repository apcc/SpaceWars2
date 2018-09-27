# include <Siv3D.hpp>
//# include "define.h"
//# include "function.cpp"

#include"config.h"
#include"CommonData.h"
// Scenes
#include"Opening.h"
#include"ControlGuidance.h"
#include"ScreenGuidance.h"
#include"Game.h"
#include"Finish.h"
#include"Ending.h"


Font CicaR32;
enum Mode gamemode;

void Main(){

	Window::SetTitle(Config::Title);
	Window::Resize(Config::Width, Config::Height);
	Graphics::SetBackground(Color(Config::Background));
	if (!FontManager::Register(L"fonts/Cica-Regular.ttf"))  return;
	//CicaR32 = Font(32, L"Cica");

	SceneManager<String,CommonData> manager;
	manager.add<Opening>(L"Opening");
	manager.add<ControlGuidance>(L"ControlGuidance");
	manager.add<ScreenGuidance>(L"ScreenGuidance");
	manager.add<Game>(L"Game");
	manager.add<Finish>(L"Finish");
	manager.add<Ending>(L"Ending");


	while (System::Update()){
		manager.updateAndDraw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
