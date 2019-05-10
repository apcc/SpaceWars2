#include "Asset.hpp"

bool SmartUI::Register() {
	bool result = true;
	for (SmartUISize s : { S12, S28, S32 }) {
		const String name = L"Smart" + Format(s);
		if (!FontAsset::Register(name, s, L"03SmartFont-Proportional"))
			result = false;
	}
	return result;
}

Font SmartUI::GetFont(SmartUISize _size) {
	const String name = L"Smart" + Format(_size);
	if (!FontAsset::IsRegistered(name)) {
		LOG_ERROR(L"SmartFontUIを参照中に、未登録のフォントサイズが指定されました: ", _size, L" at Fonts::SmartUI::GetFont(SmartUISize _size)");
		return Font();
	}
	return FontAsset(name);
}


bool SmartB::Register() {
	bool result = true;
	for (SmartBSize s : { Sb12 }) {
		const String name = L"SmartB" + Format(s);
		if (!FontAsset::Register(name, s, L"03SmartFont-Proportional", FontStyle::Bold))
			result = false;
	}
	return result;
}

Font SmartB::GetFont(SmartBSize _size) {
	const String name = L"SmartB" + Format(_size);
	if (!FontAsset::IsRegistered(name)) {
		LOG_ERROR(L"SmartFontUIを参照中に、未登録のフォントサイズが指定されました: ", _size, L" at Fonts::SmartB::GetFont(SmartUISize _size)");
		return Font();
	}
	return FontAsset(name);
}


bool CicaR::Register() {
	bool result = true;
	for (CicaRSize s : { C12, C18, C32 }) {
		const String name = L"CicaR" + Format(s);
		if (!FontAsset::Register(name, s, L"Cica"))
			result = false;
	}
	return result;
}

Font CicaR::GetFont(CicaRSize _size) {
	const String name = L"CicaR" + Format(_size);
	if (!FontAsset::IsRegistered(name)) {
		LOG_ERROR(L"SmartFontUIを参照中に、未登録のフォントサイズが指定されました: ", _size, L" at Fonts::CicaR::GetFont(SmartUISize _size)");
		return Font();
	}
	return FontAsset(name);
}


bool Letters::Register() {
	bool result = true;
	for (LettersSize s : { L7, L10, L12, L18, L32 }) {
		const String name = L"Letters" + Format(s);
		if (!FontAsset::Register(name, s, L"Letters Laughing"))
			result = false;
	}
	return result;
}

Font Letters::GetFont(LettersSize _size) {
	const String name = L"Letters" + Format(_size);
	if (!FontAsset::IsRegistered(name)) {
		LOG_ERROR(L"SmartFontUIを参照中に、未登録のフォントサイズが指定されました: ", _size, L" at Fonts::Letters::GetFont(SmartUISize _size)");
		return Font();
	}
	return FontAsset(name);
}
