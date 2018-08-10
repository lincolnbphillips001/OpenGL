#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>

struct coordinate{
  float x, y, z;
  coordinate(float a, float b, float c) : x(a), y(b), z(c) {};
};

struct face{
  int facenum;
  bool four;
  int faces[4];
  face(int facen, int f1, int f2, int f3) : facenum(facen) {
    faces[0] = f1;
    faces[1] = f2;
    faces[2] = f3;
    four = false;
  }
  face(int facen, int f1, int f2, int f3, int f4) : facenum(facen) {
    faces[0] = f1;
    faces[1] = f2;
    faces[2] = f3;
    faces[3] = f4;
    four = true;
  }
};


float angle = 0.0;

int loadObject(const char* filename)
{
  std::vector<std::string*> coord;
  std::vector<coordinate*> vextex;
  std::vector<face*> faces;
  std::vector<coordinate*> normals;
  std::ifstream in(filename);
  if (!in.is_open())
  {
    std::cout << "Not opened" << std::endl;
    return -1;
  }
  char buf[256];
  while (!in.eof())
  {
    in.getline(c, 256);
    coord.push_back(new std::string(c));
  }
  for (int i=0; i < coord.size(); i++)
  {
    if ((*coord[i])[0] == '#')
    {
      continue;
    }
    else if (((*coord[i])[0] == 'v') && ((*coord[i])[1] == ' '))
    {
      float tmpx, tmpy, tmpz;
      sscanf(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
      vertex.push_back(new coordinate(tmpx, tmpy, tmpz));
    }
    else if (((*coord[i])[0] == 'v') && ((*coord[i])[1] == 'n'))
    {
      float tmpx, tmpy, tmpz;
      sscanf(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
      normals.push_back(new coordinate(tmpx, tmpy, tmpz));
    }
  }


}


void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 640.0/480.0, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  tex = loadTexture("images/brick.bmp");
}

void display(void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
  glRotatef(angle, 1.0, 1.0, 1.0);
  glBindTexture(GL_TEXTURE_2D, tex);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-2.0, 2.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-2.0, -2.0, 0.0);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(2.0, -2.0, 0.0);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(2.0, 2.0, 0.0);
  glEnd();
}

int main(int argc, char** argv) {

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface* screen;
  screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
  bool running = true;
  const int FPS = 30;
  Uint32 start;
  init();
  while(running) {
    start = SDL_GetTicks();
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
            running = false;
            break;
      }
    }
    display();
    SDL_GL_SwapBuffers();
    angle = angle + 0.5;
    if(angle > 360) {
      angle = angle - 360;
    }

    if((1000/FPS) > (SDL_GetTicks()-start)) {
      SDL_Delay((1000/FPS)-(SDL_GetTicks()-start));
    }
  }
  SDL_Quit();
  return 0;
}
