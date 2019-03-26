# include "Axis.hpp"
# include "CAxis.hpp"

using namespace asc;

Axis::Axis() = default;

Axis::Axis(Key positive, Key negative) :
	pAxis(std::make_shared<CKeyboardAxis>(positive, negative)) {}

Axis::Axis(uint32 userIndex, GamepadAxis axis) :
	pAxis(std::make_shared<CGamepadAxis>(userIndex, axis)) {}

Axis::Axis(const Gamepad& gamepad, GamepadAxis axis) :
	pAxis(std::make_shared<CGamepadAxis>(gamepad, axis)) {}

Axis::Axis(uint32 userIndex, XInputAxis axis) :
	pAxis(std::make_shared<CXInputAxis>(userIndex, axis)) {}

Axis::Axis(const XInput& xinput, XInputAxis axis) :
	pAxis(std::make_shared<CXInputAxis>(xinput, axis)) {}

Axis::operator double() const
{
	return *pAxis;
}

void AxisCombination::append() {}

void AxisCombination::append(Axis axis)
{
	m_axes.push_back(axis);
}

void AxisCombination::append(const AxisCombination& axes)
{
	for (auto axis : axes.m_axes)
	{
		m_axes.push_back(axis);
	}
}

AxisCombination::operator double() const
{
	for (auto axis : m_axes)
	{
		if (Abs(static_cast<double>(axis)) > 0.0)
		{
			return axis;
		}
	}

	return 0.0;
}