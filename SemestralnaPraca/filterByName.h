#define ANO L"1"
#define EDUCATION 8
#define LASTEVS 4

#pragma once
#include "age.h"
#include "state.h"
#include "territorialUnit.h"
#include <iostream>
#include "educationCountCriterion.h"
#include "ageGroupCountCriterion.h"
#include "typeCriterion.h"

namespace filtering 
{


	class FilterByName
	{
	public:
		FilterByName(data::State& slovakia);
		void menu();
		void writeInfo(data::TerritorialUnit& unit);
		~FilterByName();
	private:
		data::State& slovakia_;
	};


	inline FilterByName::FilterByName(data::State& slovakia) : slovakia_(slovakia)
	{
		this->menu();
	}

	inline void FilterByName::menu()
	{
		std::wcout << L"\n\n-----H�ADANIE POD�A N�ZVU-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;
			std::wstring unitName = L"";

			std::wcout << L"Zadajte n�zov �zemnej jednotky: ";
			std::getline(std::wcin, unitName, L'\n');

			data::TerritorialUnit* unit;
			if (!unitName.compare(L"Slovensko")) {
				this->writeInfo(slovakia_);
			}
			else if (this->slovakia_.getAllTUnits().tryFind(unitName, unit)) {
				this->writeInfo(*unit);
			}
			else {
				std::wcout << L"Jednotka s dan�m n�zvom sa nena�la.\n";
			}

			std::wcout << L"\nPrajete si vyh�ada� �zemn� jednotku znovu? \n(stla�te 1 pre �no, �ubovoln� znak pre n�vrat do menu):";
			std::getline(std::wcin, choice, L'\n');
			if (choice != ANO) {

				end = true;
			}
		}
	}

	inline void FilterByName::writeInfo(data::TerritorialUnit& unit)
	{
		criterion::TypeCriterion typeCr;
		std::wcout << "\n";

		data::TerritorialUnit* newUnit = &unit; 
		while (&newUnit->getSuperiorUnit() != nullptr) {
			std::wcout << newUnit->getOfficialTitle() << ", �zemn� jednotka: " << typeCr.rate(*newUnit) << "\n";
			data::TerritorialUnit* helpUnit = &newUnit->getSuperiorUnit();
			newUnit = helpUnit;
		}

		std::wcout << L"\nVzdelanie:\n";
		for (int i = 0; i < EDUCATION; i++) {
			criterion::EducationCountCriterion edCr(i);
			std::wcout << edCr.toString(unit) << L"\n";
		}


		int manInUnit = 0;
		std::wcout << L"\nVekov� skupiny:\n";
		for (int i = 1; i < LASTEVS; i++) {
			criterion::AgeGroupCountCriterion edGrCr(i);
			manInUnit += edGrCr.rate(unit);
			std::wcout << edGrCr.toString(unit) << L"\n";
		}

		std::wcout << L"\nPo�et obyvate�ov dokopy: " << manInUnit << L"\n";
	}

	inline FilterByName::~FilterByName()
	{
	}
}




