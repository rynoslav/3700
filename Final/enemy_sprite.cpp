#include "enemy_sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "vec2d.h"
#include "collision.h"
#include <cmath>
using namespace std;

namespace csis3700 {

  enemy_sprite::enemy_sprite(float initial_x, float initial_y) :
    phys_sprite(initial_x, initial_y) {
        time = 0;
        walk = new image_sequence;
        set_image_sequence(walk);
        walk -> add_image(image_library::get() -> get("goomba_right.png"), 0.1);
        walk -> add_image(image_library::get() -> get("goomba_left.png"), 0.1);
  }

  bool enemy_sprite::is_passive() const {
    return false;
  }

  void enemy_sprite::set_on_ground(bool v) {
    on_ground = v;
  }

  void enemy_sprite::advance_by_time(double dt) {
    phys_sprite::advance_by_time(dt);
    set_velocity(vec2d(50, 0));

  }

  void enemy_sprite::resolve(const collision& collision, sprite *other) {
  }

}

