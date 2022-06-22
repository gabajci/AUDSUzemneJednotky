#pragma once
#include "filterWithCriterion.h"
#include "criterion.h"

namespace filter
{
	template<typename T>
	class FilterRange : public FilterWithCriterion<T>
	{
	public:
		FilterRange(T& valueFrom,T& valueTo, criterion::Criterion<T>* criterion);
		bool belongsTo(data::TerritorialUnit& unit) override;
		std::wstring representCriterion(data::TerritorialUnit& unit) override;
	private:
		T valueFrom_;
		T valueTo_;
	};

	template<typename T>
	inline FilterRange<T>::FilterRange(T& valueFrom, T& valueTo, criterion::Criterion<T>* criterion) : FilterWithCriterion<T>(criterion)
	{
		this->valueFrom_ = valueFrom;
		this->valueTo_ = valueTo;
	}

	template<typename T>
	inline bool FilterRange<T>::belongsTo(data::TerritorialUnit& unit)
	{
		T criterionValue = this->criterion_->rate(unit);
		return criterionValue >= valueFrom_ && criterionValue <= this->valueTo_;
	}

	template<typename T>
	inline std::wstring FilterRange<T>::representCriterion(data::TerritorialUnit& unit)
	{
		return this->criterion_->toString(unit);
	}

}


