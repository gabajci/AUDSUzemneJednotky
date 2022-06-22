#pragma once
#include "age.h"
#include "state.h"
#include "dataLoader.h"
#include "filterByName.h"
#include "customFilter.h"
#include "mainFilter.h"
#include "finderMaxMin.h"
#include "sorter.h"
#include <iostream>


	class Inicializator 
	{
	public:
		Inicializator();
		void menu();
		~Inicializator();
	};


	inline Inicializator::Inicializator()
	{
		this->menu();
	}

	inline void Inicializator::menu()
	{
		data::State* slovakia = new data::State(L"Slovakia", L"1", L"1", nullptr);

		std::wcout << L"Naèítavam dáta..\n";
		data::DataLoader* dataLoader = new data::DataLoader(*slovakia);
		std::wcout << L"Dáta úspešne naèítané.\n";

		bool end = false;
		while (!end) {
			std::wcout << L"\n\n-----HLAVNÉ MENU-----\n\n";
			
			std::wstring choice;
			std::wcout << L"Vyh¾adanie územnej jednotky pod¾a názvu - 1\n";
			std::wcout << L"Filtrovanie dát / Triedenie dát / Vyh¾adanie najväèšej - najmenšej vekovej skupiny - 2\n";
			std::getline(std::wcin, choice, L'\n');
			if (choice == L"1") {
				filtering::FilterByName filterByName(*slovakia);
			}
			else if (choice == L"2") {
				filtering::MainFilter mainFilter(*slovakia);	
				structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& filteredData = mainFilter.menu();
				std::wcout << L"\n\nPouži viacej filtrov - 1\n";
				std::wcout << L"Triedenie dát - 2\n";
				std::wcout << L"Vyh¾ada najväèšiu / najmenšiu vekovú skupinu - 3\n";
				std::wcout << L"Pre pokraèovanie stlaète ¾ubovolný znak\n";
				std::getline(std::wcin, choice, L'\n');
				if (choice == L"1") {
					filtering::CustomFilter customFilter(filteredData);
				} else if(choice == L"2") {
					filtering::Sorter sorter(filteredData);
				}
				else if (choice == L"3") {
					filtering::FinderMaxMin findMaxMin(filteredData);
				}
				
			}


			std::wcout << L"Prajete si návrat do menu?(stlaète 1 pre návrat, ¾ubovolnú klávesu pre ukonèenie aplikácie): ";
			std::getline(std::wcin, choice, L'\n');
			if (choice != L"1") {
				end = true;
			}
		}

		delete dataLoader;
		delete slovakia;
		
	}

	inline Inicializator::~Inicializator()
	{
		
	}




