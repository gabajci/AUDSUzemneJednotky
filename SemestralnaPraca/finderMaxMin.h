#define ANO L"1"
#define EDUCATION 8
#define LASTEVS 4

#pragma once
#include "territorialUnit.h"
#include <iostream>
#include "ageGroupCountCriterion.h"
#include "typeCriterion.h"

namespace filtering
{


	class FinderMaxMin
	{
	public:
		FinderMaxMin(structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& filteredData);
		void menu();
		void find(int scenario,int evs);
		~FinderMaxMin();
	private:
		structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>* filteredData_;
	};


	inline FinderMaxMin::FinderMaxMin(structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& filteredData) : filteredData_(&filteredData)
	{
		this->menu();
	}

	inline void FinderMaxMin::menu()
	{
		std::wcout << L"\n\n-----NÁJDENIE NAJVÄÈŠEJ / NAJMENŠEJ  VEKOVEJ SKUPINY-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;
			std::wstring evs;

			std::wcout << L"Najväèšia veková skupina - 1\n";
			std::wcout << L"Najmenšia veková skupina - 2\n";
			std::getline(std::wcin, choice, L'\n');


			std::wcout << L"\nZadajte prosím skupinu(1. predproduktívny, 2. produktívny,3. poproduktívny)\n";
			std::getline(std::wcin, evs, L'\n');

			int evsInt = stoi(evs);
			if (evsInt >= 1 && evsInt <= 3) {
				if (choice == L"1") {
					this->find(1, evsInt);
				}
				else if (choice == L"2") {
					this->find(2, evsInt);
				}
			}
			else {
				std::wcout << L"Neplatná vo¾ba.\n";
			}
			
			std::wcout << L"\nPrajete si nájs najväèšiu / najmenšiu vekovú skupinu znovu? \n(stlaète 1 pre áno, ¾ubovolný znak pre návrat do menu):";
			std::getline(std::wcin, choice, L'\n');
			if (choice != ANO) {

				end = true;
			}
		}
	}

	inline void FinderMaxMin::find(int scenario,int evs)
	{
		criterion::AgeGroupCountCriterion* criterion = new criterion::AgeGroupCountCriterion(evs);

		data::TerritorialUnit* bestUnit = nullptr;

		int bestValue = INT_MIN;
		if (scenario == 1) {

			for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *filteredData_) {
				int unitValue = criterion->rate(*unit->accessData());
				if (unitValue > bestValue) {
					bestUnit = unit->accessData();
					bestValue = unitValue;
				}
			}

		} else if (scenario == 2) {
			bestValue = INT_MAX;
			for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *filteredData_) {
				int unitValue = criterion->rate(*unit->accessData());
				if (unitValue < bestValue) {
					bestUnit = unit->accessData();
					bestValue = unitValue;
				}
			}

		}

		criterion::TypeCriterion typeCr;
		std::wcout << "\n";

		std::wcout << bestUnit->getOfficialTitle() << ". " << criterion->toString(*bestUnit) << "\n";

		while (&bestUnit->getSuperiorUnit() != nullptr) {
			std::wcout << bestUnit->getOfficialTitle() << ", územná jednotka: " << typeCr.rate(*bestUnit) << "\n";
			data::TerritorialUnit* helpUnit = &bestUnit->getSuperiorUnit();
			bestUnit = helpUnit;
		}
		std::wcout << "\n";

		delete criterion;
	}

	inline FinderMaxMin::~FinderMaxMin()
	{
	}
}




