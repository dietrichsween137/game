#ifndef STATE_H
#define STATE_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/variant/packed_string_array.hpp"

namespace godot {

class State : public Node {
	GDCLASS(State, Node);
protected:
	static void _bind_methods() {};
public:
	virtual void physics_update(double delta) = 0;
	void start_state() {};
	virtual void end_state(String next_state) = 0;
};

class StateMachine : public Node {
	GDCLASS(StateMachine, Node);
private:
	void (*physics_update_ptr)(double);
protected:
	static void _bind_methods() {};
public:
	StateMachine(): physics_update_ptr {nullptr} {}
	~StateMachine() {};
	void _ready() override;
	void switch_state(State& current_state, String next_state);
};

}

#endif
