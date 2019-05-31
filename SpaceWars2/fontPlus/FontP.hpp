//----------------------------------------------------------------------------------------
//
//	FontPlus for Siv3D
//
//	Copyright(c) 2019 subaru2003
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this softwareand associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//
//	The above copyright noticeand this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//
//----------------------------------------------------------------------------------------

# pragma once
# include <Siv3D.hpp> // Siv3D August 2016 v2

namespace s3d {

	namespace Arg {
		enum Args {
			topLeft,
			topRight,
			bottomLeft,
			bottomRight,
			topCenter,
			bottomCenter,
			leftCenter,
			rightCenter,
			center,
		};
	}


	class DrawableStringP : public DrawableString {

	public:

		DrawableStringP(const Font& font, String&& text) : DrawableString(font, text) {}
		DrawableStringP(const DrawableString& drawableString) : DrawableString(drawableString) {}
		DrawableStringP(const Font& font, const String& text) : DrawableString(font, text) {}

		/// <summary>
		/// 基準位置を指定してテキストを描画します。
		/// </summary>
		/// <param name="arg">
		/// 基準位置
		/// </param>
		/// <param name="pos">
		/// 座標
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <param name="lineHeight">
		/// 行間のスケール
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw (
			Arg::Args arg = Arg::topLeft, 
			Vec2 pos = { 0.0, 0.0 }, 
			ColorF color = Palette::White, 
			double lineHeight = 1.0
		) const;

		/// <summary>
		/// テキストを描画します。
		/// </summary>
		/// <param name="pos">
		/// 座標
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <param name="lineHeight">
		/// 行間のスケール
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw (
			Vec2 pos = { 0.0, 0.0 }, 
			ColorF color = Palette::White, 
			double lineHeight = 1.0
		) const {
			return DrawableString::draw(pos, color, lineHeight);
		}
	};


	class FontP : public Font {

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		FontP() : Font() {}

		/// <summary>
		/// フォントを作成します。
		/// </summary>
		/// <param name="size">
		/// フォントのサイズ
		/// </param>
		/// <param name="name">
		/// フォント名
		/// </param>
		/// <param name="style">
		/// フォントのスタイル
		/// </param>
		explicit FontP (
			int32 size, 
			const String& name = Typeface::Default, 
			FontStyle style = FontStyle::Regular
		) : Font(size, name, style) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~FontP() = default;
		
		/// <summary>
		/// 基準位置を指定してテキストを描画します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <param name="arg">
		/// 基準位置
		/// </param>
		/// <param name="pos">
		/// 座標
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <param name="lineHeight">
		/// 行間のスケール
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw (
			const String& text, 
			Arg::Args arg = Arg::topLeft, 
			Vec2 pos = { 0.0, 0.0 }, 
			ColorF color = Palette::White, 
			double lineHeight = 1.0
		) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		DrawableStringP operator()(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="args">
		/// 文字列に変換するデータ
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		template <class ... Args>
		inline DrawableStringP operator()(const Args& ... args) const {
			return DrawableStringP(*this, Format(args...));
		}

		operator Font() const;
	};

}
