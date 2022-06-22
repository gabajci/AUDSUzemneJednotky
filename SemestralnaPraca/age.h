#pragma once

#define AGES 101
#include "structures/list/array_list.h"

namespace data
{
	class Age
	{
	public:
		Age();
		~Age();
		int& getManAge(int year);
		int getManAgeInRange(int startYear, int endYear);
		void addYearsToManAge(int years, int sum);
		int getManInUnit();
		int& getWomanAge(int year);
		int getWomanAgeInRange(int startYear, int endYear);
		void addYearsToWomanAge(int years, int sum);

	private:
		structures::Array<int>* listMan_;
		structures::Array<int>* listWoman_;
		int numberOfManInUnit_ = 0;
	};

	inline Age::Age() :
		listMan_(new structures::Array<int>(AGES)), // 0-101 - muzi vek 0 - 100
		listWoman_(new structures::Array<int>(AGES)) // vek zeny 0 - 100
	{													
	}

	inline Age::~Age()
	{
		delete this->listWoman_;
		delete this->listMan_;
	}

	inline int& Age::getManAge(int year)
	{
		return this->listMan_->at(year);
	}

	inline int Age::getManAgeInRange(int startYear, int endYear)
	{
		int sumOfYears = 0;
		for (int i = startYear; i <= endYear; i++) {
			sumOfYears += this->listMan_->at(i);
		}
		return sumOfYears;
	}

	inline void Age::addYearsToManAge(int years, int sum)
	{
		this->listMan_->at(years)+= sum;
		this->numberOfManInUnit_ += sum;
	}

	inline int Age::getManInUnit()
	{
		return this->numberOfManInUnit_;
	}

	inline int& Age::getWomanAge(int year)
	{

		return this->listWoman_->at(year);
	}

	inline int Age::getWomanAgeInRange(int startYear, int endYear)
	{
		int sumOfYears = 0;
		for (int i = startYear; i <= endYear; i++) {
			sumOfYears += this->listWoman_->at(i);
		}
		return sumOfYears;
	}

	inline void Age::addYearsToWomanAge(int years, int sum)
	{
		this->listWoman_->at(years) += sum;
		this->numberOfManInUnit_ += sum;
	}

}


