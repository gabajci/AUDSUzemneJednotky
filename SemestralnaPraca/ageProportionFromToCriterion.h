#pragma once
#include "territorialUnit.h"
#include "criterion.h"
#include "ageCountFromToCriterion.h"

namespace criterion
{
	class AgeProportionFromToCriterion : public Criterion<double>
	{
	public:
		AgeProportionFromToCriterion(int ageFrom, int ageTo, int gender);
		~AgeProportionFromToCriterion();
		double rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
		int ageFrom_;
		int ageTo_;
		int gender_;
	};

	AgeProportionFromToCriterion::AgeProportionFromToCriterion(int ageFrom, int ageTo, int gender)
		: ageFrom_(ageFrom), ageTo_(ageTo), gender_(gender)
	{
	}

	AgeProportionFromToCriterion::~AgeProportionFromToCriterion()
	{
	}

	double AgeProportionFromToCriterion::rate(data::TerritorialUnit& unit)//pozor na indexovanie, mozno -1
	{  
		criterion::AgeCountFromToCriterion ageSum(ageFrom_,ageTo_,gender_);
		double sum = ageSum.rate(unit);

		return 100 * (sum / unit.getAge().getManInUnit());
	
	}

	inline std::wstring AgeProportionFromToCriterion::toString(data::TerritorialUnit& unit)
	{
		std::wstring genderStr;
		switch (this->gender_) {
		case 1:
			genderStr = L"muži: ";
			break;
		case 2:
			genderStr = L"6eny: ";
			break;
		case 3:
			genderStr = L"muži + ženy: ";
			break;
		default:
			break;
		}
		return L"Vek podiel - " + genderStr + L" od "+ std::to_wstring(this->ageFrom_) + 
			L" do " + std::to_wstring(this->ageTo_) +  L" = "
			+ std::to_wstring(rate(unit)) + L'.\n';
	}

}


