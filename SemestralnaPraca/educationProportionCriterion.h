#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class EducationProportionCriterion : public Criterion<double>
	{
	public:
		EducationProportionCriterion(int education);
		~EducationProportionCriterion();
		double rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);

	private:
		int education_;
	};

	EducationProportionCriterion::EducationProportionCriterion(int education) : education_(education)
	{
	}

	EducationProportionCriterion::~EducationProportionCriterion()
	{
	}

	double EducationProportionCriterion::rate(data::TerritorialUnit& unit)//pozor na indexovanie, mozno -1
	{
		double edCount = unit.getEducation().getEducation(this->education_); //129
		double livingMan = unit.getAge().getManInUnit(); //529
		double result = 100 * (edCount / livingMan); //tu je result 0
		return result;
	}

	inline std::wstring EducationProportionCriterion::toString(data::TerritorialUnit& unit)
	{
		std::wstring educationStr;
		switch (this->education_) {
		case 0:
			educationStr = L"bez ukonèeného vzdelania: ";
			break;
		case 1:
			educationStr = L"základné: ";
			break;
		case 2:
			educationStr = L"uènovské: ";
			break;
		case 3:
			educationStr = L"stredné: ";
			break;
		case 4:
			educationStr = L"vyššie: ";
			break;
		case 5:
			educationStr = L"vysokoškolské: ";
			break;
		case 6:
			educationStr = L"bez vzdelania: ";
			break;
		case 7:
			educationStr = L"nezistené: ";
			break;
		default:
			break;
		}
		return L"Vzdelanie podiel - " + educationStr + std::to_wstring(rate(unit)) + L'.\n';
	}

}


