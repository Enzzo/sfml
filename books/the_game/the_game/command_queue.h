#pragma once

#include <queue>

#include "scene_node.h"

//--------------------------------------------------+
//					class CommandQueue				|
//--------------------------------------------------+
class CommandQueue {
public:
	void	push(const Command& command);
	Command	pop();
	bool	is_empty() const;

private:
	std::queue<Command> _queue;
};