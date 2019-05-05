#pragma once
#include <Siv3D.hpp>


#define CENTER (int)(Config::WIDTH / 2.0)

namespace Config {

	// タイトル
	const String TITLE		= L"SPACE WARS 2";

	// サイズ
	const int32  WIDTH		= 1280;
	const int32  HEIGHT		= 720;

	// 背景色
	const String BACKGROUND	= L"#ffffff";
}
