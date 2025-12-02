#pragma once

#include <cstdint>
#include "Simulation/Attributes/Vitals.hpp"

namespace sw::interfaces
{
	// в данной задаче интерфейс оверкилл с моей точки зрения, но в будущем для расширения может быть полезен чтобы иметь минимальный доступ к юнитам для более удобного API для других систем
	class IUnit
	{
	protected:
		attributes::Vitals vitals;
		int32_t currentHp;

		IUnit(int32_t currentHp) :
				currentHp(currentHp),
				vitals(sw::attributes::Vitals::defaultUnit())
		{ }

	public:
		inline bool isAlive() const { return currentHp > 0; }
		virtual int32_t getDamage(int32_t range) = 0;
		virtual void takeDamage(int32_t damage)
		{
			currentHp -= damage;
			if (currentHp < 0)
			{
				currentHp = 0;
			}
		}
	};
}
