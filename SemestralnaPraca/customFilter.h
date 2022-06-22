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
		std::wcout << L"\n\n-----POKRO�IL� FILTROVANIE-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;		
			
			this->customFilter();




			std::wcout << L"\nPrajete si vyfiltrova� d�ta znovu? \n(stla�te 1 pre �no, �ubovoln� znak pre pokra�ovanie):";
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

		std::wcout << L"\nPrajete si vyfiltrova� d�ta pod�a typu vzdelania?\n(stla�te 1 pre �no, �ubovoln� znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nPros�m zvo�te si typ.\n";
			std::wcout << "1. bez ukon�.vzdel., 2. z�kladn�, 3. u�novsk�, 4. stredn�, 5. vy��ie, 6. vysoko�kolsk�,7. bez vzdelania, 8. nezisten�): ";
			std::getline(std::wcin, type, L'\n');
			int intType = stoi(type);
			if (intType >= 1 && intType <= 8) {
				std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� po�et)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte pros�m parameter DO(koncov� po�et)\n";
				std::getline(std::wcin, to, L'\n');
				intType--;
				criterion::EducationCountCriterion* edCountCr = new criterion::EducationCountCriterion(intType);

				int intFrom = stoi(from);
				int intTo = stoi(to);
				filter::FilterRange<int>* edCountCrFilter = new filter::FilterRange<int>(intFrom, intTo, edCountCr);
				filters.add(edCountCrFilter);
			}
			else {
				std::wcout << L"Zl� hodnoty. Filter nebude aplikovan�\n";
			}
		}

		std::wcout << L"\nPrajete si vyfiltrova� d�ta pod�a podielu vzdelania?\n(stla�te 1 pre �no, �ubovoln� znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nPros�m zvo�te si typ.\n";
			std::wcout << "1. bez ukon�.vzdel., 2. z�kladn�, 3. u�novsk�, 4. stredn�, 5. vy��ie, 6. vysoko�kolsk�,7. bez vzdelania, 8. nezisten�): ";
			std::getline(std::wcin, type, L'\n');
			int intType = stoi(type);
			if (intType >= 1 && intType <= 8) {
				std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� percent�)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte pros�m parameter DO(koncov� percent�)\n";
				std::getline(std::wcin, to, L'\n');

				intType--;
				criterion::EducationProportionCriterion* edProportion = new criterion::EducationProportionCriterion(intType);

				double intFrom = stoi(from);
				double intTo = stoi(to);
				filter::FilterRange<double>* edProportionFilter = new filter::FilterRange<double>(intFrom, intTo, edProportion);
				filters.add(edProportionFilter);
			}
			else {
				std::wcout << L"Zl� hodnoty. Filter nebude aplikovan�\n";
			}
		}

		std::wcout << L"\nPrajete si vyfiltrova� d�ta pod�a veku?\n(stla�te 1 pre �no, �ubovoln� znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte pros�m pohlavie(1. mu�i, 2. �eny, 3. dokopy)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� vek)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte pros�m parameter DO(koncov� vek)\n";
			std::getline(std::wcin, to, L'\n');

			int intFromAge = stoi(from);
			int intToAge = stoi(to);

			if (intFromAge >= 0 && intToAge <= 101) {
				int gender = stoi(param);

				criterion::AgeCountFromToCriterion* ageFromToCr = new criterion::AgeCountFromToCriterion(intFromAge, intToAge, gender);

				std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� po�et)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte pros�m parameter DO(koncov� po�et)\n";
				std::getline(std::wcin, to, L'\n');

				int intFrom = stoi(from);
				int intTo = stoi(to);
				filter::FilterRange<int>* ageFromToCrFilter = new filter::FilterRange<int>(intFrom, intTo, ageFromToCr);
				filters.add(ageFromToCrFilter);
			}
			else {
				std::wcout << L"Zl� hodnoty. Filter nebude aplikovan�\n";
			}
		}

		std::wcout << L"\nPrajete si vyfiltrova� d�ta pod�a podielu veku?\n(stla�te 1 pre �no, �ubovoln� znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte pros�m pohlavie(1. mu�i, 2. �eny, 3. dokopy)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� vek)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte pros�m parameter DO(koncov� vek)\n";
			std::getline(std::wcin, to, L'\n');

			int intFromAge = stoi(from);
			int intToAge = stoi(to);
			if (intFromAge >= 0 && intToAge <= 101) {
				int gender = stoi(param);

				criterion::AgeProportionFromToCriterion* agePropFromToCr = new criterion::AgeProportionFromToCriterion(intFromAge, intToAge, gender);

				std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� percent�)\n";
				std::getline(std::wcin, from, L'\n');
				std::wcout << L"\nZadajte pros�m parameter DO(koncov� percent�)\n";
				std::getline(std::wcin, to, L'\n');

				double intFrom = stoi(from);
				double intTo = stoi(to);
				filter::FilterRange<double>* agePropFromToCrFilter = new filter::FilterRange<double>(intFrom, intTo, agePropFromToCr);
				filters.add(agePropFromToCrFilter);
			}
			else {
				std::wcout << L"Zl� hodnoty. Filter nebude aplikovan�\n";
			}
			
		}

		std::wcout << L"\nPrajete si vyfiltrova� d�ta pod�a po�tu veku EVS skupiny?\n(stla�te 1 pre �no, �ubovoln� znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte pros�m skupinu(1. predprodukt�vny, 2. produkt�vny,3. poprodukt�vny)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� po�et)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte pros�m parameter DO(koncov� po�et)\n";
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
				std::wcout << L"Zl� hodnoty. Filter nebude aplikovan�\n";
			}			
		}

		std::wcout << L"\nPrajete si vyfiltrova� d�ta pod�a podielu veku EVS skupiny?\n(stla�te 1 pre �no, �ubovoln� znak pre nie):";
		std::getline(std::wcin, choice, L'\n');

		if (choice == ANO) {
			std::wcout << L"\nZadajte pros�m skupinu(1. predprodukt�vny, 2. produkt�vny,3. poprodukt�vny)\n";
			std::getline(std::wcin, param, L'\n');
			std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� percent�)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte pros�m parameter DO(koncov� percent�)\n";
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
				std::wcout << L"Zl� hodnoty. Filter nebude aplikovan�\n";
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
						std::wcout << newUnit->getOfficialTitle() << ", �zemn� jednotka: " << typeCr.rate(*newUnit) << "\n";
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
			std::wcout << L"Neboli vyfiltrovan� �iadne d�ta.\n";
		}
		

		for (auto filter : filters) {
			delete filter;
		}

		std::wcout << L"\n--------------------------------------------------\n";
	}

}


