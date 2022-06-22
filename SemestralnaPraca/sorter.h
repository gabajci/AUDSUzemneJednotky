#define ANO L"1"
#define EDUCATION 8
#define LASTEVS 4
#define LOWTOTOP 1
#define TOPTOLOW 2

#pragma once
#include "territorialUnit.h"
#include <iostream>
#include "ageGroupCountCriterion.h"
#include "typeCriterion.h"
#include "quickSort.h"
#include "nameCriterion.h"
#include "ageCountCriterion.h"
#include "filterValue.h"

namespace filtering
{
	class Sorter
	{
	public:
		Sorter(structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& filteredData);
		void menu();
		void sort(int choice);
		~Sorter();
	private:
		structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>* filteredData_;
		structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>* dataToSort_;
		int direction_ = 0;
	};


	inline Sorter::Sorter(structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& filteredData) : 
		filteredData_(new structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>()),
		dataToSort_(new structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>())
	{
		for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : filteredData) {
			this->filteredData_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
		}

		this->menu();
	}

	inline void Sorter::menu()
	{
		std::wcout << L"\n\n-----TRIEDENIE D�T-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;
			std::wstring sortDirection;

			std::wcout << L"Pod�a n�zvu - 1\n";
			std::wcout << L"Pod�a po�tu vzdelan�ch - 2\n";
			std::wcout << L"Pod�a podielu vzdelan�ch- 3\n";
			std::wcout << L"Pod�a podielu veku - 4\n";
			std::wcout << L"Pod�a po�tu vekovej skupiny - 5\n";
			std::getline(std::wcin, choice, L'\n');

			std::wcout << L"\nVzostupne - 1\n";
			std::wcout << L"Zostupne - 2\n";
			std::getline(std::wcin, sortDirection, L'\n');
			this->direction_ = stoi(sortDirection);
			
			if (choice == L"1" || choice == L"2" || choice == L"3"
				|| choice == L"4" || choice == L"5") {
				this->sort(stoi(choice));				
			}			
			else {
				std::wcout << L"Neplatn� vo�ba.\n";
			}
			
			std::wcout << L"\nPrajete si d�ta utriedi� znovu? \n(stla�te 1 pre �no, �ubovoln� znak pre n�vrat do menu):";
			std::getline(std::wcin, choice, L'\n');
			if (choice != ANO) {
				end = true;
			}
			else {
				delete this->dataToSort_;
				this->dataToSort_ = new structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>();
			}
		}
	}

	inline void Sorter::sort(int choice)
	{
		if (choice == 1) {
			criterion::NameCriterion* nameCr = new criterion::NameCriterion();


			filtering::QuickSort<std::wstring> sort;
			sort.sort(nameCr, *this->filteredData_);

			if (this->direction_ == 1) {
				for (int i = this->filteredData_->size() - 1; i >= 0; i--) {
					std::wcout << this->filteredData_->getItemAtIndex(i).accessData()->getOfficialTitle() << L"\n";
				}
			}
			else {
				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->filteredData_) {
					std::wcout << unit->accessData()->getOfficialTitle() << L"\n";

				}
			}

			delete nameCr;
			return;
		}
		else if (choice == 2) {
			std::wstring type;
			std::wstring from;
			std::wstring to;

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

				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->filteredData_) {
					if (edCountCrFilter->belongsTo(*unit->accessData())) {
						this->dataToSort_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
					}
				}

				filtering::QuickSort<int> sort;
				sort.sort(edCountCr, *this->dataToSort_);

				if (this->direction_ == 1) {
					for (int i = this->dataToSort_->size()-1; i >= 0; i--) {
						std::wcout << this->dataToSort_->getItemAtIndex(i).accessData()->getOfficialTitle() << " - ";
						std::wcout << edCountCr->toString(*this->dataToSort_->getItemAtIndex(i).accessData()) << L"\n";
					}
				}
				else {
					for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->dataToSort_) {
						std::wcout << unit->accessData()->getOfficialTitle() << "  -  " << edCountCr->toString(*unit->accessData()) << L"\n";
					}
				}
				

				delete edCountCrFilter;
			}
		}
		else if (choice == 3) {
			std::wstring type;
			std::wstring from;
			std::wstring to;

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
				
				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->filteredData_) {
					if (edProportionFilter->belongsTo(*unit->accessData())) {
						this->dataToSort_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
					}
				}

				filtering::QuickSort<double> sort;
				sort.sort(edProportion, *this->dataToSort_);

				if (this->direction_ == 1) {
					for (int i = this->dataToSort_->size() - 1; i >= 0; i--) {
						std::wcout << this->dataToSort_->getItemAtIndex(i).accessData()->getOfficialTitle() << " - ";
						std::wcout << edProportion->toString(*this->dataToSort_->getItemAtIndex(i).accessData()) << L"\n";
					}
				}
				else {
					for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->dataToSort_) {
						std::wcout << unit->accessData()->getOfficialTitle() << "  -  " << edProportion->toString(*unit->accessData()) << L"\n";

					}
				}

				delete edProportionFilter;
			}
		}
		else if (choice == 4) {
			std::wstring param;
			std::wstring from;
			std::wstring to;

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

				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->filteredData_) {
					if (agePropFromToCrFilter->belongsTo(*unit->accessData())) {
						this->dataToSort_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
					}
				}

				filtering::QuickSort<double> sort;
				sort.sort(agePropFromToCr, *this->dataToSort_);

				if (this->direction_ == 1) {
					for (int i = this->dataToSort_->size() - 1; i >= 0; i--) {
						std::wcout << this->dataToSort_->getItemAtIndex(i).accessData()->getOfficialTitle() << " - ";
						std::wcout << agePropFromToCr->toString(*this->dataToSort_->getItemAtIndex(i).accessData()) << L"\n";
					}
				}
				else {
					for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->dataToSort_) {
						std::wcout << unit->accessData()->getOfficialTitle() << "  -  " << agePropFromToCr->toString(*unit->accessData()) << L"\n";

					}
				}

				delete agePropFromToCrFilter;
			}
		}
		else if (choice == 5) {
			std::wstring evs;
			std::wstring from;
			std::wstring to;
			std::wcout << L"\nZadajte pros�m skupinu(1. predprodukt�vny, 2. produkt�vny,3. poprodukt�vny)\n";
			std::getline(std::wcin, evs, L'\n');
			int evsInt = stoi(evs);
			std::wcout << L"\nZadajte pros�m parameter OD(za�iato�n� po�et)\n";
			std::getline(std::wcin, from, L'\n');
			std::wcout << L"\nZadajte pros�m parameter DO(koncov� po�et)\n";
			std::getline(std::wcin, to, L'\n');

			criterion::AgeGroupCountCriterion* ageGroupFromToCr = new criterion::AgeGroupCountCriterion(evsInt);
			int intFrom = stoi(from);
			int intTo = stoi(to);
			filter::FilterRange<int>* agePropCrFilter = new filter::FilterRange<int>(intFrom, intTo, ageGroupFromToCr);

			for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->filteredData_) {
				if (agePropCrFilter->belongsTo(*unit->accessData())) {
					this->dataToSort_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
				}
			}

			filtering::QuickSort<int> sort;
			sort.sort(ageGroupFromToCr, *this->dataToSort_);

			if (this->direction_ == 1) {
				for (int i = this->dataToSort_->size() - 1; i >= 0; i--) {
					std::wcout << this->dataToSort_->getItemAtIndex(i).accessData()->getOfficialTitle() << " - ";
					std::wcout << ageGroupFromToCr->toString(*this->dataToSort_->getItemAtIndex(i).accessData()) << L"\n";
				}
			}
			else {
				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->dataToSort_) {
					std::wcout << unit->accessData()->getOfficialTitle() << "  -  " << ageGroupFromToCr->toString(*unit->accessData()) << L"\n";

				}
			}

			delete agePropCrFilter;
		}

	}


	inline Sorter::~Sorter()
	{
		delete this->filteredData_;
		delete this->dataToSort_;
	}
}




