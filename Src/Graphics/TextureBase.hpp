#pragma once
#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	enum class DepthStencilTextureMode
	{
		DepthComponent = 0x1902,
	};

	enum class TextureCompareFunc
	{
		LessEqual = 0x0203,
		GreaterEqual = 0x0206,
		Less = 0x0201,
		Greater = 0x0204,
		Equal = 0x0202,
		NotEqual = 0x0205,
		Always = 0x0207,
		Never = 0x0200,
	};

	enum class TextureCompareMode
	{
		CompareRefToTexture = 0x884E,
		None = 0,
	};

	enum class TextureMinFilter
	{
		Nearest = 0x2600,
		Linear = 0x2601,
		NearestMipmapNearest = 0x2700,
		LinearMipmapNearest = 0x2701,
		NearestMipmapLinearR = 0x2702,
		LinearMipmapLinear = 0x2703,
	};

	enum class TextureMagFilter
	{
		Nearest = 0x2600,
		Linear = 0x2601,
	};

	enum class TextureSwizzle
	{
		Red = 0x1903,
		Green = 0x1904,
		Blue = 0x1905,
		Alpha = 0x1906,
		One = 1,
		Zero = 0,
	};

	enum class TextureWrap
	{
		ClampToEdge = 0x812F,
		ClampToborder = 0x812D,
		MirroredRepeat = 0x8370,
		Repeat = 0x2901,
		MirrorClampToEdge = 0x8743,
	};

	enum class TextureParameter
	{
		DepthStencilTextureMode = 0x90EA,
		BaseLevel = 0x813C,

		CompareMode = 0x884C,
		CompareFunc = 0x884D,

		LodBias = 0x8501,

		MagFilter = 0x2800,
		MinFilter = 0x2801,

		MinLod = 0x813A,
		MaxLod = 0x813B,
		MaxLevel = 0x813D,

		SwizzleR = 0x8E42,
		SwizzleG = 0x8E43,
		SwizzleB = 0x8E44,
		SwizzleA = 0x8E45,

		WrapS = 0x2802,
		WrapT = 0x2803,
		WrapR = 0x8072,
	};

	enum class InternalTextureFormat
	{
		DepthComponent = 0x1902,
		DepthStencil = 0x84F9,
		Red = 0x1903,
		Rg = 0x8227,
		Rgb = 0x1907,
		Rgba = 0x1908,


		R8 = 0x8229,
		Rg8 = 0x822B,
		Rgb8 = 0x8051,
		Rgba8 = 0x8058,

		R16 = 0x822A,
		Rg16 = 0x822C,
		Rgb16 = 0x8054,
		Rgba16 = 0x805B,

		R8Snorm = 0x8F94,
		Rb8Snorm = 0x8F95,
		Rbg8Snorm = 0x8F96,
		Rgba8Snorm = 0x8F97,

		R16Snorm = 0x8F98,
		Rg16Snorm = 0x8F99,
		Rgb16Snorm = 0x8F9A,
		Rgba16Snorm = 0x8F9B,

		R3G3B2 = 0x2A10,

		Rgb4 = 0x804F,
		Rgb5 = 0x8050,
		Rgb10 = 0x8052,
		Rgb12 = 0x8053,
		
		Rgba2 = 0x8055,
		Rgba4 = 0x8056,
		Rgba12 = 0x805A,

		RGB5A1 = 0x8057,

		Rgb10A2 = 0x8059,
		Rgb10A2UI = 0x906F,

		Srgb8 = 0x8C41,
		Srgb8A8 = 0x8C43,

		R16F = 0x822D,
		Rg16F = 0x822F,
		Rgb16F = 0x881B,
		Rgba16F = 0x881A,

		R32F = 0x822E,
		Rg32F = 0x8230,
		Rgb32F = 0x8815,
		Rgba32F = 0x8814,

		R11G11B10F = 0x8C3A,
		Rgb9E5 = 0x8C3D,

		R8I = 0x8231,
		R8UI = 0x8232,
		R16I = 0x8233,
		R16UI = 0x8234,
		R32I = 0x8235,
		R32UI = 0x8236,
		Rg8I = 0x8237,
		Rg8UI = 0x8238,
		Rg16I = 0x8239,
		Rg16UI = 0x823A,
		Rg32I = 0x823B,
		Rg32UI = 0x823C,

		Rgba32UI = 0x8D70,
		Rgb32UI = 0x8D71,
		Rgba16UI = 0x8D76,
		Rgb16UI = 0x8D77,
		Rgba8UI = 0x8D7C,
		Rgb8UI = 0x8D7D,
		Rgba32I = 0x8D82,
		Rgb32I = 0x8D83,
		Rgba16I = 0x8D88,
		Rgb16I = 0x8D89,
		Rgba8I = 0x8D8E,
		Rgb8I = 0x8D8F,

		CompressedRed = 0x8225,
		CompressedRg = 0x8226,
		CompressedRgb = 0x84ED,
		CompressedRgba = 0x84EE,
		CompressedSrgb = 0x8C48,
		CompressedSrgba = 0x8C49,
		CompressedRedRgtc1 = 0x8DBB,
		CompressedSignedRedRgtc1 = 0x8DBC,
		CompressedRgRgtc2 = 0x8DBD,
		CompressedSignedRgRgtc2 = 0x8DBE,
		CompressedRgbaBptcUnorm = 0x8E8C,
		CompressedSrgbaBptcUnorm = 0x8E8D,
		CompressedRgbBptcSignedFloat = 0x8E8E,
		CompressedRgbBptcUnsignedFloat = 0x8E8F,
	};

	enum class TextureFormat
	{
		Red = 0x1903,
		Rg = 0x8227,
		Rgb = 0x1907,
		Bgr = 0x80E0,
		Rgba = 0x1908,
		Bgra = 0x80E1,
		RedInteger = 0x8D94,
		RgInteger = 0x8228,
		RgbInteger = 0x8D98,
		BgrInteger = 0x8D9A,
		RbgaInteger = 0x8D99,
		BgraInteger = 0x8D9B,
		StencilIndex = 0x1901,
		DepthComponent = 0x1902,
		DepthStencil = 0x84F9,
	};

	enum class TextureDataType
	{
		UnsignedByte = 0x1401,
		Byte = 0x1400,
		UnsignedShort = 0x1403,
		Short = 0x1402,
		UnsignedInteger = 0x1405,
		Integer = 0x1404,
		Float = 0x1406,
	};

	class TextureBase abstract
	{
	public:
		KALEID_GRAPHICS_API const unsigned int GetWidth() const;
		KALEID_GRAPHICS_API const unsigned int GetHeight() const;
		KALEID_GRAPHICS_API void GetSize(unsigned int* width, unsigned int* height) const;
		KALEID_GRAPHICS_API bool Exists() const;

		KALEID_GRAPHICS_API virtual void SetDefaultParameters() = 0;
		KALEID_GRAPHICS_API virtual void GenerateMipmap() = 0;
		KALEID_GRAPHICS_API virtual void SetParameter(TextureParameter pname, int value) = 0;
#define _TEXTURE_BASE_PARAMETER_SETTERS(OGL_TYPE) KALEID_GRAPHICS_API virtual void SetParameter(TextureParameter pname, OGL_TYPE value) = 0;
		_TEXTURE_BASE_PARAMETER_SETTERS(DepthStencilTextureMode)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureCompareFunc)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureCompareMode)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureMinFilter)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureMagFilter)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureSwizzle)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureWrap)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureParameter)
		_TEXTURE_BASE_PARAMETER_SETTERS(InternalTextureFormat)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureFormat)
		_TEXTURE_BASE_PARAMETER_SETTERS(TextureDataType)
#undef _TEXTURE_BASE_PARAMETER_SETTERS

#ifdef KALEID_GRAPHICS_DLL
		TextureBase();
		virtual void Bind() = 0;
		void Dispose();
		const unsigned int GetId() const;
	protected:
		unsigned int _id;
		unsigned int _width;
		unsigned int _height;
#endif
	};
}
API_END