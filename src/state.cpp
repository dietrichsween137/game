#include "state.h"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/variant/variant_internal.hpp"

using namespace godot;

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
	UtilityFunctions::print(next_state);
}

void PStateIdle::_bind_methods() {
	ADD_SIGNAL(MethodInfo("switch_state", PropertyInfo(Variant::STRING, "next_state")));
}

void PStateIdle::physics_update(double delta) {
	static Input* input = Input::get_singleton();	

	if (input->is_action_pressed("right")) {
		emit_signal("switch_state", "PStateWalkRight");
	} else if (input->is_action_pressed("left")) {
		emit_signal("switch_state", "PStateWalkLeft");
	}
}

void PStateWalkLeft::_bind_methods() {
	ADD_SIGNAL(MethodInfo("switch_state", PropertyInfo(Variant::STRING, "next_state")));
}

void PStateWalkLeft::physics_update(double delta) {
	static Input* input = Input::get_singleton();	

	if (input->is_action_pressed("left")) {
	} else if (input->is_action_pressed("right")) {
		emit_signal("switch_state", "PStateWalkRight");
	} else {
		emit_signal("switch_state", "PStateIdle");
	}
}

void PStateWalkRight::_bind_methods() {
	ADD_SIGNAL(MethodInfo("switch_state", PropertyInfo(Variant::STRING, "next_state")));
}

void PStateWalkRight::physics_update(double delta) {
	static Input* input = Input::get_singleton();	

	if (input->is_action_pressed("right")) {
	} else if (input->is_action_pressed("left")) {
		emit_signal("switch_state", "PStateWalkLeft");
	} else {
		emit_signal("switch_state", "PStateIdle");
	}
}
