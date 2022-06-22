#pragma once
#define EDUCATIONS 8
#include "structures/list/array_list.h"

namespace data
{

	class Education
	{
	public:

		Education();
		~Education();
		int& getEducation(int education);
		int getEducationInRange(int startEd, int endEd);
		void addManToEducation(int education, int man);

	private:
	private:
		structures::Array<int>* list_;
	};

	inline Education::Education() :
		list_(new structures::Array<int>(EDUCATIONS))
	{
	}

	inline Education::~Education()
	{
		delete this->list_;
	}

	inline int& Education::getEducation(int education)
	{
		return this->list_->at(education);
	}

	inline int Education::getEducationInRange(int startEd, int endEd)
	{
		int sumOfEd = 0;
		for (int i = startEd; i <= endEd; i++) {
			sumOfEd += this->list_->at(i);
		}
		return sumOfEd;
	}

	inline void Education::addManToEducation(int education, int man)
	{
		this->list_->at(education) += man;
	}

}


