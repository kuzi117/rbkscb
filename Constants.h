#ifndef RBKSCB_CONSTANTS_H
#define RBKSCB_CONSTANTS_H

#include <cstdint>

// Rerender delay in milliseconds.
constexpr unsigned int RENDER_DELAY = 10;

// Render size constants.
constexpr uint8_t TILE_WIDTH = 8; // Size of square on each panel.
constexpr double SPACE = .4f;     // Size between squares and on edge of panel.
constexpr double LIFT = 0.001f;   // Lift value to prevent z-fighting for panels.

// Derived size constants.
constexpr double HALF_TILE_WIDTH = TILE_WIDTH / 2.f;      // Half the width of a tile.
constexpr double CUBE_WIDTH = TILE_WIDTH * 3 + SPACE * 4; // The width of the entire cube.
constexpr double HALF_CUBE_WIDTH = CUBE_WIDTH / 2.f;      // Half the width of the entire cube.
constexpr double TILE_CENTER_OFFSET = TILE_WIDTH + SPACE; // The non-diagonal offset to the center
                                                          // of a new tile on a face.

// Control constants.
constexpr double ROT_SCALE = .85; // The scale of the mouse delta to convert to degrees of rotation.

#endif // RBKSCB_CONSTANTS_H
