#pragma once

#include "Simulation/Unit.hpp"
#include "Simulation/Map.hpp"
#include "Simulation/Attributes/Combat.hpp"
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <random>

namespace sw::units
{
    class Swordsman : public Unit
    {
    private:
		attributes::CombatAttributes combat;
		attributes::BaseAttribute strength;

    public:
        Swordsman(uint32_t id, int32_t x, int32_t y, int32_t hp, int32_t strength)
            : Unit(id, x, y, hp),
				combat(attributes::CombatAttributes::melee())
        {
			
        }

        std::string getTypeName() const override
        {
            return "Swordsman";
        }

        virtual int32_t getDamage(int32_t range) override {
			return strength.GetValue();
        }

        void act(Map& map, EventLog& log, uint32_t tick, std::vector<Unit*>& scratchBuffer) override
        {
            if (!isAlive())
                return;

            scratchBuffer.clear();
			map.getUnitsInRange(id, transform.x, transform.y, combat.minRange.GetValue(), combat.maxRange.GetValue(), scratchBuffer);

            if (!scratchBuffer.empty())
            {
                static std::random_device rd;
                static std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(0, scratchBuffer.size() - 1);
                
                auto damage = getDamage(1);
                Unit* target = scratchBuffer[dis(gen)];
                target->takeDamage(damage);
                
                log.log(tick, io::UnitAttacked{
                    id,
                    target->getId(),
					static_cast<uint32_t>(damage),
                    static_cast<uint32_t>(target->getHp())
                });
                return;
            }

            if (mobility.canMove)
            {
                moveTowardsTarget(map, log, tick);
            }
        }
    };
}
