#include "CommonData.hpp"

namespace Data {
	Player LPlayer;
	Player RPlayer;

	KeyRepeat KeyEnter	 = KeyRepeat(L"KeyEnter");
	KeyRepeat KeyBack	 = KeyRepeat(L"KeyBack");
	KeyRepeat LKeyBack	 = KeyRepeat(true,  L"KeyBack");
	KeyRepeat RKeyBack	 = KeyRepeat(false, L"KeyBack");
	KeyRepeat LKeySelect = KeyRepeat(true,  L"KeySelect");
	KeyRepeat RKeySelect = KeyRepeat(false, L"KeySelect");
	KeyRepeat LKeyCancel = KeyRepeat(true,  L"KeyCancel");
	KeyRepeat RKeyCancel = KeyRepeat(false, L"KeyCancel");
	KeyRepeat KeyUp		 = KeyRepeat(L"KeyUp");
	KeyRepeat KeyLeft	 = KeyRepeat(L"KeyLeft");
	KeyRepeat KeyDown	 = KeyRepeat(L"KeyDown");
	KeyRepeat KeyRight	 = KeyRepeat(L"KeyRight");
	KeyRepeat KeySelectUp = KeyRepeat(L"KeySelectUp");
	KeyRepeat KeySelectDown = KeyRepeat(L"KeySelectDown");
}
