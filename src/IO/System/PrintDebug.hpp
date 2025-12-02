#pragma once

#include "details/PrintFieldVisitor.hpp"

namespace sw
{
	template <typename TCommand>
	void printDebug(std::ostream& stream, TCommand& attributes)
	{
		stream << attributes.Name << ' ';
		PrintFieldVisitor visitor(stream);
		attributes.visit(visitor);
		stream << "\n";
	}
}
