# include <unordered_map>
# include <Siv3D.hpp>
# include "Axis.hpp"
# include "../Input.hpp"

namespace asc
{
	class Input::CInput
	{

	public:

		bool m_enabled;

		std::unordered_map<String, KeyCombination> m_buttons;

		std::unordered_map<String, AxisCombination> m_axes;

		CInput() : m_enabled(true) {};
	};
}

asc::Input::Input() : pInput(std::make_shared<CInput>()) {};

KeyCombination asc::Input::button(const String& name) const
{
	if (!pInput->m_enabled)
		return KeyCombination();

	return pInput->m_buttons.at(name);
}

double asc::Input::axis(const String& name) const
{
	if (!pInput->m_enabled)
		return 0.0;

	return pInput->m_axes.at(name);
}

Vec2 asc::Input::vec2(const String& xName, const String& yName) const
{
	return Vec2{ axis(xName), axis(yName) };
}

Vec2 asc::Input::vec2Normalized(const String& xName, const String& yName) const
{
	const auto vector2D = vec2(xName, yName);

	if (vector2D == Vec2::Zero)
		return vector2D;

	return vector2D.normalized();
}

Optional<uint32> asc::Input::as4Direction(const String& xName, const String& yName, double threshold)
{
	const Circular circular = Vec2{ axis(xName), -axis(yName) };

	if (circular.r < threshold)
		return none;

	const double deg = Degrees(circular.theta);

	if (deg <= -135.0)
		return 2u;
	else if (deg <= -45.0)
		return 3u;
	else if (deg <= 45.0)
		return 0u;
	else if (deg <= 135.0)
		return 1u;
	else
		return 2u;
}

Optional<uint32> asc::Input::as8Direction(const String& xName, const String& yName, double threshold)
{
	const Circular circular = Vec2{ axis(xName), -axis(yName) };

	if (circular.r < threshold)
		return none;

	const double deg = Degrees(circular.theta);

	if (deg <= -157.5)
		return 4u;
	else if (deg <= -112.5)
		return 5u;
	else if (deg <= -67.5)
		return 6u;
	else if (deg <= -22.5)
		return 7u;
	else if (deg <= 22.5)
		return 0u;
	else if (deg <= 67.5)
		return 1u;
	else if (deg <= 112.5)
		return 2u;
	else if (deg <= 157.5)
		return 3u;
	else
		return 4u;
}

bool asc::Input::hasButton(const String& name) const
{
	return pInput->m_buttons.find(name) != pInput->m_buttons.end();
}

bool asc::Input::hasAxis(const String& name) const
{
	return pInput->m_axes.find(name) != pInput->m_axes.end();
}

void asc::Input::addButton(const String& name, const KeyCombination& button)
{
	pInput->m_buttons[name] = button;
}

void asc::Input::addAxis(const String& name, const AxisCombination& axis)
{
	pInput->m_axes[name] = axis;
}

void asc::Input::eraseButton(const String& name)
{
	pInput->m_buttons.erase(name);
}

void asc::Input::eraseAxis(const String& name)
{
	pInput->m_axes.erase(name);
}

bool asc::Input::_get_enabled() const { return pInput->m_enabled; }

void asc::Input::_put_enabled(bool value) { pInput->m_enabled = value; }
