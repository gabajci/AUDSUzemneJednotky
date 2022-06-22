#pragma once
#include "territorialUnit.h"
#include "criterion.h"
#include "structures/table/unsorted_sequence_table.h"

namespace filtering
{
	template<typename T>
	class QuickSort
	{
	public:
		void sort(criterion::Criterion<T>* criterion,structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>& data);
	private:
		void quick(int min, int max, structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>& table, criterion::Criterion<T>* criterion);
	};

	template<typename T>
	inline void QuickSort<T>::sort(criterion::Criterion<T>* criterion, structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>& data)
	{
		if (data.size() != 0) {
			quick(0, data.size() - 1, data, criterion);
		}
		else {
			std::wcout << L"\nTabu¾ka neobsahuje žiadne dáta na utriedenie.\n";
		}
	}

	template<typename T>
	inline void QuickSort<T>::quick(int min, int max, structures::UnsortedSequenceTable<std::wstring, data::TerritorialUnit*>& table, criterion::Criterion<T>* criterion)
	{
		T pivot = criterion->rate(*(table.getItemAtIndex((min + max) / 2).accessData()));
		int lavy = min;
		int pravy = max;

		do
		{			
			while (criterion->rate(*(table.getItemAtIndex(lavy).accessData())) > pivot)
			{
				lavy++;
			}

			while (criterion->rate(*(table.getItemAtIndex(pravy).accessData())) < pivot)
			{
				pravy--;
			}

			if (lavy <= pravy)
			{
				table.swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);

		if (min < pravy)
		{
			quick(min, pravy, table, criterion);
		}

		if (lavy < max)
		{
			quick(lavy, max, table, criterion);
		}
	}

}


