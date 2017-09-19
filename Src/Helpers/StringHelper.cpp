#include "stdafx.hpp"
#include "StringHelper.hpp"

using namespace Kaleid::Helpers;

std::vector<std::string> StringHelper::Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	StringHelper::Split(s, delim, std::back_inserter(elems));
	return elems;
}