#include "stdafx.hpp"
#include "MtlMaterialStreamDecoder.hpp"
#include "StringHelper.hpp"
#include "VectorHelper.hpp"
#include "Material.hpp"
#include "Vector.hpp"
#include <string>
#include <vector>

using namespace Kaleid::IO;
using namespace Kaleid::Game;
using namespace Kaleid::Helpers;
using namespace Kaleid::Math;

bool TryReadSpecularExponent(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.SpecularExponent = std::stof(strings[1]);
	return true;
}

bool TryReadOpticalDensity(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.OpticalDensity = std::stof(strings[1]);
	return true;
}

bool TryReadTransparency(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.Transparency = std::stof(strings[1]);
	return true;
}

bool TryReadTransparencyInverted(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.Transparency = 1.0f - std::stof(strings[1]);
	return true;
}

bool TryReadTransmissionFilter(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.TransmissionFilter = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadIlluminationModel(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.IlluminationModel = (unsigned char)std::stoi(strings[1]);
	return true;
}

bool TryReadAmbientColor(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.AmbientColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadDiffuseColor(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.DiffuseColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadSpecularColor(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.SpecularColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadEmmisiveColor(const std::string& line, Material& output)
{
	std::vector<std::string> strings = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; });
	output.EmissiveColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadLine(const std::string& line, Kaleid::Game::Material& output)
{
	if (StringHelper::BeginsWith(line, std::string("newmtl ")))
		return TryReadSpecularExponent(line, output);

	if (StringHelper::BeginsWith(line, std::string("Ns ")))
		return TryReadSpecularExponent(line, output);

	if (StringHelper::BeginsWith(line, std::string("Ni ")))
		return TryReadOpticalDensity(line, output);

	if (StringHelper::BeginsWith(line, std::string("d ")))
		return TryReadTransparency(line, output);

	if (StringHelper::BeginsWith(line, std::string("Tr ")))
		return TryReadTransparencyInverted(line, output);

	if (StringHelper::BeginsWith(line, std::string("Tf ")))
		return TryReadTransmissionFilter(line, output);

	if (StringHelper::BeginsWith(line, std::string("illum ")))
		return TryReadIlluminationModel(line, output);

	if (StringHelper::BeginsWith(line, std::string("Ka ")))
		return TryReadAmbientColor(line, output);

	if (StringHelper::BeginsWith(line, std::string("Kd ")))
		return TryReadDiffuseColor(line, output);

	if (StringHelper::BeginsWith(line, std::string("Ks ")))
		return TryReadSpecularColor (line, output);

	if (StringHelper::BeginsWith(line, std::string("Ke ")))
		return TryReadEmmisiveColor(line, output);

	return true;
}

bool MtlMaterialStreamDecoder::TryDecode(std::istream& source, std::vector<Kaleid::Game::Material>* output, void* arg)
{
	std::string line;
	bool mtl_exists = false;
	while (std::getline(source, line))
	{
		line = StringHelper::TrimLeading(line);
		if (StringHelper::BeginsWith(line, std::string("newmtl ")))
		{
			if (mtl_exists)
				output->push_back(this->_cMaterial);
			else
				mtl_exists = true;

			this->_cMaterial = Material();
			this->_cMaterial.Name = VectorHelper::Where(StringHelper::Split(line, ' '), [&](std::string s) -> bool { return s.length() != 0; })[1];
		}
		else if (!TryReadLine(line, this->_cMaterial))
		{
			std::string msg("Could not read line:\n");
			msg += line;
			throw std::runtime_error(msg);
		}
	}

	output->push_back(this->_cMaterial);
	return true;
}