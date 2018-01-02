#pragma once

#include "Kaleid.Shared\Common.hpp"
#include <sstream>
#include <vector>

namespace Kaleid::Helpers
{
	enum class SplitArg
	{
		NoWhitespace,
		Whitespace
	};

	class KALEID_HELPERS_API StringHelper sealed
	{
	public:
		static bool BeginsWith(const std::string& input, const std::string& match);
		static bool EndsWith(const std::string& input, const std::string& match);
		static std::vector<std::string> Split(const std::string &s, char delim);
		static std::string TrimLeading(const std::string& s);
	private:
		template<typename T>
		static inline void Split(const std::string &s, char delim, T result, SplitArg arg = SplitArg::NoWhitespace)
		{
			std::stringstream ss;
			ss.str(s);
			std::string item;

			while (std::getline(ss, item, delim))
			{
				if (arg == SplitArg::Whitespace || (arg == SplitArg::NoWhitespace && item.length() != 0))
					*(result++) = item;
			}
		}
	};
}