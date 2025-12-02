#include "Unit.hpp"
#include "IO/System/EventLog.hpp"
#include "Map.hpp"

namespace sw
{
	bool Unit::moveTowardsTarget(Map& map, EventLog& log, uint32_t tick)
	{
		if (!transform.hasMarchTarget())
		{
			return false;
		}

		if (transform.isAtTarget())
		{
			transform.clearMarchTarget();
			log.log(
				tick, sw::io::MarchEnded{id, static_cast<uint32_t>(transform.x), static_cast<uint32_t>(transform.y)});
			return false;
		}

		auto [targetX, targetY] = transform.getMarchTarget();
		auto [newX, newY] = transform.getNextStepTowards(targetX, targetY);

		if (map.isInBounds(newX, newY) && !map.isCellOccupied(newX, newY))
		{
			transform.moveTo(newX, newY);
			log.log(tick, io::UnitMoved{id, static_cast<uint32_t>(transform.x), static_cast<uint32_t>(transform.y)});

			if (transform.isAtTarget())
			{
				transform.clearMarchTarget();
				log.log(
					tick, io::MarchEnded{id, static_cast<uint32_t>(transform.x), static_cast<uint32_t>(transform.y)});
			}

			return true;
		}

		return false;
	}
}
