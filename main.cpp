#include "AppState.h"
#include "Callbacks.h"
#include "Constants.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glut.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  for (size_t face = 0; face < Cube::faceCount; ++face) {
    glPushMatrix();

    auto [xAngle, yAngle] = Cube::rotMap.at(static_cast<Face>(face));
    glRotatef(xAngle, 1.f, 0.f, 0.f);
    glRotatef(yAngle, 0.f, 1.f, 0.f);

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f(-HALF_CUBE_WIDTH, HALF_CUBE_WIDTH, -HALF_CUBE_WIDTH);
    glVertex3f(HALF_CUBE_WIDTH, HALF_CUBE_WIDTH, -HALF_CUBE_WIDTH);
    glVertex3f(HALF_CUBE_WIDTH, -HALF_CUBE_WIDTH, -HALF_CUBE_WIDTH);
    glVertex3f(-HALF_CUBE_WIDTH, -HALF_CUBE_WIDTH, -HALF_CUBE_WIDTH);
    glEnd();

    for (int8_t i = 0; i < 3; ++i) {
      for (int8_t j = 0; j < 3; ++j) {
        glPushMatrix();

        glTranslatef(TILE_CENTER_OFFSET * (1 - j), TILE_CENTER_OFFSET * (1 - i), 0);

        const color &cols = Cube::colorMap.at(state.c.grid[face][i][j]);
        glColor3ub(cols.vals[0], cols.vals[1], cols.vals[2]);
        glBegin(GL_QUADS);
        glVertex3f(-HALF_TILE_WIDTH, HALF_TILE_WIDTH, -(HALF_CUBE_WIDTH + LIFT));
        glVertex3f(HALF_TILE_WIDTH, HALF_TILE_WIDTH, -(HALF_CUBE_WIDTH + LIFT));
        glVertex3f(HALF_TILE_WIDTH, -HALF_TILE_WIDTH, -(HALF_CUBE_WIDTH + LIFT));
        glVertex3f(-HALF_TILE_WIDTH, -HALF_TILE_WIDTH, -(HALF_CUBE_WIDTH + LIFT));
        glEnd();
        glPopMatrix();
      }
    }
    glPopMatrix();
  }
  glPopMatrix();

  glFlush();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50, 50.0, -50.0, 50.0, -25, 15);

  glRotated(state.rotY, 1, 0, 0);
  glRotated(state.rotX, 0, 1, 0);
}

void loop(int timerState)
{
  glutPostRedisplay();
  glutTimerFunc(RENDER_DELAY, loop, timerState);
}

int main(int argc, char **argv)
{
  // Glut init.
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(600,600);
  state.windowId = glutCreateWindow ("square");

  // Gl init.
  glClearColor(.8, .8, .8, 1); // black background
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);

  // Set up glut functions.
  glutTimerFunc(RENDER_DELAY, loop, 0);
  glutDisplayFunc(display);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
  glutKeyboardUpFunc(keyboard);
  glutMainLoop();

  return 0;
}
