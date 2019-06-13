#include "SkillDescription.hpp"

std::vector<String> SkillDescript::split(String str) {
		int strstart = 0;
		std::vector<String> res;
		for (int i = 0; i < str.length; i++) {
			if (str[i] == ',') {
				res.push_back(str.substr(strstart, i - strstart));
				strstart = i + 1;
			}
		}
		res.push_back(str.substr(strstart, str.length - strstart));
		return res;
}

void SkillDescript::Memory(String str) {
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
	case 3: count++; //iconPath = str; break;
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

SkillDescript::SkillDescript(String _name, String _path, String _Descrpit, Vec4 _status) {
	name = _name;
	iconPath = _path;
	descript = _Descrpit;
	status[0] = (int)_status.w;
	status[1] = (int)_status.x;
	status[2] = (int)_status.y;
	status[3] = (int)_status.z;
}

SkillDescript::SkillDescript(String _status[PARM_COUNT]) {
	for (int i = 0; i < PARM_COUNT; i++) {
		Memory(_status[i]);
	}
}
