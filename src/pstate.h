#ifndef PSTATE_H
#define PSTATE_H

#include "state.h"

namespace godot {

class PStateIdle : public State {
	GDCLASS(PStateIdle, State);
protected:
	static void _bind_methods() {}
public:
	virtual void physics_update(double delta) override {}
};

class PStateWalkRight : public State {
	GDCLASS(PStateWalkRight, State);
protected:
	static void _bind_methods() {}
public:
	virtual void physics_update(double delta) override {}
};

class PStateWalkLeft: public State {
	GDCLASS(PStateWalkLeft, State);
protected:
	static void _bind_methods() {}
public:
	virtual void physics_update(double delta) override {}
};

}

#endif
