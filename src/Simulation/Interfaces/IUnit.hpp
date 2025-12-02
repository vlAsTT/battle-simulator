#pragma once

#include <cstdint>
#include "Simulation/Attributes/Vitals.hpp"

namespace sw::interfaces
{
	// интерфейс для данного задания это оверкилл, с моей точки зрения, но в будущем это поможет минимизировать код работающий с юнитами для других систем, то есть чтобы создать свой API для юнитов
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
