#include "player_sprite.h"
#include "keyboard_manager.h"
#include "image_library.h"
#include "image_sequence.h"
#include "vec2d.h"
#include "collision.h"
#include <cmath>

#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"


using namespace std;

namespace csis3700 {

  player_sprite::player_sprite(float initial_x, float initial_y) :
    phys_sprite(initial_x, initial_y) {
        time = 0;

        still = new image_sequence;
        set_image_sequence(still);
        still -> add_image(image_library::get() -> get("mario_right.png"), 0.2);

        walk_right = new image_sequence;
        walk_right -> add_image(image_library::get() -> get("mario_right.png"), .1);
        walk_right -> add_image(image_library::get() -> get("mario_walk_right.png"), .1);
        walk_right -> add_image(image_library::get() -> get("mario_walk_right2.png"), .1);
        walk_right -> add_image(image_library::get() -> get("mario_walk_right.png"), .1);

        walk_left = new image_sequence;
        walk_left -> add_image(image_library::get() -> get("mario_left.png"), .1);
        walk_left -> add_image(image_library::get() -> get("mario_walk_left.png"), .1);
        walk_left -> add_image(image_library::get() -> get("mario_walk_left2.png"), .1);
        walk_left -> add_image(image_library::get() -> get("mario_walk_left.png"), .1);
  }

  bool player_sprite::is_passive() const {
    return false;
  }

  void player_sprite::set_on_ground(bool v) {
    on_ground = v;
  }

  void player_sprite::advance_by_time(double dt) {
    phys_sprite::advance_by_time(dt);

    if(keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_RIGHT) && keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_UP) && position.get_y() >= 505){
        set_velocity(vec2d(150, -325));
        set_acceleration(vec2d(0, 500));
        jump_right = new image_sequence;
        set_image_sequence(jump_right);
        jump_right -> add_image(image_library::get() -> get("mario_jump_right.png"), 1000);
        jump_right -> add_image(image_library::get() -> get("mario_right.png"), 1000);

        ALLEGRO_SAMPLE *sample=NULL;
        sample = al_load_sample("Sounds/jump.wav");
        if (!sample){
            cerr << "Audio clip sample not loaded!"<< endl;
        }
        else{
            al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        }

    } else if(keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_LEFT) && keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_UP) && position.get_y() >= 505){
        set_velocity(vec2d(-150, -325));
        set_acceleration(vec2d(0, 500));
        jump_left = new image_sequence;
        set_image_sequence(jump_left);
        jump_left -> add_image(image_library::get() -> get("mario_jump_left.png"), 1000);
        jump_left -> add_image(image_library::get() -> get("mario_left.png"), 1000);

        ALLEGRO_SAMPLE *sample=NULL;
        sample = al_load_sample("Sounds/jump.wav");

        if (!sample){
            cerr << "Audio clip sample not loaded!"<< endl;
        }
        else{
            al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        }

    } else if(keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_UP) && position.get_y() >= 505){
        set_velocity(vec2d(0, -325));
        set_acceleration(vec2d(0, 500));
        jump = new image_sequence;
        set_image_sequence(jump);
        jump -> add_image(image_library::get() -> get("mario_jump_right.png"), 1000);
        jump -> add_image(image_library::get() -> get("mario_right.png"), 1000);

        ALLEGRO_SAMPLE *sample=NULL;
        sample = al_load_sample("Sounds/jump.wav");
        if (!sample){
            cerr << "Audio clip sample not loaded!"<< endl;
        }
        else{
            al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        }
    } else if (keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_RIGHT) && position.get_y() >= 505){
        set_image_sequence(walk_right);
        set_velocity(vec2d(150, 0));

    } else if (keyboard_manager::get() -> is_key_down(ALLEGRO_KEY_LEFT) && position.get_y() >= 505){
        set_image_sequence(walk_left);
        set_velocity(vec2d(-150, 0));

    } else if(position.get_y() >= 505){
        set_on_ground(true);
        set_velocity(vec2d(0,0));
        set_acceleration(vec2d(0,0));
        set_image_sequence(still);
    }
  }

  void player_sprite::resolve(const collision& collision, sprite *other) {
  //if (other->bounding_box().  get_position()){cout<<"collision!" << endl;}

  }

}
