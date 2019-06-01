#pragma once
#include "Include.hpp"

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

	std::vector<String> split(String str) {
		int strstart = 0;
		std::vector<String> res;
		for (int i = 0; i < str.length; i++) {
			if (str[i] == ',') {
				res.push_back(str.substr(strstart, i-strstart));
				strstart = i+1;
			}
		}
		res.push_back(str.substr(strstart, str.length - strstart));
		return res;
	}

	void Memory(String str) {
		switch (count) {
		case 0:
			for (int i = 0; i < 3; i++) {
				if (str == SKILL_TYPE[i]) type = i;
			}
			if (type == -1)
				LOG_ERROR(L"SkillDescript: WriteError: un-expected type", str);
			break;

		case 1: name = str; break;
		case 2: descript = str; break;
		case 3: iconPath = str; break;
		default:
			if (count >= PARM_COUNT) {
				LOG_ERROR(L"SkillDescrpit: Write Eror: out of range in ", name);
			}
			else {
				status[count - 4] = Parse<int>(str);
			}
			break;
		}
		count++;
	}

public:
	SkillDescript(String _name, String _path, String _Descrpit, Vec4 _status) {
		name = _name;
		iconPath = _path;
		descript = _Descrpit;
		status[0] = (int)_status.w;
		status[1] = (int)_status.x;
		status[2] = (int)_status.y;
		status[3] = (int)_status.z;
	}

	SkillDescript(String _status[PARM_COUNT]) {
		for (int i = 0; i < PARM_COUNT; i++) {
			Memory(_status[i]);
		}
	}

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

	void AddDescript(String _str) {
		SkillDescript data(_str);
		skillDescription[data.type].emplace_back(data);
	}

};

class SkillSelect final : public SceneManager<String, CommonData>::Scene {
private:
	static bool isLoaded;
	int nextStageTime = 0;
	bool LContinue = false;
	bool RContinue = false;
	double LAlpha[3] = { 0.5, 0.5, 0.5 };
	double RAlpha[3] = { 0.5, 0.5, 0.5 };

	SkillDescriptManager skillSelectManager;
public:
	void init() override;
	void update() override;
	void draw() const override;
};
