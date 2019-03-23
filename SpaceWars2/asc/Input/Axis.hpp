# pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// Gamepad�̎��̎��
	/// </summary>
	enum class GamepadAxis
	{
		X, Y, Z, R, U, V
	};

	/// <summary>
	/// XInput�̎��̎��
	/// </summary>
	enum class XInputAxis
	{
		LeftThumbX, LeftThumbY, RightThumbX, RightThumbY
	};

	/// <summary>
	/// ���̓f�o�C�X�̎��̒l
	/// </summary>
	/// <remarks>
	/// ���̓f�o�C�X�̎��̒l�� [0.0-1.0] �������܂��B
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
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		Axis();

		/// <summary>
		/// �L�[2�����Ƃ��Ĉ����܂��B
		/// </summary>
		/// <param name="positive">
		/// ���̐��̕����̃L�[
		/// </param>
		/// <param name="negative">
		/// ���̕��̕����̃L�[
		/// </param>
		Axis(Key positive, Key negative);

		/// <summary>
		/// �Q�[���p�b�h�̎�
		/// </summary>
		/// <param name="userIndex">
		/// �擾����Q�[���p�b�h�̃C���f�b�N�X
		/// </param>
		/// <param name="axis">
		/// �擾���鎲�̎��
		/// </param>
		Axis(uint32 userIndex, GamepadAxis axis);

		/// <summary>
		/// �Q�[���p�b�h�̎�
		/// </summary>
		/// <param name="gamepad">
		/// �擾����Q�[���p�b�h
		/// </param>
		/// <param name="axis">
		/// �擾���鎲�̎��
		/// </param>
		Axis(const Gamepad& gamepad, GamepadAxis axis);

		/// <summary>
		/// XInput �Ή��R���g���[���̎�
		/// </summary>
		/// <param name="userIndex">
		/// �擾����XInput �Ή��R���g���[���̃C���f�b�N�X
		/// </param>
		/// <param name="axis">
		/// �擾����XInput �Ή��R���g���[���̎��̎��
		/// </param>
		Axis(uint32 userIndex, XInputAxis axis);

		/// <summary>
		/// XInput �Ή��R���g���[���̎�
		/// </summary>
		/// <param name="xinput">
		/// �擾����XInput �Ή��R���g���[��
		/// </param>
		/// <param name="axis">
		/// �擾����XInput �Ή��R���g���[���̎��̎��
		/// </param>
		Axis(const XInput& xinput, XInputAxis axis);

		/// <summary>
		/// ���̒l [-1.0, 1.0] �������܂��B
		/// </summary>
		operator double () const;
	};

	/// <summary>
	/// �����̓��̓f�o�C�X�̎��̒l
	/// </summary>
	/// <remarks>
	/// �����̓��͂�����ꍇ�A��ɓo�^���������D��B
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
		/// ���̒l [-1.0, 1.0] �������܂��B
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