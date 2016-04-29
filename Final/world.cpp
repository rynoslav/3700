#include "world.h"
#include "image_library.h"
#include "keyboard_manager.h"
#include <cassert>
#include <algorithm>
#include "sprite.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "player_sprite.h"
#include "obstruction_sprite.h"
#include "collision.h"

using namespace std;

namespace csis3700 {

  const float gravity_acceleration = 600;

  void free_sprite(sprite* s) {
    delete s;
  }

  world::world() {
      font = al_load_font("8bit.TTF", 40, NULL);
      assert(font != NULL);
      player = new player_sprite(0, 505);
      sprites.push_back(player);
      if (camera_x < 0)
        camera_x = 0;
      if (camera_y < 0)
        camera_y = 0;
      if (camera_x > 2560 - 1000)
        camera_x = 2560 - 1000;
      if (camera_y > 1000 - 720)
        camera_y = 1000 - 720;
  }

  world::world(const world& other) {
    assert(false); // do not copy worlds
  }

  world& world::operator=(const world& other) {
    assert(false); // do not assign worlds
  }

  world::~world() {
    for_each(sprites.begin(), sprites.end(), free_sprite);
    sprites.clear();
  }

  void world::handle_event(ALLEGRO_EVENT ev) {
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
        keyboard_manager::get() -> get() -> key_down(ev.keyboard.keycode);
    }
    if(ev.type == ALLEGRO_EVENT_KEY_UP){
        keyboard_manager::get() -> get() -> key_up(ev.keyboard.keycode);
    }
  }

  void world::resolve_collisions() {

  }

  void world::advance_by_time(double dt) {
    for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
      (*it)->advance_by_time(dt);
    resolve_collisions();
    camera_x = player -> get_x() - 1280 / 2;
  }

  void world::draw() {
    ALLEGRO_BITMAP *bg_image = NULL;

    ALLEGRO_TRANSFORM T;
    al_identity_transform(&T);
    al_translate_transform(&T, -camera_x, camera_y);
    al_use_transform(&T);
    bg_image = image_library::get() -> get("mariobg2.png");
    for (int i = -1280; i < 12800; i += 1280)
        al_draw_bitmap(bg_image, i, 0, 0);
    //al_clear_to_color(al_map_rgb(255,255,255));

    for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
      (*it)->draw();
    al_identity_transform(&T);
    al_use_transform(&T);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 0, 0, "SCORE: %d", score);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 0, 0, "LIVES x %d", lives);
  }

  bool world::should_exit() {
    return false;
  }

}
