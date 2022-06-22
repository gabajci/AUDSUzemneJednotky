#pragma once
#include "territorialUnit.h"
#include "criterion.h"

#define CHILDAGESTART 0
#define CHILDAGEEND 15
#define PRODAGEEND 65
#define AGEEND 100

namespace criterion
{
	class AgeGroupProportionCriterion : public Criterion<double>
	{
	public:
		AgeGroupProportionCriterion(int evs);
		~AgeGroupProportionCriterion();
		double rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
		int evs_;
	};

	AgeGroupProportionCriterion::AgeGroupProportionCriterion(int evs)
		: evs_(evs)
	{
	}

	AgeGroupProportionCriterion::~AgeGroupProportionCriterion()
	{
	}

	double AgeGroupProportionCriterion::rate(data::TerritorialUnit& unit)
	{
		double manInUnit = unit.getAge().getManInUnit();
		if (evs_ == 1) {

			double manCount = 0;
			for (int i = CHILDAGESTART; i < CHILDAGEEND;i++) { //TOTO OVERIT
				manCount += unit.getAge().getManAge(i);
				manCount += unit.getAge().getWomanAge(i);
			}
			return 100 * (manCount / manInUnit);
		}
		else if (evs_ == 2) {

			double manCount = 0;
			for (int i = CHILDAGEEND; i < PRODAGEEND; i++) { //TOTO OVERIT
				manCount += unit.getAge().getManAge(i);
				manCount += unit.getAge().getWomanAge(i);
			}
			return 100 * (manCount / manInUnit);
		}
		else {

			double manCount = 0;
			for (int i = PRODAGEEND; i < AGEEND; i++) { //TOTO OVERIT
				manCount += unit.getAge().getManAge(i);
				manCount += unit.getAge().getWomanAge(i);
			}
			return 100 * (manCount / manInUnit);
		}
	}

	inline std::wstring AgeGroupProportionCriterion::toString(data::TerritorialUnit& unit)
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
		return L"Veková skupina podiel -" + evsStr + std::to_wstring(rate(unit)) + L'.\n';
	}

}


