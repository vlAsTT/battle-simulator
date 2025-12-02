#pragma once

#include <cstdint>

namespace sw::attributes
{
    struct Mobility
    {
        int32_t moveSpeed;
        bool canMove; // если бы была необходимость в оптимизации, было бы хорошо запаковать все эти булы в int
        bool isFlying;

        Mobility() : moveSpeed(1), canMove(true), isFlying(false) { }

        static Mobility ground()
        {
            Mobility mob;
            mob.moveSpeed = 1;
            mob.canMove = true;
            mob.isFlying = false;

            return mob;
        }

        static Mobility stationary()
        {
            Mobility mob;
            mob.moveSpeed = 0;
            mob.canMove = false;
            mob.isFlying = false;

            return mob;
        }

        static Mobility flying(int32_t speed = 2)
        {
            Mobility mob;
            mob.moveSpeed = speed;
            mob.canMove = true;
            mob.isFlying = true;

            return mob;
        }
    };
}
