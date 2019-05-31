#include "Asset.hpp"

#define RETURN_FONTP FontP(FontAsset(name).size(), FontAsset(name).name(), FontAsset(name).style())

using std::make_pair;

Array<SmartUISize> SmartUI::size = { S12, S28, S32 };
Array<SmartBSize>  SmartB::	size = { Sb12, Sb32 };
Array<CicaRSize>   CicaR::	size = { C12, C18, C32 };
Array<LettersSize> Letters::size = { L7, L10, L12, L18, L32 };
std::map<String, FontP> FontPAsset::fonts = {};

bool SmartUI::Register() {
	for (SmartUISize s : size) {
		const String name = L"Smart" + Format(s);
		FontPAsset::fonts.insert(make_pair(name, FontP(s, L"03SmartFont-Proportional")));
	}
	return true;
}

FontP SmartUI::Get(SmartUISize _size) {
	const String name = L"Smart" + Format(_size);
	return FontPAsset::fonts[name];
}


bool SmartB::Register() {
	for (SmartBSize s : size) {
		const String name = L"SmartB" + Format(s);
		FontPAsset::fonts.insert(make_pair(name, FontP(s, L"03SmartFont-Proportional", FontStyle::Bold)));
	}
	return true;
}

FontP SmartB::Get(SmartBSize _size) {
	const String name = L"SmartB" + Format(_size);
	return FontPAsset::fonts[name];
}


bool CicaR::Register() {
	for (CicaRSize s : size) {
		const String name = L"Cica" + Format(s);
		FontPAsset::fonts.insert(make_pair(name, FontP(s, L"Cica")));
	}
	return true;
}

FontP CicaR::Get(CicaRSize _size) {
	const String name = L"Cica" + Format(_size);
	return FontPAsset::fonts[name];
}


bool Letters::Register() {
	for (LettersSize s : size) {
		const String name = L"Letters" + Format(s);
		FontPAsset::fonts.insert(make_pair(name, FontP(s, L"Letters Laughing")));
	}
	return true;
}

FontP Letters::Get(LettersSize _size) {
	const String name = L"Letters" + Format(_size);
	return FontPAsset::fonts[name];
}
