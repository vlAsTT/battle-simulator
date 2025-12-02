#pragma once

#include <cstdint>
#include "BaseAttribute.hpp"

namespace sw::attributes
{
    struct CombatAttributes
    {
		attributes::BaseAttribute minRange;
		attributes::BaseAttribute maxRange;

        CombatAttributes() : minRange(0) { }
        CombatAttributes(int32_t minRange, int32_t maxRange) : minRange(minRange), maxRange(maxRange) { }

        static CombatAttributes melee()
        {
			return CombatAttributes(1, 1);
        }

        static CombatAttributes ranged(int32_t minRange, int32_t maxRange)
        {
			return CombatAttributes(minRange, maxRange);
        }

        bool canAttackAtDistance(int32_t distance) const
        {
            return distance <= minRange.GetValue();
        }

        bool isMelee() const
        {
            return minRange.GetValue() <= 1;
        }

        bool isRanged() const
        {
            return !isMelee();
        }
    };
}
