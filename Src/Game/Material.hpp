#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"
#include <string>

API_BEGIN
namespace Kaleid::Game
{
	struct Material
	{
		std::string Name;
		float SpecularExponent; // Ns Shininess
		float OpticalDensity; // Ni 
		float Transparency; // d or inverted Tr
		Kaleid::Math::Vector3F TransmissionFilter; // Tf
	    unsigned char IlluminationModel; // Illum
		Kaleid::Math::Vector3F AmbientColor; // Ka
		Kaleid::Math::Vector3F DiffuseColor; // Kd
		Kaleid::Math::Vector3F SpecularColor; // Ks
		Kaleid::Math::Vector3F EmissiveColor; // Ke
		// TODO: DiffuseTexture
		// TODO: NormalTexture
	};
}
API_END