#pragma once

struct Position
{
  int x_pos;
  int y_pos;

  bool operator==(std::vector<Position>::const_reference position) const = default;
};