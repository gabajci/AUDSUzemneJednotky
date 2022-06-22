#pragma once
#include "age.h"
#include "structures/table/sorted_sequence_table.h"
#include "region.h"
#include "territorialUnit.h"

namespace data
{
	class District : public TerritorialUnit
	{
	public:
		District(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit);
		~District();
		void clear();

		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& getTowns();
		structures::SortedSequenceTable<std::wstring, Region*>& getRegions();
	private:
		structures::SortedSequenceTable<std::wstring, Region*>* regions_;
		structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* towns_;
	};


	inline District::District(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit) :
		TerritorialUnit(officialTitle,code,note,territorialUnit),
		regions_(new structures::SortedSequenceTable<std::wstring, Region*>()),
		towns_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>())
	{
	}

	inline District::~District()
	{
		this->clear();
		delete this->regions_;
		delete this->towns_;
	}

	inline void District::clear()
	{
		for (structures::TableItem<std::wstring, data::Region*>* item : *this->regions_) {
			delete item->accessData();
		}

	}

	inline structures::SortedSequenceTable<std::wstring, Region*>& District::getRegions()
	{
		return *this->regions_;
	}

	inline structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& District::getTowns()
	{
		return *this->towns_;
	}


}


