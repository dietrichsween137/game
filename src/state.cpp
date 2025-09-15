#include "state.h"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

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
	if (state == nullptr) {
		UtilityFunctions::print("No state found");
	} else {
		state->physics_update(delta);
	}
}

void StateMachine::switch_state(String next_state) {
	state = get_node<State>(next_state);
}

void PStateIdle::physics_update(double delta) {
	static Input* input = Input::get_singleton();	

	if (input->is_action_pressed("right")) {
		UtilityFunctions::print("right");
	} else if (input->is_action_pressed("left")) {
		UtilityFunctions::print("left");
	}
}
