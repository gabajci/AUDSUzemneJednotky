#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class SuperiorCriterion : public Criterion<data::TerritorialUnit&>
	{
	public:
		SuperiorCriterion();
		~SuperiorCriterion();
		data::TerritorialUnit& rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);

	private:
	};

	SuperiorCriterion::SuperiorCriterion()
	{
	}

	SuperiorCriterion::~SuperiorCriterion()
	{
	}

	data::TerritorialUnit& SuperiorCriterion::rate(data::TerritorialUnit& unit)
	{
		return unit.getSuperiorUnit();
	}

	inline std::wstring SuperiorCriterion::toString(data::TerritorialUnit& unit)
	{
		return std::wstring();
	}

}


