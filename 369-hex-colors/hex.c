#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct color {
  uint r, g, b, hexCode;
} Color;

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

Color mix(Color a, Color b)
{
  Color out;
  out.r = 0.5 * a.r + 0.5 * b.r;
  out.g = 0.5 * a.g + 0.5 * b.g;
  out.b = 0.5 * a.b + 0.5 * b.b;
  out.hexCode = (out.r << 16) + (out.g << 8) + out.b;
  return out;
}

void print_color(Color col)
{
  printf("%d, %d, %d: #%06x\n", col.r, col.g, col.b, col.hexCode);
}

int main(int argc, char *argv[])
{

  if (argc == 2) {
    print_color(parse_color(argv[1]));
  } else if (argc == 3) {
    print_color(mix(parse_color(argv[1]), parse_color(argv[2])));
  } else {
    fprintf(stderr, "Incorrect number of parameters\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
