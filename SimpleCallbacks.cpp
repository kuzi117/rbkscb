#include "Callbacks.h"

#include "AppState.h"
#include "Constants.h"

#include <GL/glut.h>

#include <iostream>

void mouseButton(int button, int buttonState, int x, int y) {
  // If it's not the left mouse button down, ignore it.
  if (button != GLUT_LEFT_BUTTON || buttonState != GLUT_DOWN)
    return;

  // Set the starting mouse position.
  state.prevMouseX = x;
  state.prevMouseY = y;
}

void mouseMotion(int x, int y) {
  // Calculate deltas.
  int dX = state.prevMouseX - x;
  int dY = state.prevMouseY - y;

  // Calculate new rotations.
  double rotX = state.rotX - (dX * ROT_SCALE);
  double rotY = state.rotY - (dY * ROT_SCALE);

  // Wrap the values at the edges.
  if (rotX < 0)
    rotX += 360;
  else if (rotX > 360)
    rotX -= 360;
  if (rotY < 0)
    rotY += 360;
  else if (rotY > 360)
    rotY -= 360;

  // Set the new values.
  state.rotX = rotX;
  state.rotY = rotY;

  // Update the previous state for next frame.
  state.prevMouseX = x;
  state.prevMouseY = y;
}

void keyboard(unsigned char c, int x, int y) {
  // Q always quits.
  if (c == 'q') {
    std::cout << "Got quit key\n";
    glutDestroyWindow(state.windowId);
    return;
  }

  // Interactive mode allows manual rotation of the cube. Can also switch to solve mode.
  if (state.mode == AppState::INTERACTIVE) {
    switch (c) {
      case 'U': {
        state.c.rotate(UP, ACLOCK);
        break;
      }
      case 'u': {
        state.c.rotate(UP, CLOCK);
        break;
      }
      case 'F': {
        state.c.rotate(FRONT, ACLOCK);
        break;
      }
      case 'f': {
        state.c.rotate(FRONT, CLOCK);
        break;
      }
      case 'L': {
        state.c.rotate(LEFT, ACLOCK);
        break;
      }
      case 'l': {
        state.c.rotate(LEFT, CLOCK);
        break;
      }
      case 'B': {
        state.c.rotate(BACK, ACLOCK);
        break;
      }
      case 'b': {
        state.c.rotate(BACK, CLOCK);
        break;
      }
      case 'R': {
        state.c.rotate(RIGHT, ACLOCK);
        break;
      }
      case 'r': {
        state.c.rotate(RIGHT, CLOCK);
        break;
      }
      case 'D': {
        state.c.rotate(DOWN, ACLOCK);
        break;
      }
      case 'd': {
        state.c.rotate(DOWN, CLOCK);
        break;
      }
      case 'a': {
        state.c = Cube();
        break;
      }
      case 's': {
        state.mode = AppState::SOLVE;
        state.steps = state.c.solve();
        state.stepIdx = 0;
      }
      default:
        std::cout << "Unhandled keypress in interactive mode '" << c << "'\n";
        break;
    }
  } else if (state.mode == AppState::SOLVE) {
    switch (c) {
      case 's': {
        state.mode = AppState::INTERACTIVE;
        state.steps.clear();
      }
      default:
        std::cout << "Unhandled keypress in solve mode '" << c << "'\n";
        break;
    }

  }
}
