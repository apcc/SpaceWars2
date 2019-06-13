#pragma once
#include <Siv3D.hpp>


namespace Config {
	// version
	const String VERSION	= L"0.8_d";
	const int	 VER_NUM	= 19053123;

	// タイトル
	const String TITLE		= L"SpaceWars 2";

	// サイズ
	const int32  WIDTH		= 1280;
	const int32  HEIGHT		= 720;

	//各種音量
	const double masterVolume = 1.0;
	const double effectSoundVolume = 0.5;
	const double bgmVolume = 1.0;
	const double cursolSoundVolume = 0.3;

	// 背景色
	const String BACKGROUND	= L"#ffffff";
}
