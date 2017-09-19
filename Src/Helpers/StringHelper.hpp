#include "stdafx.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace Kaleid::Helpers
{
	class KALEID_HELPERS_API StringHelper sealed
	{
	public:
		template<class TContainer>
		static inline bool BeginsWith(const TContainer& input, const TContainer match)
		{
			return input.size() >= match.size() && equal(match.begin(), match.end(), input.begin());
		}
		
		template<typename Out>
		static inline void Split(const std::string &s, char delim, Out result)
		{
			std::stringstream ss;
			ss.str(s);
			std::string item;

			while (std::getline(ss, item, delim))
				*(result++) = item;
		}

		static std::vector<std::string> Split(const std::string &s, char delim);
	};
}