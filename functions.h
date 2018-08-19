#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>

struct coordinate{
  float x;
  float y;
  float z;
  coordinate(float a, float b, float c);
};

struct face{
  int facenum;
  bool four;
  int faces[4];
  face(int facen, int f1, int f2, int f3);
  face(int facen, int f1, int f2, int f3, int f4);
};

int loadObject(const char* filename);
void drawCube(float sizeOfCube);

#endif // FUNCTIONS_H
