#pragma once
#include "age.h"
#include "structures/table/sorted_sequence_table.h"
#include "township.h"
#include "territorialUnit.h"

namespace data
{
	class Region : public TerritorialUnit
	{
	public:
		Region(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit);
		~Region();
		void clear();

		structures::SortedSequenceTable<std::wstring, Township*>& getTowns();
	private:
		structures::SortedSequenceTable<std::wstring, Township*>* towns_;
	};

	inline Region::Region(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit) :
		TerritorialUnit(officialTitle,code,note,territorialUnit),
		towns_(new structures::SortedSequenceTable<std::wstring, Township*>())
	{
	}

	inline Region::~Region()
	{
		this->clear();
		delete this->towns_;
	}

	inline void Region::clear()
	{
		for (structures::TableItem<std::wstring, data::Township*>* item : *this->towns_) {
			delete item->accessData();
		}

	}

	inline structures::SortedSequenceTable<std::wstring, Township*>& Region::getTowns()
	{
		return *this->towns_;
	}


}


