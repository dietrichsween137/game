#ifndef STATE_H
#define STATE_H

#include "godot_cpp/classes/animation_player.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/sprite2d.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/packed_string_array.hpp"

namespace godot {

class State : public Node {
	GDCLASS(State, Node);
private:
	AnimationPlayer* animation_player;
	Sprite2D* sprite;
protected:
	static void _bind_methods() {};
public:
	State(): animation_player {nullptr}, sprite {nullptr} {};
	~State() {};

	void _ready() override;
	AnimationPlayer* get_animation_player() const {return animation_player;}
	Sprite2D* get_sprite() const {return sprite;}

	virtual void enter() {};
	virtual void handle_input(InputEvent event) {};
	virtual void physics_update(double delta) = 0;
};

class StateMachine : public Node {
	GDCLASS(StateMachine, Node);
private:
	State* state;
	double last_delta;
protected:
	static void _bind_methods();
public:
	StateMachine(): state {nullptr}, last_delta {0} {} 
	~StateMachine() {};

	void _ready() override;
	void switch_state(String next_state);
	void physics_update(double delta);
};

class PStateIdle : public State {
	GDCLASS(PStateIdle, State);
protected:
	static void _bind_methods();
public:
	void enter() override;
	void physics_update(double delta) override;
};

class PStateWalkRight : public State {
	GDCLASS(PStateWalkRight, State);
protected:
	static void _bind_methods();
public:
	void enter() override;
	void physics_update(double delta) override;
};

class PStateWalkLeft : public State {
	GDCLASS(PStateWalkLeft, State);
protected:
	static void _bind_methods();
public:
	void enter() override;
	void physics_update(double delta) override;
};

}

#endif
