#pragma once

#include "Kaleid.Math\Vector.hpp"
#include <string>

namespace Kaleid::Graphics
{
	class TextureBase;

	struct Material
	{
		std::string Name;
		Kaleid::Math::Vector3F AmbientColor; // Ka
		Kaleid::Math::Vector3F DiffuseColor; // Kd
		Kaleid::Math::Vector3F SpecularColor; // Ks
		Kaleid::Math::Vector3F EmissiveColor; // Ke
		float Transparency; // d or inverted Tr
		float SpecularExponent; // Ns Shininess
		float OpticalDensity; // Ni 
		Kaleid::Math::Vector3F TransmissionFilter; // Tf
		unsigned char IlluminationModel; // Illum

		TextureBase* AmbientTexture;
		TextureBase* DiffuseTexture;
		TextureBase* SpecularTexture;
		TextureBase* EmissiveTexture;
		TextureBase* AlphaTexture;
		TextureBase* BumpMapTexture;
		TextureBase* DisplacementTexture;
		TextureBase* StencilDecalTexture;
	};

	struct MaterialInfo
	{
		std::string Name;
		Kaleid::Math::Vector3F AmbientColor; // Ka
		Kaleid::Math::Vector3F DiffuseColor; // Kd
		Kaleid::Math::Vector3F SpecularColor; // Ks
		Kaleid::Math::Vector3F EmissiveColor; // Ke
		float Transparency; // d or inverted Tr
		float SpecularExponent; // Ns Shininess
		float OpticalDensity; // Ni 
		Kaleid::Math::Vector3F TransmissionFilter; // Tf
		unsigned char IlluminationModel; // Illum

		std::string AmbientTexture;
		std::string DiffuseTexture;
		std::string SpecularTexture;
		std::string EmissiveTexture;
		std::string AlphaTexture;
		std::string BumpMapTexture;
		std::string DisplacementTexture;
		std::string StencilDecalTexture;

		inline Material CreateMaterial() const
		{
			Material material;
			material.Name = this->Name;
			material.AmbientColor = this->AmbientColor;
			material.DiffuseColor = this->DiffuseColor;
			material.SpecularColor = this->SpecularColor;
			material.EmissiveColor = this->EmissiveColor;
			material.Transparency = this->Transparency;
			material.SpecularExponent = this->SpecularExponent;
			material.OpticalDensity = this->OpticalDensity;
			material.TransmissionFilter = this->TransmissionFilter;
			material.IlluminationModel = this->IlluminationModel;
			return material;
		}
	};
}