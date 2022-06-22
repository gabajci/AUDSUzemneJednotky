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
		std::wcout << L"\n\n-----N�JDENIE NAJV�ȊEJ / NAJMEN�EJ  VEKOVEJ SKUPINY-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;
			std::wstring evs;

			std::wcout << L"Najv��ia vekov� skupina - 1\n";
			std::wcout << L"Najmen�ia vekov� skupina - 2\n";
			std::getline(std::wcin, choice, L'\n');


			std::wcout << L"\nZadajte pros�m skupinu(1. predprodukt�vny, 2. produkt�vny,3. poprodukt�vny)\n";
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
				std::wcout << L"Neplatn� vo�ba.\n";
			}
			
			std::wcout << L"\nPrajete si n�js� najv��iu / najmen�iu vekov� skupinu znovu? \n(stla�te 1 pre �no, �ubovoln� znak pre n�vrat do menu):";
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
			std::wcout << bestUnit->getOfficialTitle() << ", �zemn� jednotka: " << typeCr.rate(*bestUnit) << "\n";
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




