#pragma once
#include "age.h"
#include "structures/table/sorted_sequence_table.h"
#include "district.h"
#include "territorialUnit.h"

namespace data
{
	class State : public TerritorialUnit
	{
	public:
		State(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit);
		~State();
		void clear();
		structures::SortedSequenceTable<std::wstring, District*>& getDistricts();
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& getRegions();
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& getTowns();
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& getAllTUnits(); 
	private:
		structures::SortedSequenceTable<std::wstring, District*>* districts_;
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* regions_;
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* towns_;
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* allTUnits_;
	};


	inline State::State(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit) :
		TerritorialUnit(officialTitle, code,note,territorialUnit),
		districts_(new structures::SortedSequenceTable<std::wstring, District*>()),
		allTUnits_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>()),
		regions_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>()),
		towns_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>())

	{
	}

	inline State::~State()
	{
		this->clear();
		delete this->districts_;
		delete this->allTUnits_;
		delete this->towns_;
		delete this->regions_;
	}

	inline void State::clear()
	{
		for (structures::TableItem<std::wstring, data::District*>* item : *this->districts_) {
			delete item->accessData();
		}

	}

	inline structures::SortedSequenceTable<std::wstring, District*>& State::getDistricts()
	{
		return *this->districts_;
	}

	inline structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& State::getRegions()
	{
		return *this->regions_;
	}

	inline structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& State::getTowns()
	{
		return *this->towns_;
	}

	inline structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& State::getAllTUnits()
	{
		return *this->allTUnits_;
	}


}


