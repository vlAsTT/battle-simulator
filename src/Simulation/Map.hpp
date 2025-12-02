#pragma once

#include "Unit.hpp"
#include <memory>
#include <vector>
#include <algorithm>

namespace sw
{
    class EventLog;

    class Map
    {
    private:
        int32_t width;
        int32_t height;
        std::vector<std::unique_ptr<Unit>> units;

    public:
        Map(int32_t width, int32_t height)
            : width(width), height(height)
        {
        }

        void addUnit(std::unique_ptr<Unit> unit)
        {
            units.push_back(std::move(unit));
        }

        Unit* getUnitById(uint32_t id)
        {
            for (auto& unit : units)
            {
                if (unit->getId() == id)
                    return unit.get();
            }
            return nullptr;
        }

        Unit* getUnitAt(int32_t x, int32_t y)
        {
            for (auto& unit : units)
            {
                if (unit->isAlive() && unit->getX() == x && unit->getY() == y)
                    return unit.get();
            }
            return nullptr;
        }

		void getUnitsInRange(uint32_t callerId, int32_t x, int32_t y, int32_t minRange, int32_t maxRange, std::vector<Unit*>& outResult)
		{
			outResult.clear();
			for (auto& unit : units)
			{
				if (unit->isAlive())
				{
					int32_t dx = std::abs(unit->getX() - x);
					int32_t dy = std::abs(unit->getY() - y);
					int32_t distance = std::max(dx, dy);

					if (distance >= minRange && distance <= maxRange && unit->getId() != callerId)
					{
						outResult.push_back(unit.get());
					}
				}
			}
		}

        bool isInBounds(int32_t x, int32_t y) const
        {
            return x >= 0 && x < width && y >= 0 && y < height;
        }

        bool isCellOccupied(int32_t x, int32_t y) const
        {
            for (const auto& unit : units)
            {
                if (unit->isAlive() && !unit->isFlying() && unit->getX() == x && unit->getY() == y)
                {
                    return true;
                }
            }

            return false;
        }

        void removeDeadUnits(EventLog& log, uint32_t tick);

        std::vector<Unit*> getAllUnits()
        {
            std::vector<Unit*> result;
            for (auto& unit : units)
            {
                if (unit->isAlive())
                    result.push_back(unit.get());
            }

            return result;
        }

        bool hasActiveUnits() const
        {
            int32_t aliveCount = 0;
            for (const auto& unit : units)
            {
                if (unit->canAct())
                    aliveCount++;
            }

            return aliveCount > 1;
        }

        int32_t getWidth() const { return width; }
        int32_t getHeight() const { return height; }
    };
}
