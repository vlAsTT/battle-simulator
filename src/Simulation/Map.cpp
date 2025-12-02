#include "Map.hpp"
#include <IO/System/EventLog.hpp>
#include <IO/Events/UnitDied.hpp>

namespace sw
{
    void Map::removeDeadUnits(EventLog& log, uint32_t tick)
    {
        for (auto& unit : units)
        {
            if (!unit->isAlive())
            {
                log.log(tick, io::UnitDied{unit->getId()});
            }
        }

        units.erase(
            std::remove_if(units.begin(), units.end(),
                [](const std::unique_ptr<Unit>& unit) { return !unit->isAlive(); }),
            units.end()
        );
    }
}
