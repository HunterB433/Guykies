#include "EmitSprite.h"

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <random>
#include <godot_cpp/core/math.hpp>



using namespace godot;

// Stub
void EmitSprite::_bind_methods() {

	// Bind Getters and Setters
	// Emit_speed
	ClassDB::bind_method(D_METHOD("get_emit_speed"), &EmitSprite::get_emit_speed);
	ClassDB::bind_method(D_METHOD("set_emit_speed", "p_speed"), &EmitSprite::set_emit_speed);
	// Emit_scale
	ClassDB::bind_method(D_METHOD("get_emit_scale"), &EmitSprite::get_emit_scale);
	ClassDB::bind_method(D_METHOD("set_emit_scale", "p_scale"), &EmitSprite::set_emit_scale);
	// Emit_direction
	ClassDB::bind_method(D_METHOD("get_emit_direction"), &EmitSprite::get_emit_direction);
	ClassDB::bind_method(D_METHOD("set_emit_direction", "p_dir"), &EmitSprite::set_emit_direction);
	// Velocity
	ClassDB::bind_method(D_METHOD("get_velocity"), &EmitSprite::get_velocity);
	ClassDB::bind_method(D_METHOD("set_velocity", "p_vel"), &EmitSprite::set_velocity);
	// Stationary flag
	ClassDB::bind_method(D_METHOD("get_is_emitter_stationary"), &EmitSprite::get_is_emitter_stationary);
	ClassDB::bind_method(D_METHOD("set_is_emitter_stationary", "p_val"), &EmitSprite::set_is_emitter_stationary);
	// Can Emit Flag
	ClassDB::bind_method(D_METHOD("get_can_emit"), &EmitSprite::get_can_emit);
	ClassDB::bind_method(D_METHOD("set_can_emit", "p_val"), &EmitSprite::set_can_emit);

	// Add Properties
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "emit_speed"), "set_emit_speed", "get_emit_speed");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "emit_scale"), "set_emit_scale", "get_emit_scale");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "emit_direction"), "set_emit_direction", "get_emit_direction");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "velocity"), "set_velocity", "get_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_emitter_stationary"), "set_is_emitter_stationary", "get_is_emitter_stationary");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "can_emit"), "set_can_emit", "get_can_emit");

	// Special
	ClassDB::bind_method(D_METHOD("emit_copy"), &EmitSprite::emit_copy);

	// Signal
	ADD_SIGNAL(MethodInfo("scored", PropertyInfo(Variant::INT, "points")));

}

// Stub
EmitSprite::EmitSprite() {
	// Initialize to avoid Null data
	emit_speed = 0.0;
	emit_scale = 0.0;
}

// Stub
EmitSprite::~EmitSprite() {
}



void EmitSprite::set_emit_speed(const float p_speed) {
	emit_speed = p_speed;
}

float EmitSprite::get_emit_speed() const {
	return emit_speed;
}

void EmitSprite::set_emit_scale(const float p_scale) {
	emit_scale = p_scale;
}

float EmitSprite::get_emit_scale() const {
	return emit_scale;
}

void EmitSprite::set_emit_direction(const Vector2 p_dir) {
	emit_direction = p_dir.normalized();
}

Vector2 EmitSprite::get_emit_direction() const {
	return emit_direction;
}


void EmitSprite::emit_copy() {
	EmitSprite* clone = memnew(EmitSprite);

	// Copy texture
	clone->set_texture(get_texture());

	// Position at parent
	clone->set_position(get_position());

	// Scale relative to parent
	clone->set_scale(get_scale() * (emit_scale > 0 ? emit_scale : 1.0));

	// Random direction
	// terrible aweful code I dont like
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, Math_PI * 2.0f);
	float angle = dist(gen);
	Vector2 random_dir(Math::cos(angle), Math::sin(angle));
	clone->set_velocity(random_dir * emit_speed);

	clone->set_is_emitter_stationary(false);
	clone->set_can_emit(false);
	clone->set_process(true);
	clone->set_visible(true);

	// Add to parent
	get_parent()->add_child(clone);
}







void EmitSprite::_process(double delta) {
	// Move
	if (!is_emitter_stationary && velocity != Vector2()) {
		set_position(get_position() + velocity * (float)delta);
	}

	// Life timer
	life_timer += delta;
	if (!can_emit && life_timer >= lifespan) {
		queue_free();
		return; // stop processing
	}

	// Emit
	emit_timer += delta;
	if (can_emit && emit_timer >= emit_interval) {
		emit_signal("scored", 1);
		emit_copy();
		emit_timer = 0.0;
	}
}



