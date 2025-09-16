#include "state.h"
#include "godot_cpp/classes/animation_player.hpp"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/node.hpp"

using namespace godot;


void State::_ready() {
	animation_player = get_node<AnimationPlayer>("../../AnimationPlayer");
	sprite = get_node<Sprite2D>("../../Sprite2D");
}

void StateMachine::_bind_methods() {
	ClassDB::bind_method(D_METHOD("switch_state", "next_state"), &StateMachine::switch_state);
}

void StateMachine::_ready() {
	int child_count {get_child_count()};

	for (int i {0}; i != child_count; i++) {
		Node* child = get_child(i);
		child->connect("switch_state", Callable(this, "switch_state"));

		// First state in the heirachy is default
		if (i == 0) {
			state = static_cast<State*>(child);
		}
	}
}

void StateMachine::physics_update(double delta) const{
	state->physics_update(delta);
}

void StateMachine::switch_state(String next_state) {
	state = get_node<State>(next_state);
	state->enter();
}

void PStateIdle::_bind_methods() {
	ADD_SIGNAL(MethodInfo("switch_state", PropertyInfo(Variant::STRING, "next_state")));
}

void PStateIdle::enter() {
	UtilityFunctions::print(get_class());
	State::get_animation_player()->play("idle");
}

void PStateIdle::physics_update(double delta) {
	static Input* input = Input::get_singleton();
	
	int horiz = static_cast<int>(input->get_axis("left", "right"));

	switch (horiz) {
		case 1:
			emit_signal("switch_state", "PStateWalkRight"); 
			break;
		case -1:
			emit_signal("switch_state", "PStateWalkLeft");
			break;
	}
}

void PStateWalkRight::_bind_methods() {
	ADD_SIGNAL(MethodInfo("switch_state", PropertyInfo(Variant::STRING, "next_state")));
}

void PStateWalkRight::enter() {
	UtilityFunctions::print(get_class());
	State::get_animation_player()->play("walk");
	State::get_sprite()->set_flip_h(false);
}

void PStateWalkRight::physics_update(double delta) {
	static Input* input = Input::get_singleton();
	
	int horiz = static_cast<int>(input->get_axis("left", "right"));

	switch (horiz) {
		case 0:
			emit_signal("switch_state", "PStateIdle"); 
			break;
		case -1:
			emit_signal("switch_state", "PStateWalkLeft");
			break;
	}
}

void PStateWalkLeft::_bind_methods() {
	ADD_SIGNAL(MethodInfo("switch_state", PropertyInfo(Variant::STRING, "next_state")));
}

void PStateWalkLeft::enter() {
	UtilityFunctions::print(get_class());
	State::get_animation_player()->play("walk");
	State::get_sprite()->set_flip_h(true);
}

void PStateWalkLeft::physics_update(double delta) {
	static Input* input = Input::get_singleton();
	
	int horiz = static_cast<int>(input->get_axis("left", "right"));

	switch (horiz) {
		case 1:
			emit_signal("switch_state", "PStateWalkRight"); 
			break;
		case 0:
			emit_signal("switch_state", "PStateIdle");
			break;
	}
}
