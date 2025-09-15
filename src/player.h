#ifndef PLAYER_H	
#define PLAYER_H	

#include "godot_cpp/classes/animation_player.hpp"
#include "godot_cpp/classes/character_body2d.hpp"
#include "state.h"

namespace godot {

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)
private:
	const StateMachine* state_machine;
	const AnimationPlayer* animation_player;
	double ground_speed;
	double ground_accel;
protected:
	static void _bind_methods();
public:
	Player();
	~Player();
	
	void _ready() override;
	void _physics_process(double delta) override;

	void set_ground_speed(const double p_ground_speed);
	double get_ground_speed() const;

	void set_ground_accel(const double p_ground_accel);
	double get_ground_accel() const;
};

}

#endif
