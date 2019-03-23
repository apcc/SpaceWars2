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
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		Input();

		/// <summary>
		/// ���͂��L�����ǂ����������܂��B
		/// </summary>
		__declspec(property(get = _get_enabled, put = _put_enabled)) bool enabled;

		/// <summary>
		/// �w�肵���{�^���̏�Ԃ�Ԃ��܂��B
		/// </summary>
		/// <param name="name">
		/// �o�^�����{�^���̖��O
		/// </param>
		/// <returns>
		/// �{�^���̏��
		/// </returns>
		KeyCombination button(const String& name) const;

		/// <summary>
		/// �w�肵�����̏�Ԃ�Ԃ��܂��B
		/// </summary>
		/// <param name="name">
		/// �o�^�����{�^���̖��O
		/// </param>
		/// <returns>
		/// ���̒l [-1.0, 1.0]
		/// </returns>
		double axis(const String& name) const;

		/// <summary>
		/// 2�̎����� Vec2 ���쐬���܂��B
		/// </summary>
		/// <param name="xName">
		/// X���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <param name="yName">
		/// Y���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <returns>
		/// { xName, yName } �� Vec2
		/// </returns>
		Vec2 vec2(const String& xName, const String& yName) const;

		/// <summary>
		/// 2�̎����琳�K�����ꂽ Vec2 ���쐬���܂��B
		/// </summary>
		/// <param name="xName">
		/// X���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <param name="yName">
		/// Y���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <returns>
		/// { xName, yName } �̐��K�����ꂽ Vec2
		/// </returns>
		/// <remarks>
		/// ��x�N�g���̏ꍇ�͗�x�N�g����Ԃ��܂��B
		/// </remarks>
		Vec2 vec2Normalized(const String& xName, const String& yName) const;

		/// <summary>
		/// 2�̎���������� [0, 3] �ŕԂ��܂��B
		/// </summary>
		/// <param name="xName">
		/// X���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <param name="yName">
		/// Y���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <param name="threshold">
		/// �L���ɂ���l�̍Œ�l
		/// </param>
		/// <returns>
		/// [0, 3] �ŕ\�����ꂽ�����Bthreshold�ȉ��̏ꍇ�� none
		/// </returns>
		Optional<uint32> as4Direction(const String& xName, const String& yName, double threshold = 0.2);

		/// <summary>
		/// 2�̎���������� [0, 7] �ŕԂ��܂��B
		/// </summary>
		/// <param name="xName">
		/// X���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <param name="yName">
		/// Y���ɂ���o�^�����{�^���̖��O
		/// </param>
		/// <param name="threshold">
		/// �L���ɂ���l�̍Œ�l
		/// </param>
		/// <returns>
		/// [0, 7] �ŕ\�����ꂽ�����Bthreshold�ȉ��̏ꍇ�� none
		/// </returns>
		Optional<uint32> as8Direction(const String& xName, const String& yName, double threshold = 0.2);

		/// <summary>
		/// �{�^�����o�^�ς݂����m�F���܂��B
		/// </summary>
		/// <param name="name">
		/// �o�^�����{�^���̖��O
		/// </param>
		/// <returns>
		/// �{�^�����o�^����Ă���� true
		/// </returns>
		bool hasButton(const String& name) const;

		/// <summary>
		/// �����o�^�ς݂����m�F���܂��B
		/// </summary>
		/// <param name="name">
		/// �o�^�������̖��O
		/// </param>
		/// <returns>
		/// �����o�^����Ă���� true
		/// </returns>
		bool hasAxis(const String& name) const;

		/// <summary>
		/// �{�^����o�^���܂��B
		/// </summary>
		/// <param name="name">
		/// �o�^����{�^���̖��O
		/// </param>
		/// <param name="button">
		/// �o�^����{�^��
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void addButton(const String& name, const KeyCombination& button);

		/// <summary>
		/// ����o�^���܂��B
		/// </summary>
		/// <param name="name">
		/// �o�^���鎲�̖��O
		/// </param>
		/// <param name="axis">
		/// �o�^���鎲
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void addAxis(const String& name, const AxisCombination& axis);

		/// <summary>
		/// �{�^�����폜���܂��B
		/// </summary>
		/// <param name="name">
		/// �폜����{�^���̖��O
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void eraseButton(const String& name);

		/// <summary>
		/// �����폜���܂��B
		/// </summary>
		/// <param name="name">
		/// �폜���鎲�̖��O
		/// </param>
		/// <returns>
		/// �Ȃ�
		/// </returns>
		void eraseAxis(const String& name);

		/// <summary>
		/// enabled�v���p�e�B
		/// </summary>
		bool _get_enabled() const;

		/// <summary>
		/// enabled�v���p�e�B
		/// </summary>
		void _put_enabled(bool value);
	};
}