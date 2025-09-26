#include "Slideshow.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Slideshow::_bind_methods() {
    // Bind Methods
    ClassDB::bind_method(D_METHOD("set_photo1", "tex"), &Slideshow::set_photo1);
    ClassDB::bind_method(D_METHOD("get_photo1"), &Slideshow::get_photo1);

    ClassDB::bind_method(D_METHOD("set_photo2", "tex"), &Slideshow::set_photo2);
    ClassDB::bind_method(D_METHOD("get_photo2"), &Slideshow::get_photo2);

    ClassDB::bind_method(D_METHOD("set_photo3", "tex"), &Slideshow::set_photo3);
    ClassDB::bind_method(D_METHOD("get_photo3"), &Slideshow::get_photo3);

    ClassDB::bind_method(D_METHOD("set_photo4", "tex"), &Slideshow::set_photo4);
    ClassDB::bind_method(D_METHOD("get_photo4"), &Slideshow::get_photo4);

    ClassDB::bind_method(D_METHOD("set_transition_time", "time"), &Slideshow::set_transition_time);
    ClassDB::bind_method(D_METHOD("get_transition_time"), &Slideshow::get_transition_time);

    // Properties
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "photo1", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_photo1", "get_photo1");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "photo2", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_photo2", "get_photo2");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "photo3", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_photo3", "get_photo3");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "photo4", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_photo4", "get_photo4");

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "transition_time"), "set_transition_time", "get_transition_time");
}

Slideshow::Slideshow() {
}

Slideshow::~Slideshow() {
}

// Switch between
void Slideshow::_process(double delta) {
    timer += static_cast<float>(delta);
    if (timer >= transition_time) {
        timer = 0.0f;
        next_photo();
    }
}

void Slideshow::set_photo1(const Ref<Texture2D>& tex) { photo1 = tex; }
Ref<Texture2D> Slideshow::get_photo1() const { return photo1; }

void Slideshow::set_photo2(const Ref<Texture2D>& tex) { photo2 = tex; }
Ref<Texture2D> Slideshow::get_photo2() const { return photo2; }

void Slideshow::set_photo3(const Ref<Texture2D>& tex) { photo3 = tex; }
Ref<Texture2D> Slideshow::get_photo3() const { return photo3; }

void Slideshow::set_photo4(const Ref<Texture2D>& tex) { photo4 = tex; }
Ref<Texture2D> Slideshow::get_photo4() const { return photo4; }

void Slideshow::set_transition_time(float time) { transition_time = time; }
float Slideshow::get_transition_time() const { return transition_time; }

// Swiych case for photos
void Slideshow::next_photo() {
    current_index = (current_index + 1) % 4;

    Ref<Texture2D> tex;
    switch (current_index) {
    case 0: tex = photo1; break;
    case 1: tex = photo2; break;
    case 2: tex = photo3; break;
    case 3: tex = photo4; break;
    }

    if (tex.is_valid()) {
        set_texture(tex);
    }
}
