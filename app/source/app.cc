// app.cc

#include "app.hpp"

int main(int argc, char **argv)
{
   using namespace lime; // note: window has to be 1280x720
   if (window::open(1280, 720, "lime")) {
      Bitmap tileset{};
      if (!bitmap::create("assets/explosion.bmp", tileset)) {
         return false;
      }

      Bitmap image{}; // note: has to be 320x180
      if (!bitmap::create(320, 180, image)) {
         return false;
      }

      // todo: construct frames for animation
      Rectangle frames[12];
      for (int index = 0; index < 12; index++) {
          frames[index].x = index * 96;
          frames[index].y = 0;
          frames[index].width = 96;
          frames[index].height = 96;
      }

      constexpr int frame_limiter = 6;
      int frame_counter = 0;
      int frame_index = 0;
      
      while (window::process()) {
         if (keyboard::pressed(keyboard::Key::Escape)) {
            break;
         }
         
         // todo: blit frame animation looping
         frame_counter++;
         if (frame_counter > frame_limiter) {
             frame_counter = 0;
             frame_index = (frame_index + 1) % 12;
         }

         bitmap::clear(image, { 0, 0, 0, 255 });
         bitmap::blit(tileset, frames[frame_index], image, { 20, 20 });
         window::display(image);
      }
   }

   return 0;
}
