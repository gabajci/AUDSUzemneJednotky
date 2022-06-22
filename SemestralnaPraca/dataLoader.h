#pragma once
#define AGES 101
#define EDUCATION 8

#include "state.h"
#include "district.h"
#include "region.h"
#include "township.h"

#include "structures/structure.h"
#include "structures/structure_iterator.h"
#include "structures/table/table.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>



namespace data
{
	class DataLoader
	{
	public:
		DataLoader(State& slovakia);
		void loadTerritorianUnitData();
		void loadAge();
		void loadEducation();
		void test();
		~DataLoader();
	private:
		State& state_;
	};

	data::DataLoader::DataLoader(State& state) : state_(state)
	{
		loadTerritorianUnitData();
		loadAge();
		loadEducation();
		//test();
	}

	inline void DataLoader::loadTerritorianUnitData() //ako parameter pride stat- slovensko odkazom
	{
		//Kraje
		std::wifstream district;
		district.imbue(std::locale("Slovak"));
		district.open("kraje.csv");

		std::wstring line;
		std::wstring code;
		std::wstring title;
		std::wstring note;
		std::wstring noNeed;

		std::getline(district, line); //prvy riadok preskoc - netreba

		while (std::getline(district, line))   //precita cely riadok
		{		
			std::wstringstream liner(line); // pracuje s riadkom
			std::getline(liner, noNeed, L';'); //netreba 
			std::getline(liner, code, L';'); //cislo kraja  
			std::getline(liner, title, L';'); //nazov kraja
			std::getline(liner, noNeed, L';'); //nazov kraja
			std::getline(liner, noNeed, L';'); //nazov kraja
			std::getline(liner, note, L';'); //nazov kraja

			
			if (title.compare(L"Zahranicie")) {
				data::District* district = new District(title, code, note, &state_);
				this->state_.getDistricts().insert(title, district);
				this->state_.getAllTUnits().insert(title, district);
			}					
		}  	

		//Okresy
		std::wifstream region;
		region.open("okresy.csv");
		region.imbue(std::locale("Slovak"));

		std::getline(region, line); //prvy riadok precitaj = preskoc
		while (std::getline(region, line))   //precita cely riadok
		{
			std::wstringstream liner(line); // pracuje s riadkom
			std::getline(liner, noNeed, L';'); //netreba 
			std::getline(liner, code, L';'); //kod 
			std::getline(liner, title, L';'); //nazov kraja
			std::getline(liner, noNeed, L';'); //netreba
			std::getline(liner, noNeed, L';'); //netreba 
			std::getline(liner, note, L';'); //note



			for (structures::TableItem<std::wstring, data::District*>* district : this->state_.getDistricts()) {

				std::wstring DistrictCode = district->accessData()->getCode();

				if (note != L"" && !DistrictCode.compare(note.substr(0, 1))) { //L"" je zahranicie.
					data::Region* region = new Region(title, code, note, district->accessData());
					district->accessData()->getRegions().insert(title, region);
					this->state_.getAllTUnits().insert(title, region);
					this->state_.getRegions().insert(title, region);
					break;
				}
			}			
		}

		//Obce
		std::wifstream township;
		township.open("obce.csv");
		township.imbue(std::locale("Slovak"));

		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* helperTitleExistTable
			= new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* helperTitleExistTable2
			= new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>();

		std::getline(township, line); //prvy riadok precitaj = preskoc
		while (std::getline(township, line))   //precita cely riadok
		{
			std::wstringstream liner(line); // pracuje s riadkom
			std::getline(liner, noNeed, L';'); //netreba 
			std::getline(liner, code, L';'); //cislo kraja  
			std::getline(liner, noNeed, L';'); //netreba
			std::getline(liner, title, L';'); //nazov kraja
			std::getline(liner, noNeed, L';'); //netreba
			std::getline(liner, noNeed, L';'); //netreba
			std::getline(liner, note, L';'); //note


			

			for (structures::TableItem<std::wstring, data::District*>* district : this->state_.getDistricts()) {

				for (structures::TableItem<std::wstring, data::Region*>* region : district->accessData()->getRegions()) {

					std::wstring RegionCode = region->accessData()->getCode().substr(3, 3);

					if (!RegionCode.compare(code.substr(3, 3))) {

						data::Township* town = new Township(title, code, note, region->accessData());
						region->accessData()->getTowns().insert(title, town);  	
						std::wstring defaultTitle = title;

						if (this->state_.getAllTUnits().containsKey(title)) {
							helperTitleExistTable->insert(title, town);
							data::TerritorialUnit* existedTown = this->state_.getAllTUnits().remove(title);
							this->state_.getTowns().remove(title);

							std::wstring oldTitle = existedTown->getOfficialTitle() + L" " + existedTown->getSuperiorUnit().getOfficialTitle();
							existedTown->setOfficialTitle(oldTitle);

							std::wstring newTitle = title + L" " + region->accessData()->getOfficialTitle();
							town->setOfficialTitle(newTitle);

							this->state_.getTowns().insert(oldTitle, existedTown);
							this->state_.getTowns().insert(newTitle, town);
							this->state_.getAllTUnits().insert(oldTitle, existedTown);
							this->state_.getAllTUnits().insert(newTitle, town);
						}
						else if (helperTitleExistTable->containsKey(title)) {
							std::wstring newTitle = title + L" " + region->accessData()->getOfficialTitle();
							town->setOfficialTitle(newTitle);

							this->state_.getAllTUnits().insert(newTitle, town);
							this->state_.getTowns().insert(newTitle, town);
						}
						else {
							this->state_.getAllTUnits().insert(title, town);
							this->state_.getTowns().insert(title, town);
						}

						if (district->accessData()->getTowns().containsKey(defaultTitle)) {
							helperTitleExistTable2->insert(defaultTitle, town);
							data::TerritorialUnit* existedTown = district->accessData()->getTowns().remove(defaultTitle);

							district->accessData()->getTowns().insert(existedTown->getOfficialTitle(), existedTown);
							district->accessData()->getTowns().insert(town->getOfficialTitle(), town);
						}
						else if (helperTitleExistTable2->containsKey(defaultTitle)) {

							district->accessData()->getTowns().insert(town->getOfficialTitle(), town);
						}
						else {
							district->accessData()->getTowns().insert(defaultTitle, town);
						}
						continue;
					}
					continue;
				}
			}						
		}	

		/*std::wcout << L"\nPri načítavaní sa našli obce s identickým názvom.\n" <<
			L"V prípade, že s nimi chcete pracovať, je potrebné ich zadať v tvare:\n" <<
			L"'názov_obce Okres názov_okresu_do_ktorého_spadá'\n" <<
			L"Jedná sa o obce: \n";

		for (structures::TableItem<std::wstring, data::TerritorialUnit*>* unit : *helperTitleExistTable) {
			std::wcout << unit->getKey() << L", ";
		}*/

		delete helperTitleExistTable2;
		delete helperTitleExistTable;
		
	}

	inline void DataLoader::loadAge()
	{
		std::wifstream ageData;
		ageData.open("vek.csv");
		ageData.imbue(std::locale("Slovak"));

		std::wstring line;
		std::wstring code;
		std::wstring age;
		std::wstring trash;

		std::getline(ageData, line); //prvy riadok precitaj = preskoc
		while (std::getline(ageData, line))   //precita cely riadok
		{
			std::wstringstream liner(line); // pracuje s riadkom
			std::getline(liner, code, L';'); //cislo kraja  
			std::getline(liner, trash, L';'); //nepotrebne

			//muzsky vek
			for (int i = 0; i < AGES; i++) {
				std::getline(liner, age, L';'); 				

				for(structures::TableItem<std::wstring, data::District*>* district : this->state_.getDistricts()) {
					std::wstring districtCode = district->accessData()->getNote().substr(8,2);

					if (!districtCode.compare(code.substr(3, 2))) {

						for (structures::TableItem<std::wstring, data::Region*>* region : district->accessData()->getRegions()) {
							std::wstring RegionCode = region->accessData()->getCode().substr(3, 3);

							if (!RegionCode.compare(code.substr(3, 3))) {

								for (structures::TableItem<std::wstring, data::Township*>* town : region->accessData()->getTowns()) {

									if (!town->accessData()->getCode().compare(code)) {
										town->accessData()->getAge().addYearsToManAge(i, std::stoi(age));

										TerritorialUnit* unit = &town->accessData()->getSuperiorUnit();

										while (unit != nullptr) {
											unit->getAge().addYearsToManAge(i, std::stoi(age));
											unit = &unit->getSuperiorUnit();
										}
									}
									
								}
							}
							
						}
						
					}
				}

			}	

			//Zensky vek
			for (int i = 0; i < AGES; i++) {
				std::getline(liner, age, L';');

				for (structures::TableItem<std::wstring, data::District*>* district : this->state_.getDistricts()) {
					std::wstring districtCode = district->accessData()->getNote().substr(8, 2);

					if (!districtCode.compare(code.substr(3, 2))) {

						for (structures::TableItem<std::wstring, data::Region*>* region : district->accessData()->getRegions()) {
							std::wstring RegionCode = region->accessData()->getCode().substr(3, 3);

							if (!RegionCode.compare(code.substr(3, 3))) {

								for (structures::TableItem<std::wstring, data::Township*>* town : region->accessData()->getTowns()) {

									if (!town->accessData()->getCode().compare(code)) {
										town->accessData()->getAge().addYearsToWomanAge(i, std::stoi(age));

										TerritorialUnit* unit = &town->accessData()->getSuperiorUnit();

										while (unit != nullptr) {
											unit->getAge().addYearsToWomanAge(i, std::stoi(age));
											unit = &unit->getSuperiorUnit();
										}
									}

								}
							}

						}

					}
				}

			}
		}
	}

	inline void DataLoader::loadEducation()
	{
		std::wifstream educationData;
		educationData.open("vzdelanie.csv");
		educationData.imbue(std::locale("Slovak"));

		std::wstring line;
		std::wstring code;
		std::wstring education;
		std::wstring trash;

		std::getline(educationData, line); //prvy riadok precitaj = preskoc
		while (std::getline(educationData, line))   //precita cely riadok
		{
			std::wstringstream liner(line); // pracuje s riadkom
			std::getline(liner, code, L';'); //cislo obce  
			std::getline(liner, trash, L';'); //nepotrebne

			for (int i = 0; i < EDUCATION; i++) {
				std::getline(liner, education, L';');

				for (structures::TableItem<std::wstring, data::District*>* district : this->state_.getDistricts()) {
					std::wstring districtCode = district->accessData()->getNote().substr(8, 2);

					if (!districtCode.compare(code.substr(3, 2))) {

						for (structures::TableItem<std::wstring, data::Region*>* region : district->accessData()->getRegions()) {
							std::wstring RegionCode = region->accessData()->getCode().substr(3, 3);

							if (!RegionCode.compare(code.substr(3, 3))) {

								for (structures::TableItem<std::wstring, data::Township*>* town : region->accessData()->getTowns()) {

									if (!town->accessData()->getCode().compare(code)) {
										town->accessData()->getEducation().addManToEducation(i, std::stoi(education));

										TerritorialUnit* unit = &town->accessData()->getSuperiorUnit();

										while (unit != nullptr) {
											unit->getEducation().addManToEducation(i, std::stoi(education));
											unit = &unit->getSuperiorUnit();
										}
									}

								}
							}

						}

					}
				}

			}
			
		}
	}

	inline void DataLoader::test()
	{
		int x = 7;

		std::wcout << L"SLOVENSKO: " << this->state_.getOfficialTitle()
			<< " - " << this->state_.getCode() << " - " << this->state_.getNote() << " - " << this->state_.getAge().getManAge(x)
			<< " - " << this->state_.getAge().getWomanAge(x) << " - " << this->state_.getEducation().getEducation(x)
			<< L"\n";
		
		for (structures::TableItem<std::wstring, data::District*>* district : this->state_.getDistricts()) {

					std::wcout << L"KRAJ: " << district->accessData()->getOfficialTitle()
						<< " - " << district->accessData()->getCode() << " - " << district->accessData()->getNote() <<
						" - " << district->accessData()->getAge().getManAge(x) <<
						" - " << district->accessData()->getAge().getWomanAge(x) << " - " 
						<< district->accessData()->getEducation().getEducation(x) << L"\n";

					for (structures::TableItem<std::wstring, data::Region*>* region : district->accessData()->getRegions()) {

						std::wcout << L"------Okres: " << region->accessData()->getOfficialTitle()
							<< " - " << region->accessData()->getCode() << " - " << region->accessData()->getNote() <<
							" - " << region->accessData()->getAge().getManAge(x) <<
							" - " << region->accessData()->getAge().getWomanAge(x) << " - "
							<< region->accessData()->getEducation().getEducation(x) <<  L"\n";

						for (structures::TableItem<std::wstring, data::Township*>* town : region->accessData()->getTowns()) {

							std::wcout << L"----------Obec: " << town->accessData()->getOfficialTitle()
								<< " - " << town->accessData()->getCode() << " - " << town->accessData()->getNote() <<
								" - " << town->accessData()->getAge().getManAge(x) <<
								" - " << town->accessData()->getAge().getWomanAge(x) << " - "
								<< town->accessData()->getEducation().getEducation(x) << L"\n";
						}

					}
				}
	}

	inline DataLoader::~DataLoader()
	{
	}


}


