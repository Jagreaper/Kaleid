#include "stdafx.hpp"
#include "HeightmapStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Model.hpp"
#include "StringHelper.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "Face.hpp"
#include "Mesh.hpp"
#include <string>
#include <stdexcept>

using namespace Kaleid::IO;
using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Geometry;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

bool HeightmapStreamDecoder::TryDecode(std::istream& source, Model* output, GraphicsFactory* arg)
{
	throw std::runtime_error("Not yet implemented");
}