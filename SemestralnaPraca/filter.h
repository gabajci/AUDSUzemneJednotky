#pragma once
#include "territorialUnit.h"

namespace filter
{
	class Filter
	{
	public:
		virtual ~Filter() {};
		virtual bool belongsTo(data::TerritorialUnit& unit) = 0;
		virtual std::wstring representCriterion(data::TerritorialUnit & unit) = 0;
	};
}


