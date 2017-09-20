#pragma once

#include "stdafx.hpp"

namespace Kaleid::Helpers
{
	template <class T>
	class KALEID_HELPERS_API Nullable
	{
	public:
		Nullable();
		Nullable(const T& value);

		void MakeNull();
		T& GetValue();
		bool IsNull();

		void operator=(const T& value);
		operator T&();
		operator T() const;
	private:
		bool _null;
		T _value;
	};
}