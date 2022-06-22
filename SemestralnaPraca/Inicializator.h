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

		std::wcout << L"Na��tavam d�ta..\n";
		data::DataLoader* dataLoader = new data::DataLoader(*slovakia);
		std::wcout << L"D�ta �spe�ne na��tan�.\n";

		bool end = false;
		while (!end) {
			std::wcout << L"\n\n-----HLAVN� MENU-----\n\n";
			
			std::wstring choice;
			std::wcout << L"Vyh�adanie �zemnej jednotky pod�a n�zvu - 1\n";
			std::wcout << L"Filtrovanie d�t / Triedenie d�t / Vyh�adanie najv��ej - najmen�ej vekovej skupiny - 2\n";
			std::getline(std::wcin, choice, L'\n');
			if (choice == L"1") {
				filtering::FilterByName filterByName(*slovakia);
			}
			else if (choice == L"2") {
				filtering::MainFilter mainFilter(*slovakia);	
				structures::SortedSequenceTable<std::wstring, data::TerritorialUnit*>& filteredData = mainFilter.menu();
				std::wcout << L"\n\nPou�i� viacej filtrov - 1\n";
				std::wcout << L"Triedenie d�t - 2\n";
				std::wcout << L"Vyh�ada� najv��iu / najmen�iu vekov� skupinu - 3\n";
				std::wcout << L"Pre pokra�ovanie stla�te �ubovoln� znak\n";
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


			std::wcout << L"Prajete si n�vrat do menu?(stla�te 1 pre n�vrat, �ubovoln� kl�vesu pre ukon�enie aplik�cie): ";
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




