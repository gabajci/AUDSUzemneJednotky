#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class AgeCountFromToCriterion : public Criterion<int> //OD DO
	{
	public:
		AgeCountFromToCriterion(int ageFrom,int ageTo, int gender);
		~AgeCountFromToCriterion();
		int rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
		int ageFrom_;
		int ageTo_;
		int gender_;
	};

	AgeCountFromToCriterion::AgeCountFromToCriterion(int ageFrom,int ageTo, int gender)
		: ageFrom_(ageFrom),ageTo_(ageTo), gender_(gender)
	{
	}

	AgeCountFromToCriterion::~AgeCountFromToCriterion()
	{
	}

	int AgeCountFromToCriterion::rate(data::TerritorialUnit& unit) 
	{
		if (gender_ == 1) { //muzi
			int count = 0;
			for (int i = ageFrom_; i < ageTo_; i++) {
				count += unit.getAge().getManAge(i);
			}
			return count;
		}
		else if (gender_ == 2) { //zeny
			int count = 0;
			for (int i = ageFrom_; i < ageTo_; i++) {
				count += unit.getAge().getWomanAge(i);
			}
			return count;
		}
		else {
			int count = 0;
			for (int i = ageFrom_; i < ageTo_; i++) {
				count += unit.getAge().getWomanAge(i);
				count += unit.getAge().getManAge(i);
			}
			return count;
		}
	}

	inline std::wstring AgeCountFromToCriterion::toString(data::TerritorialUnit& unit)
	{
		std::wstring genderStr;
		switch (this->gender_) {
		case 1:
			genderStr = L"muži: ";
			break;
		case 2:
			genderStr = L"ženy: ";
			break;
		case 3:
			genderStr = L"muži + 6eny: ";
			break;
		default:
			break;
		}
		return L"Vek poèet - " + genderStr + L"od " + std::to_wstring(this->ageFrom_) +
			L" do " + std::to_wstring(this->ageTo_) + L" = "
			+ std::to_wstring(rate(unit)) + L'.\n';
	}




}


