#include <Siv3D.hpp>
#include "./Debug.hpp"
#include "Asset.hpp"

String Debug::InputFnKey(){
	String sceneName = L"";

	if (Input::KeyF1.clicked) sceneName = L"Title";
	if (Input::KeyF2.clicked) sceneName = L"ControlGuidance";
	if (Input::KeyF3.clicked) sceneName = L"ScreenGuidance";
	if (Input::KeyF4.clicked) sceneName = L"SkillSelect";
	if (Input::KeyF5.clicked) sceneName = L"Game";
	if (Input::KeyF6.clicked) sceneName = L"Game";
	if (Input::KeyF7.clicked) sceneName = L"Game";

	return sceneName;
}

void Debug::DebugModeWarning() {
#	ifdef _DEBUG
		CicaR::Get(C12)(L"Debug Mode").draw(Arg::topRight, { 1275, 5 }, Color(L"#f22"));
#	endif
}
