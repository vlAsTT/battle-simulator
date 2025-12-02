#pragma once

#include <cstdint>
#include <optional>

namespace sw::attributes
{
    struct Transform
    {
        int32_t x;
        int32_t y;
        std::optional<std::pair<int32_t, int32_t>> marchTarget;

        Transform(int32_t x, int32_t y) : x(x), y(y), marchTarget(std::nullopt) { }

        void setMarchTarget(int32_t targetX, int32_t targetY)
        {
            marchTarget = std::make_pair(targetX, targetY);
        }

        void clearMarchTarget()
        {
            marchTarget = std::nullopt;
        }

        bool hasMarchTarget() const
        {
            return marchTarget.has_value();
        }

        std::pair<int32_t, int32_t> getMarchTarget() const
        {
            return marchTarget.value();
        }

        bool isAtTarget() const
        {
            if (!marchTarget.has_value())
                return false;
            
            return x == marchTarget->first && y == marchTarget->second;
        }

        int32_t distanceTo(int32_t otherX, int32_t otherY) const
        {
            return std::max(std::abs(x - otherX), std::abs(y - otherY));
        }

        std::pair<int32_t, int32_t> getNextStepTowards(int32_t targetX, int32_t targetY) const
        {
            int32_t dx = targetX - x;
            int32_t dy = targetY - y;

            int32_t newX = x;
            int32_t newY = y;

            if (dx != 0)
            {
                newX += (dx > 0) ? 1 : -1;
            }
            else if (dy != 0)
            {
                newY += (dy > 0) ? 1 : -1;
            }

            return {newX, newY};
        }

        void moveTo(int32_t newX, int32_t newY)
        {
            x = newX;
            y = newY;
        }
    };
}
