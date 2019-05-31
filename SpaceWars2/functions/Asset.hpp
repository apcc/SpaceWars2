#pragma once
#include <Siv3D.hpp>
#include "../fontPlus/FontP.hpp"

namespace FontPAsset {
	extern std::map<String, FontP> fonts;
}

enum SmartUISize {
	S12 = 12,
	S28 = 28,
	S32 = 32
};
namespace SmartUI {
	extern Array<SmartUISize> size;
	// register all
	bool Register();
	// Returns: FontP
	FontP Get(SmartUISize _size);
}

enum SmartBSize {
	Sb12 = 12,
	Sb32 = 32
};
namespace SmartB {
	extern Array<SmartBSize> size;
	// register all
	bool Register();
	// Returns: FontP
	FontP Get(SmartBSize _size);
}

enum CicaRSize {
	C12 = 12,
	C18 = 18,
	C32 = 32
};
namespace CicaR {
	extern Array<CicaRSize> size;
	// register all
	bool Register();
	// Returns: FontP
	FontP Get(CicaRSize _size);
}

enum LettersSize {
	L7  = 7,
	L10 = 10,
	L12 = 12,
	L18 = 18,
	L32 = 32
};
namespace Letters {
	extern Array<LettersSize> size;
	// register all
	bool Register();
	// Returns: FontP
	FontP Get(LettersSize _size);
}
