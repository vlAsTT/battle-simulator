#pragma once

#include <cstdint>
#include "BaseAttribute.hpp"

namespace sw::attributes
{
    struct Vitals
    {
		BaseAttribute startHp;
		BaseAttribute maxHp;

        Vitals(int32_t startHp, int32_t maxHp) : startHp(startHp), maxHp(maxHp) {}

        static Vitals defaultUnit() {
			return Vitals(1, 1);
        }
    };
}
