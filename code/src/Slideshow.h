#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

    class Slideshow : public Sprite2D {
        GDCLASS(Slideshow, Sprite2D)

    private:

        // Hard coded to 4 photos because errors
        Ref<Texture2D> photo1;
        Ref<Texture2D> photo2;
        Ref<Texture2D> photo3;
        Ref<Texture2D> photo4;

        float transition_time = 2.0f; // seconds
        float timer = 0.0f;
        int current_index = 0;

    protected:
        static void _bind_methods();

    public:
        Slideshow();
        ~Slideshow();

        void _process(double delta) override;

        void set_photo1(const Ref<Texture2D>& tex);
        Ref<Texture2D> get_photo1() const;

        void set_photo2(const Ref<Texture2D>& tex);
        Ref<Texture2D> get_photo2() const;

        void set_photo3(const Ref<Texture2D>& tex);
        Ref<Texture2D> get_photo3() const;

        void set_photo4(const Ref<Texture2D>& tex);
        Ref<Texture2D> get_photo4() const;

        void set_transition_time(float time);
        float get_transition_time() const;

    private:
        void next_photo();
    };

}
