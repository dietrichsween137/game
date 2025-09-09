#include "protagonist.h"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Protagonist::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_ground_accel"), &Protagonist::get_ground_accel);
	ClassDB::bind_method(D_METHOD("set_ground_accel", "p_ground_accel"), &Protagonist::set_ground_accel);
	ClassDB::bind_method(D_METHOD("get_ground_speed"), &Protagonist::get_ground_speed);
	ClassDB::bind_method(D_METHOD("set_ground_speed", "p_ground_speed"), &Protagonist::set_ground_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ground_accel"), "set_ground_accel", "get_ground_accel");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ground_speed"), "set_ground_speed", "get_ground_speed"); 
}

Protagonist::Protagonist(): ground_accel {10.0}, ground_speed {100.0} {}
Protagonist::~Protagonist() {}

void Protagonist::_physics_process(double delta) {
}

void Protagonist::set_ground_accel(double p_ground_accel) {
	ground_accel = p_ground_accel;
}

double Protagonist::get_ground_accel() const {
	return ground_accel;
}

void Protagonist::set_ground_speed(double p_ground_speed) {
	ground_speed = p_ground_speed;
}

double Protagonist::get_ground_speed() const {
	return ground_speed;
}
