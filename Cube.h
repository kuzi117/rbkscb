#ifndef RBKSCB_CUBE_H
#define RBKSCB_CUBE_H

#include <array>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include <vector>

struct color {
  color() = delete;
  color(uint8_t r, uint8_t g, uint8_t b) : vals {r, g, b} { }

  const uint8_t vals[3];
};

enum Face : uint8_t {
  UP,
  FRONT,
  LEFT,
  BACK,
  RIGHT,
  DOWN,
};

enum Color : uint8_t {
  WHITE,
  BLUE,
  RED,
  GREEN,
  ORANGE,
  YELLOW,
  TEST
};

enum Direction : uint8_t {
  CLOCK,
  ACLOCK
};

enum FacePortion : uint8_t {
  TOP_ROW,
  RIGHT_COL,
  BOT_ROW,
  LEFT_COL
};

typedef std::unordered_map<Color, color> ColorMap;
typedef std::unordered_map<Color, std::size_t> FaceMap;
typedef std::pair<float, float> RotPair;
typedef std::unordered_map<Face, RotPair> RotMap;
typedef std::tuple<Face, FacePortion, bool> EdgeInfo;
typedef std::array<EdgeInfo, 4> RingInfo;
typedef std::unordered_map<Face, RingInfo> EdgeMap;

class Cube {
public:
  Cube();

  void rotate(Face face, Direction rotDir);

  static const ColorMap colorMap;
  static const RotMap rotMap;
  static const EdgeMap edgeMap;

  static constexpr std::size_t faceCount = 6;
  static constexpr std::size_t sideLength = 3;
  Color grid[faceCount][sideLength][sideLength];
};

#endif // RBKSCB_CUBE_H
