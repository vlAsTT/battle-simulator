#pragma once

#include "Map.hpp"
#include <IO/System/EventLog.hpp>

namespace sw
{
    class Simulator
    {
    private:
        Map map;
        EventLog& log;
        uint32_t currentTick = 0;
		std::vector<Unit*> unitsBuffer;

    public:
        Simulator(int32_t width, int32_t height, EventLog& log)
            : map(width, height), log(log)
        {
			unitsBuffer = std::vector<Unit*>{};
        }

        void addUnit(std::unique_ptr<Unit> unit)
        {
            map.addUnit(std::move(unit));
        }

        void setUnitMarchTarget(uint32_t unitId, int32_t targetX, int32_t targetY)
        {
            Unit* unit = map.getUnitById(unitId);
            if (unit)
            {
                unit->setMarchTarget(targetX, targetY);
            }
        }

        std::pair<int32_t, int32_t> getUnitPosition(uint32_t unitId) const
        {
            Unit* unit = const_cast<Map&>(map).getUnitById(unitId);
            if (unit)
            {
                return {unit->getX(), unit->getY()};
            }

            return {-1, -1};
        }

        void run()
        {
            while (map.hasActiveUnits())
            {
                currentTick++;
                simulateStep();
            }
        }

    private:
        void simulateStep()
        {
            map.removeDeadUnits(log, currentTick);

            auto units = map.getAllUnits();
            for (Unit* unit : units)
            {
                if (unit->canAct())
                {
                    unit->act(map, log, currentTick, unitsBuffer);
                }
            }
        }
    };
}
