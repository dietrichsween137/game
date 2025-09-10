#ifndef STATE_H
#define STATE_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/wrapped.hpp"

namespace godot {

class State : public Node {
	GDCLASS(State, Node);

protected:
	static void _bind_methods() {}
public:
	virtual void physics_update() = 0;
};

class PStateIdle : public State {
	GDCLASS(PStateIdle, State);

protected:
	static void _bind_methods() {}
public:
	virtual void physics_update() override {}
};

}

#endif
