# pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	class Axis::CAxis
	{

	public:

		virtual operator double() const = 0;
	};

	class Axis::CKeyboardAxis : public Axis::CAxis
	{

	private:

		Key m_positive;

		Key m_negative;

	public:

		CKeyboardAxis() = default;

		CKeyboardAxis(Key positive, Key negative) :
			m_positive(positive),
			m_negative(negative) {}

		operator double() const override
		{
			return (m_positive.pressed ? 1.0 : 0.0) + (m_negative.pressed ? -1.0 : 0.0);
		};
	};

	class Axis::CGamepadAxis : public Axis::CAxis
	{

	private:

		Gamepad m_gamepad;

		std::function<double()> m_axis;

		void setAxis(GamepadAxis axis)
		{
			switch (axis)
			{
			case GamepadAxis::X:
				m_axis = std::bind(std::mem_fn(&Gamepad::_get_x), &m_gamepad);
				return;

			case GamepadAxis::Y:
				m_axis = std::bind(std::mem_fn(&Gamepad::_get_y), &m_gamepad);
				return;

			case GamepadAxis::Z:
				m_axis = std::bind(std::mem_fn(&Gamepad::_get_z), &m_gamepad);
				return;

			case GamepadAxis::R:
				m_axis = std::bind(std::mem_fn(&Gamepad::_get_r), &m_gamepad);
				return;

			case GamepadAxis::U:
				m_axis = std::bind(std::mem_fn(&Gamepad::_get_u), &m_gamepad);
				return;

			case GamepadAxis::V:
				m_axis = std::bind(std::mem_fn(&Gamepad::_get_v), &m_gamepad);
				return;

			default:
				break;
			}
		}

	public:

		CGamepadAxis() :
			m_gamepad(0) {};

		CGamepadAxis(uint32 userIndex, GamepadAxis axis) :
			m_gamepad(userIndex)
		{
			setAxis(axis);
		}

		CGamepadAxis(const Gamepad& gamepad, GamepadAxis axis) :
			m_gamepad(gamepad)
		{
			setAxis(axis);
		}

		operator double() const override
		{
			return m_axis();
		};
	};

	class Axis::CXInputAxis : public Axis::CAxis
	{

	private:

		XInput m_xinput;

		std::function<double()> m_axis;

		void setAxis(XInputAxis axis)
		{
			switch (axis)
			{
			case XInputAxis::LeftThumbX:
				m_axis = std::bind(std::mem_fn(&XInput::_get_leftThumbX), &m_xinput);
				return;

			case XInputAxis::LeftThumbY:
				m_axis = std::bind(std::mem_fn(&XInput::_get_leftThumbY), &m_xinput);
				return;

			case XInputAxis::RightThumbX:
				m_axis = std::bind(std::mem_fn(&XInput::_get_rightThumbX), &m_xinput);
				return;

			case XInputAxis::RightThumbY:
				m_axis = std::bind(std::mem_fn(&XInput::_get_rightThumbY), &m_xinput);
				return;

			default:
				break;
			}
		}

	public:

		CXInputAxis() :
			m_xinput(0) {};

		CXInputAxis(uint32 userIndex, XInputAxis axis) :
			m_xinput(userIndex)
		{
			setAxis(axis);
		}

		CXInputAxis(const XInput& xinput, XInputAxis axis) :
			m_xinput(xinput)
		{
			setAxis(axis);
		}

		operator double() const override
		{
			return m_axis();
		};
	};
}