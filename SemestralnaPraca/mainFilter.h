#define USPESNE 0
#define CHYBA 1
#define ANO L"1"
#define NIE L"2"
#define VRATVSETKY 3
#define VRATOBCE 4
#define VRATOKRESY 5

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
	class MainFilter
	{
	public:
		MainFilter(data::State& slovakia);
		~MainFilter();
		structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& menu();
		int filterByTypeOrCompetence(std::wstring& unitName, std::wstring& territorilUnit);
	private:
		structures::SortedSequenceTable < std::wstring, data::TerritorialUnit*>* data_;
		data::State* slovakia_; //parameter
	};

	inline MainFilter::MainFilter(data::State& slovakia) :
		slovakia_(&slovakia),
		data_(new structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>())
	{
	}

	inline MainFilter::~MainFilter()
	{
		delete this->data_;
	}

	inline structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& MainFilter::menu()
	{
		std::wcout << L"\n\n-----HLAVNÉ FILTROVANIE-----\n\n";
		bool end = false;
		while (!end) {
			std::wcin.clear();

			std::wstring choice;
			std::wstring unitName = L"";
			std::wstring territorilUnit = L"";

			std::wcout << L"Prajete si vyfiltrova dáta pod¾a typu územnej jednotky?\n";
			std::wcout << L"(stlaète 1 pre áno, ¾ubovolný znak aplikovanie všetkých typov ÚJ) : ";
			std::getline(std::wcin, choice, L'\n');
			if (choice == ANO) {
				std::wcout << L"\nZadajte prosím typ územnej jednotky.\n1. Kraj 2. Okres 3. Obec (zadajte èíslo): ";
				std::getline(std::wcin, choice, L'\n');
				if (choice == L"1") {
					territorilUnit = L"District";
				}
				else if (choice == L"2") {
					territorilUnit = L"Region";
				}
				else if (choice == L"3") {
					territorilUnit = L"Township";
				}
			}

			choice = NIE;
			std::wcout << L"\nPrajete si vyfiltrova dáta ktoré patria pod územnú jednotku s názvom?\n";
			std::wcout << L"(stlaète 1 pre áno, ¾ubovolný znak pre aplikovanie ÚJ patriacich pod Slovensko) : ";
			std::getline(std::wcin, choice, L'\n');

			if (choice == ANO) {
				std::wcout << L"\nZadajte prosím názov územnej jednotky:";
				std::getline(std::wcin, unitName, L'\n');
			}
			choice = NIE;

			int result = this->filterByTypeOrCompetence(unitName, territorilUnit);

			if (result == USPESNE) {
				if (this->data_->isEmpty()) {
					std::wcout << L"\nŽiadna územná jednotka nespåòa Vami zadané filtre.";
				}
				else {
					for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *this->data_) {
						std::wcout << unit->accessData()->getOfficialTitle() << L"\n";
					}
				}				
			}
			else if (result == VRATVSETKY) {
				std::wcout << L"\nNeboli vyfiltrované žiadne dáta. Program bude pracova so všetkými územnými jednotkami.";
			}
			else if (result == VRATOBCE) {
				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : this->slovakia_->getTowns()) {
					std::wcout << unit->accessData()->getOfficialTitle() << L"\n";
				}
			}
			else if (result == VRATOKRESY) {
				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : this->slovakia_->getRegions()) {
					std::wcout << unit->accessData()->getOfficialTitle() << L"\n";
				}
			}

			std::wcout << L"\nPrajete si vyfiltrova dáta znovu? \n(stlaète 1 pre áno, ¾ubovolný znak pre pokraèovanie):";
			std::getline(std::wcin, choice, L'\n');
			if (choice == ANO) {
				delete this->data_;
				this->data_ = new structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>();
			}
			else {
				end = true;
				if (result == VRATVSETKY) {
					return this->slovakia_->getAllTUnits();
				} else if (result == VRATOBCE) {
					return this->slovakia_->getTowns();
				} else if (result == VRATOKRESY) {
					return this->slovakia_->getRegions();
				}
			}
		}		
		return *this->data_;
	}



	inline int MainFilter::filterByTypeOrCompetence(std::wstring& unitName, std::wstring& territorilUnit)
	{ //unitName = nazov vyssej uzemnej jednotky           territorialUnit - kraj/obec/..
		if (unitName == L"" && territorilUnit == L"") {
			//this->data_ = &this->slovakia_->getAllTUnits(); //problem
			return VRATVSETKY;
		}

		bool filterByType = false;
		if (territorilUnit != L"") {
			filterByType = true;
		}

		if (unitName != L"") {
			data::TerritorialUnit* tu;
			bool unitFound = this->slovakia_->getAllTUnits().tryFind(unitName, tu);

			if (!unitFound) {
				return CHYBA;
			}


			criterion::TypeCriterion typeCr_;
			std::wstring type = typeCr_.rate(*tu);
			//this->data_->insert(tu->getOfficialTitle(), tu);


			if (!type.compare(L"Region")) {
				for (structures::TableItem<std::wstring, data::Township*>* town : reinterpret_cast<data::Region*>(tu)->getTowns())
				{
					if (filterByType && territorilUnit != L"Township") {
						break;
					}
					else {
						this->data_->insert(town->accessData()->getOfficialTitle(), town->accessData());
					}

				}
			}
			else if (!type.compare(L"District")) {
				for (structures::TableItem<std::wstring, data::Region*>* region : reinterpret_cast<data::District*>(tu)->getRegions())
				{
					if (filterByType && territorilUnit != L"Region") {
					}
					else {
						this->data_->insert(region->accessData()->getOfficialTitle(), region->accessData());
					}
				}
				for (structures::TableItem<std::wstring, data::TerritorialUnit*>* town : reinterpret_cast<data::District*>(tu)->getTowns())
				{
					if (filterByType && territorilUnit != L"Township") {
					}
					else {
						this->data_->insert(town->accessData()->getOfficialTitle(), town->accessData());
					}
				}

					/*for (structures::TableItem<std::wstring, data::Township*>* town : region->accessData()->getTowns())
					{
						if (filterByType && territorilUnit != L"Township") {
							break;
						}
						else {
							this->data_->insert(town->accessData()->getOfficialTitle(), town->accessData());
						}
					}*/
				
			}
			/*else if (!type.compare(L"State")) {
				for (structures::TableItem<std::wstring, data::District*>* district : reinterpret_cast<data::State*>(tu)->getDistricts())
				{
					if (filterByType && territorilUnit != L"District") {
					}
					else {
						this->data_->insert(district->accessData()->getOfficialTitle(), district->accessData());
					}
					for (structures::TableItem<std::wstring, data::Region*>* region : district->accessData()->getRegions())
					{
						if (filterByType && territorilUnit != L"Region") {
						}
						else {
							this->data_->insert(region->accessData()->getOfficialTitle(), region->accessData());
						}
						for (structures::TableItem<std::wstring, data::Township*>* town : region->accessData()->getTowns())
						{
							if (filterByType && territorilUnit != L"Township") {
								break;
							}
							else {
								this->data_->insert(town->accessData()->getOfficialTitle(), town->accessData());
							}
						}

					}

				}
			}*/
			return USPESNE;
		}

		if (territorilUnit != L"" && unitName == L"") {

			if (territorilUnit == L"Township") {
				/*for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : this->slovakia_->getTowns()) {
					this->data_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());					
				}*/
				
				return VRATOBCE;
			}
			else if(territorilUnit == L"Region") {
				/*for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : this->slovakia_->getRegions()) {
					this->data_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
				}*/
				return VRATOKRESY;
			}
			else if (territorilUnit == L"District") {
				for (structures::TableItem<std::wstring, data::District*>* unit : this->slovakia_->getDistricts()) {
					this->data_->insert(unit->accessData()->getOfficialTitle(), unit->accessData());
				}
			}
			
			return USPESNE;
		}

		return CHYBA;
	}
}


