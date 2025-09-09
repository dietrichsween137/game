#ifndef	PROTAGONIST_H
#define	PROTAGONIST_H

#include "godot_cpp/classes/character_body2d.hpp"

namespace godot {

class Protagonist : public CharacterBody2D {
	GDCLASS(Protagonist, CharacterBody2D)
private:
	double ground_speed;
	double ground_accel;
protected:
	static void _bind_methods();
public:
	Protagonist();
	~Protagonist();

	void _physics_process(double delta) override;

	void set_ground_speed(const double p_ground_speed);
	double get_ground_speed() const;

	void set_ground_accel(const double p_ground_accel);
	double get_ground_accel() const;
};

}

#endif
