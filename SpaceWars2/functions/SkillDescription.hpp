#pragma once
#include <Siv3D.hpp>

class SkillDescript final {
private:

	String SKILL_TYPE[3] = { L"Main", L"Sub", L"Special" };
	enum SKILL_PARAMATER {
		TYPE,
		NAME,
		IMAGE,
		DESCRIPTION,
		STATS1,
		STATS2,
		STATS3,
		STATS4,
		PARM_COUNT
	};

	int count = 0;

	std::vector<String> split(String str);

	void Memory(String str);

public:
	SkillDescript(String _name, String _path, String _Descrpit, Vec4 _status);

	SkillDescript(String _status[PARM_COUNT]);

	SkillDescript(String _str) {
		WriteWithLine(_str);
	}

	int type = -1;
	String name = L"Test";
	String iconPath = L"pppath";
	String descript = L"AAA";
	int status[4] = { 10,10,10,10 };

	void WriteWithLine(String str) {
		std::vector<String> stats = split(str);

		for(int i=0;i<stats.size();i++){
			Memory(stats[i]);
		}
	}

	void WriteByVar(String _status[PARM_COUNT]) {
		for (int i = 0; i < PARM_COUNT; i++) {
			Memory(_status[i]);
		}
	}
};

class SkillDescriptManager final {
public:
	std::vector<SkillDescript> skillDescription[3]; // [int Skilltype][int SkillId] : string info

	/// <summary>
	/// 説明を管理するインスタンスを追加します
	/// </summary>
	/// <param name="_str">
	/// 説明文を含んだ読み込みたいcsvの1行
	/// </param>
	void AddDescript(String _str) {
		SkillDescript data(_str);
		skillDescription[data.type].emplace_back(data);
	}

};
