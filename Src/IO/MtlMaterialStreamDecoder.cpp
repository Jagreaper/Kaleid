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

bool TryReadSpecularExponent(const std::string& line, MaterialInfo& output)
{
	output.SpecularExponent = std::stof(StringHelper::Split(line, ' ')[1]);
	return true;
}

bool TryReadOpticalDensity(const std::string& line, MaterialInfo& output)
{
	output.OpticalDensity = std::stof(StringHelper::Split(line, ' ')[1]);
	return true;
}

bool TryReadTransparency(const std::string& line, MaterialInfo& output)
{
	output.Transparency = std::stof(StringHelper::Split(line, ' ')[1]);
	return true;
}

bool TryReadTransparencyInverted(const std::string& line, MaterialInfo& output)
{
	output.Transparency = 1.0f - std::stof(StringHelper::Split(line, ' ')[1]);
	return true;
}

bool TryReadTransmissionFilter(const std::string& line, MaterialInfo& output)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	output.TransmissionFilter = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadIlluminationModel(const std::string& line, MaterialInfo& output)
{
	output.IlluminationModel = (unsigned char)std::stoi(StringHelper::Split(line, ' ')[1]);
	return true;
}

bool TryReadAmbientColor(const std::string& line, MaterialInfo& output)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	output.AmbientColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadDiffuseColor(const std::string& line, MaterialInfo& output)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	output.DiffuseColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadSpecularColor(const std::string& line, MaterialInfo& output)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	output.SpecularColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadEmmisiveColor(const std::string& line, MaterialInfo& output)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	output.EmissiveColor = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
	return true;
}

bool TryReadLine(const std::string& line, MaterialInfo& output)
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

	if (StringHelper::BeginsWith(line, std::string("map_Ka ")))
	{
		output.AmbientTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("map_Kd ")))
	{
		output.DiffuseTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("map_Ks ")))
	{
		output.SpecularTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("map_Ke ")))
	{
		output.EmissiveTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("map_d ")))
	{
		output.AlphaTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("map_bump ")) || StringHelper::BeginsWith(line, std::string("bump ")))
	{
		output.BumpMapTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("disp ")))
	{
		output.DisplacementTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	if (StringHelper::BeginsWith(line, std::string("decal ")))
	{
		output.StencilDecalTexture = StringHelper::Split(line, ' ')[1];
		return true;
	}

	return true;
}

bool MtlMaterialStreamDecoder::TryDecode(std::istream& source, std::vector<Kaleid::Game::MaterialInfo>* output, void* arg)
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

			this->_cMaterial = MaterialInfo();
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