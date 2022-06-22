#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class NameCriterion : public Criterion<std::wstring>
	{
	public:
		NameCriterion();
		~NameCriterion();
		std::wstring rate(data::TerritorialUnit & unit);
		std::wstring toString(data::TerritorialUnit& unit);

	private:
	};

	NameCriterion::NameCriterion() 
	{
	}

	NameCriterion::~NameCriterion()
	{
	}

	std::wstring NameCriterion::rate(data::TerritorialUnit& unit)
	{
		return unit.getOfficialTitle();
	}

	inline std::wstring NameCriterion::toString(data::TerritorialUnit& unit)
	{
		return std::wstring();
	}

}


