#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class AgeCountCriterion : public Criterion<int>
	{
	public:
		AgeCountCriterion(int age, criterion::Gender gender);
		~AgeCountCriterion();
		int rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
		int age_;
		criterion::Gender gender_;
	};

	AgeCountCriterion::AgeCountCriterion(int age, criterion::Gender gender) 
		: age_(age), gender_(gender)
	{
	}

	AgeCountCriterion::~AgeCountCriterion()
	{
	}

	int AgeCountCriterion::rate(data::TerritorialUnit& unit)
	{
		if (gender_ == man) {
			return unit.getAge().getManAge(this->age_);
		}
		else if (gender_ == woman) {

			return unit.getAge().getWomanAge(this->age_);
		}
		else {
			return unit.getAge().getWomanAge(this->age_) + unit.getAge().getManAge(this->age_);
		}
	}

	inline std::wstring AgeCountCriterion::toString(data::TerritorialUnit& unit)
	{
		return std::wstring();
	}

	


}


