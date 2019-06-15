#include <Siv3D.hpp>
#include "./Utils.hpp"

void Utils::ChangeFullScreen() {
	const Size size(1280, 720);
	if (Input::KeyF11.clicked)
		Window::SetFullscreen(!Window::IsFullSceen(), size);
}
