/*****************************************************************************
Optional Bonus: Color blending
------------------------------
The original ask was just to take the average of the two values. However, that
got me thinking about gamma correction and sRGB. So this displays blending using
several techniques.

Not the cleanest or most clever code--I was really just trying to get something
going so that I could visualize the difference.

Reference: http://www.ericbrasseur.org/gamma.html
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>

#define min(a,b) (a) > (b) ? (b) : (a)

uint *img;
const uint img_width=1200, img_height=800;

typedef struct {int x, y;} Point;
typedef struct {uint r, g, b, hexCode;} Color;

Color parse_color(char *s)
{
  Color col;

  col.r = (uint) atoi(strtok(s, ","));
  col.g = (uint) atoi(strtok(NULL, ","));
  col.b = (uint) atoi(strtok(NULL, ","));

  if (col.r > 255 || col.g > 255 || col.b > 255) {
    fprintf(stderr, "Invalid color value\n");
    exit(EXIT_FAILURE);
  }

  col.hexCode = (col.r << 16) + (col.g << 8) + col.b;

  return col;
}

Color additive_mix(Color a, Color b)
{
  Color out;
  out.r = min(a.r + b.r, 255);
  out.g = min(a.g + b.g, 255);
  out.b = min(a.b + b.b, 255);
  out.hexCode = (out.r << 16) + (out.g << 8) + out.b;
  return out;
}

Color average_mix(Color a, Color b, double t)
{
  Color out;
  out.r = (1-t) * a.r + t * b.r;
  out.g = (1-t) * a.g + t * b.g;
  out.b = (1-t) * a.b + t * b.b;
  out.hexCode = (out.r << 16) + (out.g << 8) + out.b;
  return out;
}

double sRGB_to_linear(double x)
{
  const double a = 0.055;
  x /= 255;
  return x <= 0.04045 ? x / 12.92 : pow((x+a) / (1+a), 2.4);
}

double linear_to_sRGB(double x)
{
  const double a = 0.055;
  return x <= 0.0031308 ? 255 * x / 12.92 : 255 * ((1+a) * pow(x, 1.0/2.4) - a);
}

Color sRGB_mix(Color a, Color b, double t)
{
  Color out;
  out.r = linear_to_sRGB((1-t) * sRGB_to_linear((double) a.r) + t * sRGB_to_linear((double) b.r));
  out.g = linear_to_sRGB((1-t) * sRGB_to_linear((double) a.g) + t * sRGB_to_linear((double) b.g));
  out.b = linear_to_sRGB((1-t) * sRGB_to_linear((double) a.b) + t * sRGB_to_linear((double) b.b));
  out.hexCode = (out.r << 16) + (out.g << 8) + out.b;
  return out;
}

Color gamma_mix(Color a, Color b, double t, double gamma)
{
  Color out;
  out.r = 255.0 * pow((1-t) * pow(a.r/255.0, gamma) + t * pow(b.r/255.0, gamma), 1/gamma);
  out.g = 255.0 * pow((1-t) * pow(a.g/255.0, gamma) + t * pow(b.g/255.0, gamma), 1/gamma);
  out.b = 255.0 * pow((1-t) * pow(a.b/255.0, gamma) + t * pow(b.b/255.0, gamma), 1/gamma);
  out.hexCode = (out.r << 16) + (out.g << 8) + out.b;
  return out;
}

void print_color(Color col)
{
  printf("%03d, %03d, %03d: #%06x\n", col.r, col.g, col.b, col.hexCode);
}

void draw_pixel(uint color, Point p)
{
  if ( p.x >= 0 && p.x < img_width && p.y >= 0 && p.y < img_height )
    img[img_width * p.y + p.x] = color;
}

void draw_line(int color, Point p1, Point p2)
{
  int direction, slope, x_len, y_len, b;

  x_len = abs(p2.x - p1.x);
  y_len = abs(p2.y - p1.y);

  if (p1.x == p2.x) {                                    // Vertical line
    if (p1.y == p2.y) { draw_pixel(color, p1); return; } // Single pixel

    direction = p2.y > p1.y ? 1 : -1;
    for (int a=0; a <= y_len; a++)
    {
      draw_pixel(color, p1);
      p1.y += direction;
    }

  } else if (p1.y == p2.y) {                             // Horizontal line
    direction = p2.x > p1.x ? 1 : -1;

    for (int a=0; a <= x_len; a++)
    {
      draw_pixel(color, p1);
      p1.x += direction;
    }

  } else if (x_len >= y_len) {                           // Diagonal, x longer
    direction = p2.x > p1.x ? 1 : -1;
    slope = ((p2.y - p1.y) << 16) / x_len;
    b = p1.y << 16;

    for (int a=0; a <= x_len; a++)
    {
      p1.y = b >> 16;
      draw_pixel(color, p1);
      b += slope;
      p1.x += direction;
    }

  } else {                                               // Diagonal, y longer
    direction = p2.y > p1.y ? 1 : -1;
    slope = ((p2.x - p1.x) << 16) / y_len;
    b = p1.x << 16;

    for (int a=0; a <= y_len; a++)
    {
      p1.x = b >> 16;
      draw_pixel(color, p1);
      b += slope;
      p1.y += direction;
    }
  }

}

int main(int argc, char *argv[])
{
  SDL_Surface *surface;
  SDL_Event event;
  Color a, b;

  if (argc != 3)
    exit(EXIT_FAILURE);

  a = parse_color(argv[1]);
  b = parse_color(argv[2]);


  /* Initialize SDL Video */
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    exit(EXIT_FAILURE);
  atexit(SDL_Quit);
  surface = SDL_SetVideoMode(img_width, img_height, 32, SDL_SWSURFACE);
  SDL_WM_SetCaption("Color Blend Check", NULL);
  if (surface == NULL)
    exit(EXIT_FAILURE);
  img = (uint*) surface->pixels;

  #define N 4
  for (int i=0; i <= img_width; i++) {
    double t = (double) i / img_width;
    Point top = {i, 0}, bottom = {i, img_height / N};
    Color col;

    /* Plain additive */
    col = additive_mix(a, b);
    draw_line(col.hexCode, top, bottom);

    /* Average */
    top.y = img_height / N + 1;
    bottom.y = 2 * img_height / N;
    col = average_mix(a, b, t);
    draw_line(col.hexCode, top, bottom);

    /* sRGB */
    top.y = 2 * img_height / N + 1;
    bottom.y = 3 * img_height / N;
    col = sRGB_mix(a, b, t);
    draw_line(col.hexCode, top, bottom);

    /* 2.2 gamma */
    top.y = 3 * img_height / N + 1;
    bottom.y = img_height;
    col = gamma_mix(a, b, t, 2.2);
    draw_line(col.hexCode, top, bottom);
  }

  printf("Additive mixing\n");
  print_color(additive_mix(a, b));

  printf("Average mixing\n");
  print_color(average_mix(a, b, 0.5));

  printf("sRGB\n");
  print_color(sRGB_mix(a, b, 0.5));

  printf("Gamma 2.2\n");
  print_color(gamma_mix(a, b, 0.5, 2.2));

  SDL_Flip(surface);

  while (SDL_WaitEvent(&event)) {
    if (event.type == SDL_QUIT)
      exit(EXIT_SUCCESS);

    if (event.type == SDL_KEYDOWN)
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          /* FALL THRU */
        case SDLK_q:
          /* FALL THRU */
        case SDLK_ESCAPE:
          exit(EXIT_SUCCESS);
      }
  }

  return EXIT_SUCCESS;
}
