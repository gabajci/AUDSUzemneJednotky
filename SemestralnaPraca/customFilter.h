#define USPESNE 0
#define CHYBA 1
#define ANO L"1"
#define NIE L"2"

#pragma once
#include "territorialUnit.h"
#include "criterion.h"
#include "state.h"
#include "typeCriterion.h"
#include <iostream>
#include "filter.h"
#include "filterWithCriterion.h"
#include "filterRange.h"
#include "educationCountCriterion.h"
#include "educationProportionCriterion.h"
#include "ageCountFromToCriterion.h"
#include "ageProportionFromToCriterion.h"
#include "ageGroupProportionCriterion.h"
#include "ageGroupCountCriterion.h"

namespace filtering
{
	class CustomFilter
	{
	public:
		CustomFilter(structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& data);
		~CustomFilter();
		void menu();
		void customFilter(); //zlozeny
	private:
		structures::SortedSequenceTable < std::wstring, data::TerritorialUnit*>* data_; 
	};

	inline CustomFilter::CustomFilter(structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& data) :
		data_(&data)
	{
		this->menu();
	}

	inline CustomFilter::~CustomFilter()
	{
		//delete this->data_;
	}

	inline void CustomFilter::menu()
	{
		std::wcout << L"\n\n-----POKROÈILÉ FILTROVANIE-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;		
			
			this->customFilter();




			std::wcout << L"\nPrajete si vyfiltrova dáta znovu? \n(stlaète 1 pre áno, ¾ubovolný znak pre pokraèovanie):";
			std::getline(std::wcin, choice, L'\n');
			if (choice== ANO) {				
				//delete this->data_;
				//this->data_ = new structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>();
			}
			else {
				end = true;
			}
		}
	}

	
	inline void CustomFilter::customFilter()
	{
		structures::ArrayList<filter::Filter*> filters;

		std::wstring choice;
		std::wstring type;
		std::wstring from;
		std::wstring to;
		std::wstring param;

		std::wcout << L"\nPrajete si vyfiltrova dáta pod¾a typu vzdelania?\n(stlaète 1 pre áno, ¾ubovolný znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nProsím zvo¾te si typ.\n";
			std::wcout << "1. bez ukonè.vzdel., 2. základné, 3. uènovské, 4. stredné, 5. vyššie, 6. vysokoškolské,7. bez vzdelania, 8. nezistené): ";
			std::getline(std::wcin, type, L'\n');
			int intType = stoi(type);
			if (intType >= 1 && intType <= 8) {
				std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèný poèet)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte prosím parameter DO(koncový poèet)\n";
				std::getline(std::wcin, to, L'\n');
				intType--;
				criterion::EducationCountCriterion* edCountCr = new criterion::EducationCountCriterion(intType);

				int intFrom = stoi(from);
				int intTo = stoi(to);
				filter::FilterRange<int>* edCountCrFilter = new filter::FilterRange<int>(intFrom, intTo, edCountCr);
				filters.add(edCountCrFilter);
			}
			else {
				std::wcout << L"Zlé hodnoty. Filter nebude aplikovaný\n";
			}
		}

		std::wcout << L"\nPrajete si vyfiltrova dáta pod¾a podielu vzdelania?\n(stlaète 1 pre áno, ¾ubovolný znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nProsím zvo¾te si typ.\n";
			std::wcout << "1. bez ukonè.vzdel., 2. základné, 3. uènovské, 4. stredné, 5. vyššie, 6. vysokoškolské,7. bez vzdelania, 8. nezistené): ";
			std::getline(std::wcin, type, L'\n');
			int intType = stoi(type);
			if (intType >= 1 && intType <= 8) {
				std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèné percentá)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte prosím parameter DO(koncové percentá)\n";
				std::getline(std::wcin, to, L'\n');

				intType--;
				criterion::EducationProportionCriterion* edProportion = new criterion::EducationProportionCriterion(intType);

				double intFrom = stoi(from);
				double intTo = stoi(to);
				filter::FilterRange<double>* edProportionFilter = new filter::FilterRange<double>(intFrom, intTo, edProportion);
				filters.add(edProportionFilter);
			}
			else {
				std::wcout << L"Zlé hodnoty. Filter nebude aplikovaný\n";
			}
		}

		std::wcout << L"\nPrajete si vyfiltrova dáta pod¾a veku?\n(stlaète 1 pre áno, ¾ubovolný znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte prosím pohlavie(1. muži, 2. ženy, 3. dokopy)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèný vek)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte prosím parameter DO(koncový vek)\n";
			std::getline(std::wcin, to, L'\n');

			int intFromAge = stoi(from);
			int intToAge = stoi(to);

			if (intFromAge >= 0 && intToAge <= 101) {
				int gender = stoi(param);

				criterion::AgeCountFromToCriterion* ageFromToCr = new criterion::AgeCountFromToCriterion(intFromAge, intToAge, gender);

				std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèný poèet)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte prosím parameter DO(koncový poèet)\n";
				std::getline(std::wcin, to, L'\n');

				int intFrom = stoi(from);
				int intTo = stoi(to);
				filter::FilterRange<int>* ageFromToCrFilter = new filter::FilterRange<int>(intFrom, intTo, ageFromToCr);
				filters.add(ageFromToCrFilter);
			}
			else {
				std::wcout << L"Zlé hodnoty. Filter nebude aplikovaný\n";
			}
		}

		std::wcout << L"\nPrajete si vyfiltrova dáta pod¾a podielu veku?\n(stlaète 1 pre áno, ¾ubovolný znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte prosím pohlavie(1. muži, 2. ženy, 3. dokopy)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèný vek)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte prosím parameter DO(koncový vek)\n";
			std::getline(std::wcin, to, L'\n');

			int intFromAge = stoi(from);
			int intToAge = stoi(to);
			if (intFromAge >= 0 && intToAge <= 101) {
				int gender = stoi(param);

				criterion::AgeProportionFromToCriterion* agePropFromToCr = new criterion::AgeProportionFromToCriterion(intFromAge, intToAge, gender);

				std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèné percentá)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte prosím parameter DO(koncové percentá)\n";
				std::getline(std::wcin, to, L'\n');

				double intFrom = stoi(from);
				double intTo = stoi(to);
				filter::FilterRange<double>* agePropFromToCrFilter = new filter::FilterRange<double>(intFrom, intTo, agePropFromToCr);
				filters.add(agePropFromToCrFilter);
			}
			else {
				std::wcout << L"Zlé hodnoty. Filter nebude aplikovaný\n";
			}
			
		}

		std::wcout << L"\nPrajete si vyfiltrova dáta pod¾a poètu veku EVS skupiny?\n(stlaète 1 pre áno, ¾ubovolný znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte prosím skupinu(1. predproduktívny, 2. produktívny,3. poproduktívny)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèný poèet)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte prosím parameter DO(koncový poèet)\n";
			std::getline(std::wcin, to, L'\n');

			int evs = stoi(param);
			if (evs >= 1 && evs <= 3) {
				criterion::AgeGroupCountCriterion* ageGroupFromToCr = new criterion::AgeGroupCountCriterion(evs);

				int intFrom = stoi(from);
				int intTo = stoi(to);
				filter::FilterRange<int>* ageFromToCrFilter = new filter::FilterRange<int>(intFrom, intTo, ageGroupFromToCr);
				filters.add(ageFromToCrFilter);
			}
			else {
				std::wcout << L"Zlé hodnoty. Filter nebude aplikovaný\n";
			}			
		}

		std::wcout << L"\nPrajete si vyfiltrova dáta pod¾a podielu veku EVS skupiny?\n(stlaète 1 pre áno, ¾ubovolný znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte prosím skupinu(1. predproduktívny, 2. produktívny,3. poproduktívny)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte prosím parameter OD(zaèiatoèné percentá)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte prosím parameter DO(koncové percentá)\n";
			std::getline(std::wcin, to, L'\n');

			int evs = stoi(param);
			if (evs >= 1 && evs <= 3) {
				criterion::AgeGroupProportionCriterion* ageGroupPropFromToCr = new criterion::AgeGroupProportionCriterion(evs);

				double intFrom = stoi(from);
				double intTo = stoi(to);
				filter::FilterRange<double>* ageFromPropToCrFilter = new filter::FilterRange<double>(intFrom, intTo, ageGroupPropFromToCr);
				filters.add(ageFromPropToCrFilter);
			}
			else {
				std::wcout << L"Zlé hodnoty. Filter nebude aplikovaný\n";
			}
			
		}

		std::wcout << L"\n--------------------------------------------------\n";

		if (filters.size() > 0) {
			for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->data_) {
				bool verify = true;
				for (auto filter : filters) {				
					if (!filter->belongsTo(*unit->accessData())) {
						verify = false;
					}
				}
				if (verify) {
					std::wcout << L"\n"+ unit->accessData()->getOfficialTitle() << L"\n";

					criterion::TypeCriterion typeCr;
					data::TerritorialUnit* newUnit = unit->accessData();
					while (&newUnit->getSuperiorUnit() != nullptr) {
						std::wcout << newUnit->getOfficialTitle() << ", územná jednotka: " << typeCr.rate(*newUnit) << "\n";
						data::TerritorialUnit* helpUnit = &newUnit->getSuperiorUnit();
						newUnit = helpUnit;
					}

					for (auto filter : filters) {
						std::wcout << filter->representCriterion(*unit->accessData()) << L"\n";
					}
				}
			}
		}
		else {
			std::wcout << L"Neboli vyfiltrované žiadne dáta.\n";
		}
		

		for (auto filter : filters) {
			delete filter;
		}

		std::wcout << L"\n--------------------------------------------------\n";
	}

}


