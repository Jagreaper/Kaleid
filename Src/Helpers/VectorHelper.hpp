#pragma once

#include "stdafx.hpp"
#include <vector>

namespace Kaleid::Helpers
{
	class KALEID_HELPERS_API VectorHelper sealed
	{
	public:
		template<class Type>
		static inline void AddRange(std::vector<Type>* vector, const std::vector<Type>* items)
		{
			for (unsigned int index = 0; index < (unsigned int)items->size(); index++)
				vector->push_back(items->at(index));
		}

		template<class Type>
		static inline void AddRange(std::vector<Type>* vector, const std::vector<Type>& items)
		{
			for (unsigned int index = 0; index < (unsigned int)items.size(); index++)
				vector->push_back(items[index]);
		}

		template<class Type>
		static inline void AddRange(std::vector<Type>& vector, const std::vector<Type>* items)
		{
			for (unsigned int index = 0; index < (unsigned int)items->size(); index++)
				vector.push_back(items->at(index));
		}

		template<class Type>
		static inline void AddRange(std::vector<Type>& vector, const std::vector<Type>& items)
		{
			for (unsigned int index = 0; index < (unsigned int)items.size(); index++)
				vector.push_back(items[index]);
		}

		template<class Type>
		static inline void RemoveItem(std::vector<Type>* vector, Type& item)
		{
			auto index = std::find(vector->begin(), vector->end(), item);
			if (index != vector->end())
				vector->erase(index);
		}
	};
}