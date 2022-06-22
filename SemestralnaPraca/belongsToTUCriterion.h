#pragma once
#include "territorialUnit.h"
#include "criterion.h"

namespace criterion
{
	class BelongsToTUCriterion : public Criterion<bool>
	{
	public:
		BelongsToTUCriterion(data::TerritorialUnit& superiorUnit);
		~BelongsToTUCriterion();
		bool rate(data::TerritorialUnit& inferiorUnit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
		data::TerritorialUnit* superiorUnit_;
	};

	BelongsToTUCriterion::BelongsToTUCriterion(data::TerritorialUnit& superiorUnit) : superiorUnit_(&superiorUnit)
	{
	}

	BelongsToTUCriterion::~BelongsToTUCriterion()
	{
	}

	bool BelongsToTUCriterion::rate(data::TerritorialUnit& inferiorUnit)
	{
		return &inferiorUnit.getSuperiorUnit() == this->superiorUnit_;
	}

	inline std::wstring BelongsToTUCriterion::toString(data::TerritorialUnit& unit)
	{
		return std::wstring();
	}

}


