#pragma once

#define CHILDAGESTART 0
#define CHILDAGEEND 15
#define PRODAGEEND 65
#define AGEEND 100

#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class AgeGroupCountCriterion : public Criterion<int>
	{
	public:
		AgeGroupCountCriterion(int evs);
		~AgeGroupCountCriterion();
		int rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
		int evs_;
	};

	AgeGroupCountCriterion::AgeGroupCountCriterion(int evs)
		: evs_(evs)
	{
	}

	AgeGroupCountCriterion::~AgeGroupCountCriterion()
	{
	}

	int AgeGroupCountCriterion::rate(data::TerritorialUnit& unit)
	{
		if (evs_ == 1) {

			int manCount = 0;
			for (int i = CHILDAGESTART; i < CHILDAGEEND; i++) { //TOTO OVERIT
				manCount += unit.getAge().getManAge(i);
				manCount += unit.getAge().getWomanAge(i);
			}
			return manCount;
		}
		else if (evs_ == 2) {

			int manCount = 0;
			for (int i = CHILDAGEEND; i < PRODAGEEND; i++) { //TOTO OVERIT
				manCount += unit.getAge().getManAge(i);
				manCount += unit.getAge().getWomanAge(i);
			}
			return manCount;
		}
		else {

			int manCount = 0;
			for (int i = PRODAGEEND; i < AGEEND; i++) { //TOTO OVERIT
				manCount += unit.getAge().getManAge(i);
				manCount += unit.getAge().getWomanAge(i);
			}
			return manCount;
		}
	}

	inline std::wstring AgeGroupCountCriterion::toString(data::TerritorialUnit& unit)
	{
		std::wstring evsStr;
		switch (this->evs_) {
		case 1:
			evsStr = L"predproduktívny: ";
			break;
		case 2:
			evsStr = L"produktívny: ";
			break;
		case 3:
			evsStr = L"poproduktívny: ";
			break;
		default:
			break;
		}
		return L"Veková skupina poèet - " + evsStr + std::to_wstring(rate(unit)) + L'.\n';
	}

}


