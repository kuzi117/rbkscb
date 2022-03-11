#include "Cube.h"

#include <array>
#include <functional>
#include <cassert>
#include <iostream>
#include <queue>

namespace {

// Generic rotate square array right. Technically supports arbitrarily sized arrays.
void rotateFaceClock(Color g[Cube::sideLength][Cube::sideLength]) {
  // Manages the layers of the array, outside to inside.
  for (size_t i = 0; i < Cube::sideLength / 2; ++i) {
    // Manages going around in the circle.
    for (size_t j = i; j < Cube::sideLength - i - 1; ++j) {
      // Temp save top.
      Color temp = g[i][j];
      // Left to top.
      g[i][j] = g[Cube::sideLength - j - 1][i];
      // Bottom to left.
      g[Cube::sideLength - j - 1][i] = g[Cube::sideLength - i - 1][Cube::sideLength - j - 1];
      // Right to bottom.
      g[Cube::sideLength - i - 1][Cube::sideLength - j - 1] = g[j][Cube::sideLength - i - 1];
      // Top to right.
      g[j][Cube::sideLength - i - 1] = temp;
    }
  }
}

// Generic rotate square array right. Technically supports arbitrarily sized arrays.
void rotateFaceAClock(Color g[Cube::sideLength][Cube::sideLength]) {
  // Manages the layers of the array, outside to inside.
  for (size_t i = 0; i < Cube::sideLength / 2; ++i) {
    // Manages going around in the circle.
    for (size_t j = i; j < Cube::sideLength - i - 1; ++j) {
      // Temp save top.
      Color temp = g[i][j];
      // Right to top.
      g[i][j] = g[j][Cube::sideLength - i - 1];
      // Bottom to right.
      g[j][Cube::sideLength - i - 1] = g[Cube::sideLength - i - 1][Cube::sideLength - j - 1];
      // Bottom to left.
      g[Cube::sideLength - i - 1][Cube::sideLength - j - 1] = g[Cube::sideLength - j - 1][i];
      // Left to top.
      g[Cube::sideLength - j - 1][i] = temp;
    }
  }
}

typedef std::reference_wrapper<Color> ColorRef;
typedef std::array<ColorRef, 3> FacePortionArray;

FacePortionArray getFacePortion(
    Color grid[Cube::faceCount][Cube::sideLength][Cube::sideLength], Face f, FacePortion p, bool reverse) {
  switch (p) {
    case TOP_ROW: {
      if (reverse)
        return {grid[f][0][2], grid[f][0][1], grid[f][0][0]};
      else
        return {grid[f][0][0], grid[f][0][1], grid[f][0][2]};
    }
    case RIGHT_COL: {
      if (reverse)
        return {grid[f][2][2], grid[f][1][2], grid[f][0][2]};
      else
        return {grid[f][0][2], grid[f][1][2], grid[f][2][2]};
    }
    case BOT_ROW: {
      if (reverse)
        return {grid[f][2][2], grid[f][2][1], grid[f][2][0]};
      else
        return {grid[f][2][0], grid[f][2][1], grid[f][2][2]};
    }
    case LEFT_COL: {
      if (reverse)
        return {grid[f][2][0], grid[f][1][0], grid[f][0][0]};
      else
        return {grid[f][0][0], grid[f][1][0], grid[f][2][0]};
    }
  }
}

void rotateRingClock(Color grid[Cube::faceCount][Cube::sideLength][Cube::sideLength], Face face) {
  RingInfo info = Cube::edgeMap.at(face);

  Color temp[Cube::sideLength];

  // First to temp.
  auto[firstFace, firstPortion, firstReverse] = info[3];
  FacePortionArray first = getFacePortion(grid, firstFace, firstPortion, firstReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    temp[i] = first[i];

  // Second to first.
  auto[secondFace, secondPortion, secondReverse] = info[2];
  FacePortionArray second = getFacePortion(grid, secondFace, secondPortion, secondReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    first[i].get() = second[i].get();

  // Third to second.
  auto[thirdFace, thirdPortion, thirdReverse] = info[1];
  FacePortionArray third = getFacePortion(grid, thirdFace, thirdPortion, thirdReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    second[i].get() = third[i].get();

  // Fourth to third.
  auto[fourthFace, fourthPortion, fourthReverse] = info[0];
  FacePortionArray fourth = getFacePortion(grid, fourthFace, fourthPortion, fourthReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    third[i].get() = fourth[i].get();

  // First to fourth.
  for (size_t i = 0; i < Cube::sideLength; ++i)
    fourth[i].get() = temp[i];
}

void rotateRingAClock(Color grid[Cube::faceCount][Cube::sideLength][Cube::sideLength], Face face) {
  RingInfo info = Cube::edgeMap.at(face);

  Color temp[Cube::sideLength];

  // First to temp.
  auto[firstFace, firstPortion, firstReverse] = info[0];
  FacePortionArray first = getFacePortion(grid, firstFace, firstPortion, firstReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    temp[i] = first[i];

  // Second to first.
  auto[secondFace, secondPortion, secondReverse] = info[1];
  FacePortionArray second = getFacePortion(grid, secondFace, secondPortion, secondReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    first[i].get() = second[i].get();

  // Third to second.
  auto[thirdFace, thirdPortion, thirdReverse] = info[2];
  FacePortionArray third = getFacePortion(grid, thirdFace, thirdPortion, thirdReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    second[i].get() = third[i].get();

  // Fourth to third.
  auto[fourthFace, fourthPortion, fourthReverse] = info[3];
  FacePortionArray fourth = getFacePortion(grid, fourthFace, fourthPortion, fourthReverse);
  for (size_t i = 0; i < Cube::sideLength; ++i)
    third[i].get() = fourth[i].get();

  // First to fourth.
  for (size_t i = 0; i < Cube::sideLength; ++i)
    fourth[i].get() = temp[i];
}

} // End anonymous namespace.

Cube::Cube() : grid() {
  // Set up colors.
  for (size_t face = 0; face < faceCount; ++face) {
    auto color = static_cast<Color>(face);
    for (auto &row: grid[face]) {
      for (auto &cell: row) {
        cell = color;
      }
    }
  }
}

void Cube::rotate(Face face, enum Direction rotDir) {
  switch (rotDir) {
    case ACLOCK: {
      rotateFaceAClock(grid[face]);
      rotateRingAClock(grid, face);
      break;
    }
    case CLOCK: {
      rotateFaceClock(grid[face]);
      rotateRingClock(grid, face);
      break;
    }
  }
}

const ColorMap Cube::colorMap {
  {WHITE, color(255, 255, 255)},
  {BLUE, color(0, 0, 255)},
  {RED, color(255, 0, 0)},
  {GREEN, color(0, 255, 0)},
  {ORANGE, color(255, 128, 0)},
  {YELLOW, color(255, 255, 0)},
  {TEST, color(255, 0, 255)}
};

const RotMap Cube::rotMap {
  {UP, {90, 0}},
  {FRONT, {0, 0}},
  {LEFT, {0, -90}},
  {BACK, {0, 180}},
  {RIGHT, {0, 90}},
  {DOWN, {-90, 0}}
};

// Namespace holding edges. This circumvents an issue with directly constructing them as part of
// Cube::edgeMap. See https://stackoverflow.com/a/34708900.
namespace {
// UP
EdgeInfo up0{BACK, TOP_ROW, false};
EdgeInfo up1{RIGHT, TOP_ROW, false};
EdgeInfo up2{FRONT, TOP_ROW, false};
EdgeInfo up3{LEFT, TOP_ROW, false};

// FRONT
EdgeInfo front0{UP, BOT_ROW, true};
EdgeInfo front1{RIGHT, LEFT_COL, true};
EdgeInfo front2{DOWN, TOP_ROW, false};
EdgeInfo front3{LEFT, RIGHT_COL, false};

// LEFT
EdgeInfo left0{UP, LEFT_COL, false};
EdgeInfo left1{FRONT, LEFT_COL, false};
EdgeInfo left2{DOWN, LEFT_COL, false};
EdgeInfo left3{BACK, RIGHT_COL, true};

// BACK
EdgeInfo back0{UP, TOP_ROW, true};
EdgeInfo back1{LEFT, LEFT_COL, false};
EdgeInfo back2{DOWN, BOT_ROW, false};
EdgeInfo back3{RIGHT, RIGHT_COL, true};

// RIGHT
EdgeInfo right0{UP, RIGHT_COL, true};
EdgeInfo right1{BACK, LEFT_COL, false};
EdgeInfo right2{DOWN, RIGHT_COL, true};
EdgeInfo right3{FRONT, RIGHT_COL, true};

// DOWN
EdgeInfo down0{FRONT, BOT_ROW, false};
EdgeInfo down1{RIGHT, BOT_ROW, false};
EdgeInfo down2{BACK, BOT_ROW, false};
EdgeInfo down3{LEFT, BOT_ROW, false};

}

const EdgeMap Cube::edgeMap {
  {UP, {up0, up1, up2, up3}},
  {FRONT, {front0, front1, front2, front3}},
  {LEFT, {left0, left1, left2, left3}},
  {BACK, {back0, back1, back2, back3}},
  {RIGHT, {right0, right1, right2, right3}},
  {DOWN, {down0, down1, down2, down3}}
};
