#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

	class EmitSprite : public Sprite2D {
		GDCLASS(EmitSprite, Sprite2D)

	private:
		float emit_speed;
		float emit_scale;
		Vector2 emit_direction;
		Vector2 velocity = Vector2();

		double lifespan = 3.0; // seconds
		double life_timer = 0.0;

		double emit_timer = 0.0;
		double emit_interval = 1.0;

		bool is_emitter_stationary = false;
		bool can_emit = true;

	protected:
		static void _bind_methods();

	public:
		EmitSprite();
		~EmitSprite();

		void set_emit_speed(const float p_speed);
		float get_emit_speed() const;

		void set_emit_scale(const float p_scale);
		float get_emit_scale() const;

		void set_emit_direction(const Vector2 p_dir);
		Vector2 get_emit_direction() const;

		void emit_copy();

		void set_velocity(Vector2 p_vel) { velocity = p_vel; }
		Vector2 get_velocity() const { return velocity; }

		void _process(double delta) override;

		void set_is_emitter_stationary(bool p_val) { is_emitter_stationary = p_val; }
		bool get_is_emitter_stationary() const { return is_emitter_stationary; }

		void set_can_emit(bool p_val) { can_emit = p_val; };
		bool get_can_emit() const { return can_emit; };

	};
}