#pragma once

#include "stdafx.hpp"
#include <sstream>
#include <vector>

namespace Kaleid::Helpers
{
	class KALEID_HELPERS_API StringHelper sealed
	{
	public:
		static bool BeginsWith(const std::string& input, const std::string& match);
		static bool EndsWith(const std::string& input, const std::string& match);
		static std::vector<std::string> Split(const std::string &s, char delim);
	private:
		template<typename Out>
		static inline void Split(const std::string &s, char delim, Out result)
		{
			std::stringstream ss;
			ss.str(s);
			std::string item;

			while (std::getline(ss, item, delim))
				*(result++) = item;
		}
	};
}