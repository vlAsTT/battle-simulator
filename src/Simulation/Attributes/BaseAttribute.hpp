#pragma once

#include <cstdint>

namespace sw::attributes
{
	struct BaseAttribute
	{
	public:
		BaseAttribute() : value(0) {}
		BaseAttribute(int value) : value(value) {}

		inline int32_t GetValue() const
		{
			return value;
		}

		inline void SetValue(int32_t value)
		{
			this->value = value;
		}

	private:
		int32_t value;
	};
}
