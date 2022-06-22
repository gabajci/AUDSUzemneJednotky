#pragma once
#include "territorialUnit.h"
#include "criterion.h"
#include "filter.h"

namespace filter
{
	template<typename T>
	class FilterWithCriterion : public Filter
	{
	public:
		FilterWithCriterion(criterion::Criterion<T>* criterion);
		virtual ~FilterWithCriterion();
		virtual bool belongsTo(data::TerritorialUnit& unit) = 0;
		virtual std::wstring representCriterion(data::TerritorialUnit& unit) = 0;
	protected:
		criterion::Criterion<T>* criterion_;
	};

	template<typename T>
	inline FilterWithCriterion<T>::FilterWithCriterion(criterion::Criterion<T>* criterion) : Filter()
	{
		criterion_ = criterion;
	}

	template<typename T>
	inline FilterWithCriterion<T>::~FilterWithCriterion()
	{
		delete this->criterion_; 
	}

}


