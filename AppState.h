#ifndef RBKSCB_APP_STATE_H
#define RBKSCB_APP_STATE_H

#include "Cube.h"

struct AppState {
  AppState() : windowId(-1), mode(INTERACTIVE), c(), steps(), stepIdx(), rotX(180), rotY(0),
               prevMouseX(0), prevMouseY(0) {}

  // Modes that the app can be in.
  enum AppMode {
    INTERACTIVE, SOLVE
  };

  // GLUT state.
  int windowId;

  // Current app mode.
  AppMode mode;

  // The cube being rendered.
  Cube c;

  // The list of steps to solving the cube.
  std::vector<Cube> steps;

  // The solution step currently being shown.
  std::size_t stepIdx;

  // The current rotation around the x and y axes.
  double rotX;
  double rotY;

  // Mouse tracking.
  int prevMouseX;
  int prevMouseY;
};

extern AppState state;

#endif // RBKSCB_APP_STATE_H
