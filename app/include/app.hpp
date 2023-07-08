// app.hpp

#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <lime.hpp>

namespace lime {
   namespace bitmap {
      bool valid(const Bitmap &image)
      {
         return image.data != nullptr;
      }

      bool create(const int width, const int height, Bitmap &image)
      {
         // todo: check if image has previously been allocated, 
         //       if so destroy it and do the below
         // todo: allocate the bitmap pixel data using 'width' and 'height'.
          if (image.data != nullptr)
          {
              delete[] image.data;
          }
          image.data = new Color[width * height];
          image.width = width;
          image.height = height;

          return valid(image);
      }

      bool inside(const Bitmap &image, const int x, const int y)
      {
         // todo: is the image valid?
         // todo: checks if 'x' and 'y' is inside the bitmap.
          if (x <= image.width && y <= image.height && x >= 0 && y >= 0)
          {
              return valid(image);
          }

          return false;
      }

      Color get(const Bitmap &image, const int x, const int y)
      {
         const Color magenta{ 255, 0, 255, 255 };
         // todo: is the image valid?
         // todo: is pixel inside the image?
         // todo: calculate the correct index for 'x' and 'y' in the 
         //       bitmap and return requested pixel color.
         if (valid(image) && inside(image, x, y))
         {
             return image.data[x + (y * image.width)];
         }

         return magenta;
      }

      void set(Bitmap &image, const int x, const int y, const Color &color)
      {
         // todo: is the image valid?
         // todo: is pixel inside the image?
         // todo: calculate the correct index for 'x' and 'y' in bitmap
         //       and set it to color 'c'
          if (valid(image) && inside(image, x, y))
          {
              image.data[x + (y * image.width)] = color;
          }
      }

      void clear(Bitmap &image, const Color &color)
      {
         if (!valid(image)) {
            return;
         }

         // todo: set all bitmap pixels to color 'c'
         for (int i = 0; i < image.width * image.height; i++)
         {
             image.data[i] = color;
         }
      }

      void blit(const Bitmap &src, const Rectangle &rect, Bitmap &dst, const Point &pos)
      {
         // todo: blit a portion of 'src' specified by 'rect' onto the destination
         //       'dst' at the specified point 'pos'.
          if (rect.x + rect.width > src.width || rect.y + rect.height > src.height || rect.width < 0 || rect.height < 0 || rect.x < 0 || rect.y < 0)
          {
              return;
          }
          
          for (int x = 0; x < rect.width; x++)
          {
              for (int y = 0; y < rect.height; y++)
              {  
                  Color src_ = get(src, rect.x + x, rect.y + y);
                  Color dst_ = get(dst, pos.x + x, pos.y + y);
                  Color final = Color();
                  double ratio = src_.a / 255;
                  double temp_r = src_.r * ratio + dst_.r * (1 - ratio);
                  double temp_g = src_.g * ratio + dst_.g * (1 - ratio);
                  double temp_b = src_.b * ratio + dst_.b * (1 - ratio);
                  final.r = static_cast<unsigned char>(temp_r);
                  final.g = static_cast<unsigned char>(temp_g);
                  final.b = static_cast<unsigned char>(temp_b);
                  set(dst, pos.x + x, pos.y + y, final);
              }
          }
      }
   } // !image
} // !lime

#endif // !APP_HPP_INCLUDED
