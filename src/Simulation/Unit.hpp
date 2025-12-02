#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "Attributes/Vitals.hpp"
#include "Attributes/Transform.hpp"
#include "Attributes/Combat.hpp"
#include "Attributes/Mobility.hpp"
#include "Interfaces/IUnit.hpp"

namespace sw
{
    class Map;
    class EventLog;

    class Unit : public interfaces::IUnit
    {
    protected:
        uint32_t id;
        
		attributes::Transform transform;
		attributes::Mobility mobility;

    public:
		Unit(uint32_t id, int32_t x, int32_t y, int32_t hp) :
				IUnit(hp),
				id(id),
				transform(x, y),
				mobility(attributes::Mobility::ground())
		{
			
		}

        virtual ~Unit() = default;

		virtual void act(Map& map, EventLog& log, uint32_t tick, std::vector<Unit*>& scratchBuffer) = 0;
        virtual std::string getTypeName() const = 0;

        virtual bool canAct() const { return isAlive(); }
        void setMarchTarget(int32_t targetX, int32_t targetY) { transform.setMarchTarget(targetX, targetY); }

        uint32_t getId() const { return id; }
        int32_t getX() const { return transform.x; }
        int32_t getY() const { return transform.y; }
        int32_t getHp() const { return currentHp; }
        int32_t getMaxHp() const { return vitals.maxHp.GetValue(); }
        bool hasMarchTarget() const { return transform.hasMarchTarget(); }
        bool isFlying() const { return mobility.isFlying; }

		inline attributes::Vitals& getVitals() { return vitals; }
        inline attributes::Transform& getTransform() { return transform; }
		inline attributes::Mobility& getMobility() { return mobility; }

        inline const attributes::Vitals& getVitals() const { return vitals; }
		inline const attributes::Transform& getTransform() const { return transform; }
		inline const attributes::Mobility& getMobility() const { return mobility; }

    protected:
		bool moveTowardsTarget(Map& map, EventLog& log, uint32_t tick);

        int32_t distanceTo(int32_t otherX, int32_t otherY) const
        {
            return transform.distanceTo(otherX, otherY);
        }
    };
}
