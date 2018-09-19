# include <Siv3D.hpp>
//# include "define.h"
//# include "function.cpp"


#include"CommonData.h"
// Scenes
#include"Opening.h"
#include"Game.h"


Font CicaR32;
enum Mode gamemode;

void Main(){
	

	Window::SetTitle(L"SPACE WARS 2");
	Window::Resize(1280, 800);
	Graphics::SetBackground(Color(L"#ffffff"));
	if (!FontManager::Register(L"fonts/Cica-Regular.ttf"))  return;
	//CicaR32 = Font(32, L"Cica");

	SceneManager<String,CommonData> manager;
	manager.add<Opening>(L"Opening");
	manager.add<Game>(L"Game");


	while (System::Update()){
		manager.updateAndDraw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
