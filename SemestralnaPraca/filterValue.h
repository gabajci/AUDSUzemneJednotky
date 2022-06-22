#pragma once
#include "filterWithCriterion.h"
#include "criterion.h"

namespace filter
{
	template<typename T>
	class FilterValue : public FilterWithCriterion<T>
	{
	public:
		FilterValue(T& value,criterion::Criterion<T>* criterion);
		bool belongsTo(data::TerritorialUnit& unit) override;
		std::wstring representCriterion(data::TerritorialUnit& unit) override;
	private:
		T value_;
	};

	template<typename T>
	inline FilterValue<T>::FilterValue(T& value, criterion::Criterion<T>* criterion) : FilterWithCriterion<T>(criterion)
	{
		this->value_ = value;
	}

	template<typename T>
	inline bool FilterValue<T>::belongsTo(data::TerritorialUnit& unit)
	{
		return this->criterion_->rate(unit) == value_;
	}

	template<typename T>
	inline std::wstring FilterValue<T>::representCriterion(data::TerritorialUnit& unit)
	{
		return this->criterion_->toString(unit);
	}

}


