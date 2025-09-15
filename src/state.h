#ifndef STATE_H
#define STATE_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/packed_string_array.hpp"

namespace godot {

class State : public Node {
	GDCLASS(State, Node);
protected:
	static void _bind_methods() {};
public:
	virtual void physics_update(double delta) = 0;
};

class StateMachine : public Node {
	GDCLASS(StateMachine, Node);
private:
	State* state;
protected:
	static void _bind_methods();
public:
	StateMachine(): state {nullptr} {} 
	~StateMachine() {};

	void _ready() override;
	void switch_state(String next_state);
	void physics_update(double delta) const;
};

class PStateIdle : public State {
	GDCLASS(PStateIdle, State);
protected:
	static void _bind_methods();
public:
	void physics_update(double delta) override;
};

class PStateWalkRight : public State {
	GDCLASS(PStateWalkRight, State);
protected:
	static void _bind_methods();
public:
	void physics_update(double delta) override;
};

class PStateWalkLeft : public State {
	GDCLASS(PStateWalkLeft, State);
protected:
	static void _bind_methods();
public:
	void physics_update(double delta) override;
};

}

#endif
