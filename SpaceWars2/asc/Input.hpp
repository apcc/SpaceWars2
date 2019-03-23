# pragma once
# include <Siv3D.hpp>
# include "./Input/Axis.hpp"

namespace asc
{
	using namespace s3d;

	class Input
	{

	private:

		class CInput;

		std::shared_ptr<CInput> pInput;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Input();

		/// <summary>
		/// 入力が有効かどうかを示します。
		/// </summary>
		__declspec(property(get = _get_enabled, put = _put_enabled)) bool enabled;

		/// <summary>
		/// 指定したボタンの状態を返します。
		/// </summary>
		/// <param name="name">
		/// 登録したボタンの名前
		/// </param>
		/// <returns>
		/// ボタンの状態
		/// </returns>
		KeyCombination button(const String& name) const;

		/// <summary>
		/// 指定した軸の状態を返します。
		/// </summary>
		/// <param name="name">
		/// 登録したボタンの名前
		/// </param>
		/// <returns>
		/// 軸の値 [-1.0, 1.0]
		/// </returns>
		double axis(const String& name) const;

		/// <summary>
		/// 2つの軸から Vec2 を作成します。
		/// </summary>
		/// <param name="xName">
		/// X軸にする登録したボタンの名前
		/// </param>
		/// <param name="yName">
		/// Y軸にする登録したボタンの名前
		/// </param>
		/// <returns>
		/// { xName, yName } の Vec2
		/// </returns>
		Vec2 vec2(const String& xName, const String& yName) const;

		/// <summary>
		/// 2つの軸から正規化された Vec2 を作成します。
		/// </summary>
		/// <param name="xName">
		/// X軸にする登録したボタンの名前
		/// </param>
		/// <param name="yName">
		/// Y軸にする登録したボタンの名前
		/// </param>
		/// <returns>
		/// { xName, yName } の正規化された Vec2
		/// </returns>
		/// <remarks>
		/// 零ベクトルの場合は零ベクトルを返します。
		/// </remarks>
		Vec2 vec2Normalized(const String& xName, const String& yName) const;

		/// <summary>
		/// 2つの軸から方向を [0, 3] で返します。
		/// </summary>
		/// <param name="xName">
		/// X軸にする登録したボタンの名前
		/// </param>
		/// <param name="yName">
		/// Y軸にする登録したボタンの名前
		/// </param>
		/// <param name="threshold">
		/// 有効にする値の最低値
		/// </param>
		/// <returns>
		/// [0, 3] で表現された方向。threshold以下の場合は none
		/// </returns>
		Optional<uint32> as4Direction(const String& xName, const String& yName, double threshold = 0.2);

		/// <summary>
		/// 2つの軸から方向を [0, 7] で返します。
		/// </summary>
		/// <param name="xName">
		/// X軸にする登録したボタンの名前
		/// </param>
		/// <param name="yName">
		/// Y軸にする登録したボタンの名前
		/// </param>
		/// <param name="threshold">
		/// 有効にする値の最低値
		/// </param>
		/// <returns>
		/// [0, 7] で表現された方向。threshold以下の場合は none
		/// </returns>
		Optional<uint32> as8Direction(const String& xName, const String& yName, double threshold = 0.2);

		/// <summary>
		/// ボタンが登録済みかを確認します。
		/// </summary>
		/// <param name="name">
		/// 登録したボタンの名前
		/// </param>
		/// <returns>
		/// ボタンが登録されていれば true
		/// </returns>
		bool hasButton(const String& name) const;

		/// <summary>
		/// 軸が登録済みかを確認します。
		/// </summary>
		/// <param name="name">
		/// 登録した軸の名前
		/// </param>
		/// <returns>
		/// 軸が登録されていれば true
		/// </returns>
		bool hasAxis(const String& name) const;

		/// <summary>
		/// ボタンを登録します。
		/// </summary>
		/// <param name="name">
		/// 登録するボタンの名前
		/// </param>
		/// <param name="button">
		/// 登録するボタン
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void addButton(const String& name, const KeyCombination& button);

		/// <summary>
		/// 軸を登録します。
		/// </summary>
		/// <param name="name">
		/// 登録する軸の名前
		/// </param>
		/// <param name="axis">
		/// 登録する軸
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void addAxis(const String& name, const AxisCombination& axis);

		/// <summary>
		/// ボタンを削除します。
		/// </summary>
		/// <param name="name">
		/// 削除するボタンの名前
		/// <returns>
		/// なし
		/// </returns>
		void eraseButton(const String& name);

		/// <summary>
		/// 軸を削除します。
		/// </summary>
		/// <param name="name">
		/// 削除する軸の名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void eraseAxis(const String& name);

		/// <summary>
		/// enabledプロパティ
		/// </summary>
		bool _get_enabled() const;

		/// <summary>
		/// enabledプロパティ
		/// </summary>
		void _put_enabled(bool value);
	};
}