#pragma once
#include "age.h"
#include "education.h"
#include "territorialUnit.h"

namespace data
{
	class Township : public TerritorialUnit
	{
	public:
		Township(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit);
		~Township();
	};


	data::Township::Township(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit) :
		TerritorialUnit(officialTitle,code,note,territorialUnit)
	{
	}

	inline Township::~Township()
	{
	}

}


