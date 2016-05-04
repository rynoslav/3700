#include "obstruction_sprite.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
   obstruction_sprite::obstruction_sprite(float initial_x, float initial_y, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *im2) : sprite(initial_x, initial_y) {
    al_draw_bitmap(image, initial_x, initial_y, 0);
  }

  vec2d obstruction_sprite::get_velocity() const {
    return vec2d(0,0);
  }

  void obstruction_sprite::set_velocity(const vec2d& v) {
    assert(false);
  }

  void obstruction_sprite::resolve(const collision& collision, sprite* other) {
    // do nothing, I am not an active participant in a collision
  }



}
