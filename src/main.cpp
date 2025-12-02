#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <Simulation/Simulator.hpp>
#include <Simulation/Units/Swordsman.hpp>
#include <Simulation/Units/Hunter.hpp>
#include <fstream>
#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	EventLog eventLog;
	std::unique_ptr<Simulator> simulator;
	io::CommandParser parser;

	parser.add<io::CreateMap>([&](auto command) {
		simulator = std::make_unique<Simulator>(command.width, command.height, eventLog);
		eventLog.log(1, io::MapCreated{command.width, command.height});
	});

	parser.add<io::SpawnSwordsman>([&](auto command) {
		auto unit = std::make_unique<units::Swordsman>(
			command.unitId,
			command.x,
			command.y,
			command.hp,
			command.strength
		);
		simulator->addUnit(std::move(unit));
		eventLog.log(1, io::UnitSpawned{command.unitId, "Swordsman", command.x, command.y});
	});

	parser.add<io::SpawnHunter>([&](auto command) {
		auto unit = std::make_unique<units::Hunter>(
			command.unitId,
			command.x,
			command.y,
			command.hp,
			command.agility,
			command.strength,
			command.minRange
		);
		simulator->addUnit(std::move(unit));
		eventLog.log(1, io::UnitSpawned{command.unitId, "Hunter", command.x, command.y});
	});

	parser.add<io::March>([&](auto command) {
		auto [currentX, currentY] = simulator->getUnitPosition(command.unitId);
		simulator->setUnitMarchTarget(command.unitId, command.targetX, command.targetY);
		eventLog.log(1, io::MarchStarted{
			command.unitId, 
			static_cast<uint32_t>(currentX),
			static_cast<uint32_t> (currentY),
			command.targetX,
			command.targetY
		});
	});

	parser.parse(file);

	if (simulator)
	{
		simulator->run();
	}

	return 0;
}
