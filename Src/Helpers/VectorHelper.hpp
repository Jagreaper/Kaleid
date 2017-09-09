#include "stdafx.hpp"
#include <vector>

namespace Kaleid::Helpers
{
	class KALEID_HELPERS_API VectorHelper
	{
	public:
		template<class Type>
		static inline void RemoveItem(std::vector<Type>* vector, Type item)
		{
			auto index = std::find(vector->begin(), vector->end(), item);
			if (index != vector->end())
				vector->erase(index);
		}
	};
}