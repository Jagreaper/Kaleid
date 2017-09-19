#include "stdafx.hpp"
#include "StringHelper.hpp"

using namespace Kaleid::Helpers;

bool StringHelper::BeginsWith(const std::string& input, const std::string& match)
{
	return input.size() >= match.size() && std::equal(match.begin(), match.end(), input.begin());
}

bool StringHelper::EndsWith(const std::string& input, const std::string& match)
{
	return match.size() <= input.size() && std::equal(match.rbegin(), match.rend(), input.rbegin());
}

std::vector<std::string> StringHelper::Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	StringHelper::Split(s, delim, std::back_inserter(elems));
	return elems;
}