#include "stdafx.hpp"
#include "Nullable.hpp"

using namespace Kaleid::Helpers;


template <class T>
Nullable<T>::Nullable()
{
	this->_null = true;
}

template <class T>
Nullable<T>::Nullable(const T& value)
{
	this->_null = false;
	this->_value = value;
}

template <class T>
void Nullable<T>::MakeNull()
{
	this->_null = true;
}

template <class T>
T& Nullable<T>::GetValue()
{
	return this->_value;
}

template <class T>
bool Nullable<T>::IsNull()
{
	return this->_null;
}

template <class T>
void Nullable<T>::operator=(const T& value)
{
	this->_null = false;
	this->_value = value;
}

template <class T>
Nullable<T>::operator T&()
{
	return this->_value;
}

template <class T>
Nullable<T>::operator T() const
{
	return this->_value;
}