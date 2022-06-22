#pragma once
#include "territorialUnit.h"
#include "criterion.h"
#include "state.h"

namespace criterion
{
	class TypeCriterion : public Criterion<std::wstring>
	{
	public:
		TypeCriterion();
		~TypeCriterion();
		std::wstring rate(data::TerritorialUnit& unit);
		std::wstring toString(data::TerritorialUnit& unit);
	private:
	};

	TypeCriterion::TypeCriterion()
	{
	}

	TypeCriterion::~TypeCriterion()
	{
	}

	std::wstring TypeCriterion::rate(data::TerritorialUnit& unit) //mozno je zle dynamic cast<data::state*>(unit) nechcel fungovat
	{
		data::TerritorialUnit* newUnit = &unit; //mozno spravit z tohoto enum
		int numberOfSuperiors = 0;

		while (&newUnit->getSuperiorUnit() != nullptr) {
			numberOfSuperiors++;
			data::TerritorialUnit* helpUnit = &newUnit->getSuperiorUnit();
			newUnit = helpUnit;
		}

		switch (numberOfSuperiors) {
		case 0: {
			return L"State";
			break;
		}
		case 1: {
			return L"District";
			break;
		}
		case 2: {
			return L"Region";
			break;
		}
		case 3: {
			return L"Township";
			break;
		} 
		default:
			return L"Not Found";
			break;
		}
	}

	inline std::wstring TypeCriterion::toString(data::TerritorialUnit& unit)
	{
		return std::wstring();
	}


}


