#pragma once
#include <Siv3D.hpp>


namespace Config {
	// version
	const String VERSION	   = L"1.2_d";
	const int	 VER_NUM	   = 19061609;

	// タイトル
	const String TITLE		   = L"SpaceWars 2";

	// サイズ
	const int32  WIDTH		   = 1280;
	const int32  HEIGHT		   = 720;

	//各種音量
	const double MASTER_VOLUME = 1.0;
	const double EFFECT_VOLUME = 0.5;
	const double    BGM_VOLUME = 0.6;
	const double CURSOR_VOLUME = 0.5;

	// 背景色
	const String BACKGROUND	   = L"#ffffff";
}
