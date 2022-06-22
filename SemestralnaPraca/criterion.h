#pragma once
#include "territorialUnit.h"

namespace criterion
{
	template<typename T>
	class Criterion
	{
	public:
		virtual T rate(data::TerritorialUnit& unit) = 0;
		virtual std::wstring toString(data::TerritorialUnit& unit) = 0;
	};

	enum Gender { man = 1, woman = 2 , together = 3};

	enum EVS { preproductive = 1, productive = 2 , postproductive = 3 };

	enum EducationEnum { noFinishedEd = 1, primary = 2 , craft = 3 ,
	                    high = 4, higher = 5, university = 6, noEd = 7 , noDetected = 8};

}


