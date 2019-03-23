# pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// Gamepadの軸の種類
	/// </summary>
	enum class GamepadAxis
	{
		X, Y, Z, R, U, V
	};

	/// <summary>
	/// XInputの軸の種類
	/// </summary>
	enum class XInputAxis
	{
		LeftThumbX, LeftThumbY, RightThumbX, RightThumbY
	};

	/// <summary>
	/// 入力デバイスの軸の値
	/// </summary>
	/// <remarks>
	/// 入力デバイスの軸の値を [0.0-1.0] を示します。
	/// </remarks>
	class Axis
	{

	private:

		class CAxis;
		class CKeyboardAxis;
		class CGamepadAxis;
		class CXInputAxis;

		std::shared_ptr<CAxis> pAxis;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Axis();

		/// <summary>
		/// キー2つを軸として扱います。
		/// </summary>
		/// <param name="positive">
		/// 軸の正の方向のキー
		/// </param>
		/// <param name="negative">
		/// 軸の負の方向のキー
		/// </param>
		Axis(Key positive, Key negative);

		/// <summary>
		/// ゲームパッドの軸
		/// </summary>
		/// <param name="userIndex">
		/// 取得するゲームパッドのインデックス
		/// </param>
		/// <param name="axis">
		/// 取得する軸の種類
		/// </param>
		Axis(uint32 userIndex, GamepadAxis axis);

		/// <summary>
		/// ゲームパッドの軸
		/// </summary>
		/// <param name="gamepad">
		/// 取得するゲームパッド
		/// </param>
		/// <param name="axis">
		/// 取得する軸の種類
		/// </param>
		Axis(const Gamepad& gamepad, GamepadAxis axis);

		/// <summary>
		/// XInput 対応コントローラの軸
		/// </summary>
		/// <param name="userIndex">
		/// 取得するXInput 対応コントローラのインデックス
		/// </param>
		/// <param name="axis">
		/// 取得するXInput 対応コントローラの軸の種類
		/// </param>
		Axis(uint32 userIndex, XInputAxis axis);

		/// <summary>
		/// XInput 対応コントローラの軸
		/// </summary>
		/// <param name="xinput">
		/// 取得するXInput 対応コントローラ
		/// </param>
		/// <param name="axis">
		/// 取得するXInput 対応コントローラの軸の種類
		/// </param>
		Axis(const XInput& xinput, XInputAxis axis);

		/// <summary>
		/// 軸の値 [-1.0, 1.0] を示します。
		/// </summary>
		operator double () const;
	};

	/// <summary>
	/// 複数の入力デバイスの軸の値
	/// </summary>
	/// <remarks>
	/// 複数の入力がある場合、先に登録した方が優先。
	/// </remarks>
	class AxisCombination
	{
	private:

		Array<Axis> m_axes;

		template <typename Type, typename ... Args>
		void append(const Type& axis, const Args& ... args)
		{
			append(axis);
			append(args...);
		}

		void append();

		void append(Axis axis);

		void append(const AxisCombination& axes);

	public:

		template <typename ... Args>
		AxisCombination(const Args& ... args)
		{
			append(args...);
		}

		template <typename Type>
		AxisCombination& operator |= (const Type& axis)
		{
			append(axis);
			return *this;
		}

		/// <summary>
		/// 軸の値 [-1.0, 1.0] を示します。
		/// </summary>
		operator double() const;
	};

	inline AxisCombination operator | (Axis axis1, Axis axis2)
	{
		return AxisCombination(axis1, axis2);
	}

	inline AxisCombination operator | (const AxisCombination& axis1, Axis axis2)
	{
		return AxisCombination(axis1, axis2);
	}

	inline AxisCombination operator | (Axis axis1, const AxisCombination& axis2)
	{
		return AxisCombination(axis1, axis2);
	}

	inline AxisCombination operator | (const AxisCombination& axis1, const AxisCombination& axis2)
	{
		return AxisCombination(axis1, axis2);
	}
}