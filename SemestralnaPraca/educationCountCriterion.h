#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class EducationCountCriterion : public Criterion<int>
	{
	public:
		EducationCountCriterion(int education);
		~EducationCountCriterion();
		int rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);

	private:
		int education_;
	};

	EducationCountCriterion::EducationCountCriterion(int education) : education_(education)
	{
	}

	EducationCountCriterion::~EducationCountCriterion()
	{
	}

	int EducationCountCriterion::rate(data::TerritorialUnit& unit)
	{
		return unit.getEducation().getEducation(this->education_);//pozor na indexovanie, mozno -1
	}

	inline std::wstring EducationCountCriterion::toString(data::TerritorialUnit& unit)
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
		return L"vzdelanie poèet - "+ educationStr + std::to_wstring(rate(unit)) + L'.\n';
	}

}


