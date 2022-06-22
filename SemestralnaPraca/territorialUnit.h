#pragma once

#include "age.h"
#include "education.h"
#include "structures/table/sorted_sequence_table.h"


namespace data
{
	class TerritorialUnit
	{
	public:
		TerritorialUnit(std::wstring officialTitle, std::wstring code, std::wstring note,TerritorialUnit* territorialUnit);
		~TerritorialUnit();

		Age& getAge();
		Education& getEducation();
		TerritorialUnit& getSuperiorUnit();
		std::wstring& getOfficialTitle();
		void setOfficialTitle(std::wstring newTitle);
		std::wstring& getCode();
		std::wstring& getNote();
	private:
		Age* age_;
		Education* education_;
		TerritorialUnit& territorialUnit_;
		std::wstring officialTitle_;
		std::wstring code_;
		std::wstring note_;
	};

	inline TerritorialUnit::TerritorialUnit(std::wstring officialTitle, std::wstring code, std::wstring note, TerritorialUnit* territorialUnit) :
		officialTitle_(officialTitle), code_(code), age_(new Age), education_(new Education), note_(note),
		territorialUnit_(*territorialUnit)
		
	{		
	}

	inline TerritorialUnit::~TerritorialUnit()
	{
		delete this->age_;
		delete this->education_;
	}
	

	inline Age& TerritorialUnit::getAge()
	{
		return *this->age_;
	}

	inline Education& TerritorialUnit::getEducation()
	{
		return *this->education_;
	}

	inline TerritorialUnit& TerritorialUnit::getSuperiorUnit()
	{
		return this->territorialUnit_;
	}


	inline std::wstring& TerritorialUnit::getOfficialTitle()
	{
		return this->officialTitle_;
	}

	inline void TerritorialUnit::setOfficialTitle(std::wstring newTitle)
	{
		this->officialTitle_ = newTitle;
	}


	inline std::wstring& TerritorialUnit::getCode()
	{
		return this->code_;
	}

	inline std::wstring& TerritorialUnit::getNote()
	{
		return this->note_;
	}


}


