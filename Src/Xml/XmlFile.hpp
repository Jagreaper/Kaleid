#pragma once

#include "stdafx.hpp"
#include <string>
#include <vector>

namespace Kaleid::Xml
{
	struct XmlAttribute
	{
		std::string Name;
		std::string Value;
	};

	class KALEID_XML_API XmlElement
	{
	public:
		const bool HasChildren() const;
		const bool HasElementChildren() const;
		const bool HasAttributes() const;

		const std::vector<XmlAttribute>* GetAttributes() const;
		const std::vector<XmlElement>* GetChildren() const;
		const std::vector<XmlAttribute> GetAttributes(const std::string name) const;
		const std::vector<XmlElement> GetChildren(const std::string name) const;
		const std::string* GetChild() const;
		const std::string& GetName() const;

		void AddAttribute(const XmlAttribute& attribute);
		void AddElement(const XmlElement& element);
		void SetValue(const std::string& value);
		void SetName(const std::string& name);
	private:
		const void* InternalGetChildren() const;

		std::vector<XmlAttribute> _attributes;
		std::vector<XmlElement> _elements;
		std::string _name;
		std::string _value;
	};

	class KALEID_XML_API XmlFile
	{
	public:
		const std::vector<XmlElement>* GetElements() const;
		const std::vector<XmlElement> GetElements(const std::string name) const;

		void AddElement(const XmlElement& element);

		static void FromString(XmlFile* file);
		void ToString(std::string* string);
	private:
		std::vector<XmlElement> _elements;
	};
}