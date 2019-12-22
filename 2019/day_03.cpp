#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <boost/tokenizer.hpp>

using Segment = std::tuple<int, int, int>;
using Segments = std::vector<Segment>;
using Point = std::pair<int, int>;

std::vector<std::string> ToTokens(const std::string& str) {
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokenizer(str, sep);
  std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());
  return tokens;
}

std::pair<Segments, Segments> ToSegments(const std::vector<std::string>& tokens) {
  std::pair<Segments, Segments> v_and_h_segments;
  Point curr_pos{0, 0};
  Point next_pos{0, 0};
  for (const std::string& token : tokens) {
    const char dir = token[0];
    const int dist = std::stoi(token.substr(1));
    switch (dir) {
      case 'R': {
        next_pos.first = curr_pos.first + dist;
        break;
      }
      case 'L': {
        next_pos.first = curr_pos.first - dist;
        break;
      }
      case 'U': {
        next_pos.second = curr_pos.second + dist;
        break;
      }
      case 'D': {
        next_pos.second = curr_pos.second - dist;
        break;
      }
      default: {
        std::cerr << "Invalid direction: " << dir << std::endl;
        break;
      }
    }
    if (next_pos.first == curr_pos.first) {
      v_and_h_segments.first.push_back({curr_pos.first, curr_pos.second, next_pos.second});
    } else if (next_pos.second == curr_pos.second) {
      v_and_h_segments.second.push_back({curr_pos.second, curr_pos.first, next_pos.first});
    } else {
      std::cerr << "WTF" << std::endl;
    }
    curr_pos = next_pos;
  }
  /* std::sort(v_and_h_segments.first.begin(), v_and_h_segments.first.end(), [](const auto& segment_a, const auto& segment_b) -> bool { return std::get<0>(segment_a) < std::get<0>(segment_b); }); */
  /* std::sort(v_and_h_segments.second.begin(), v_and_h_segments.second.end(), [](const auto& segment_a, const auto& segment_b) -> bool { return std::get<0>(segment_a) < std::get<0>(segment_b); }); */
  return v_and_h_segments;
}

std::vector<Point> FindIntersections(const Segments& v_segments, const Segments& h_segments) {
  std::vector<Point> intersections;
  for (const Segment& v_seg : v_segments) {
    for (const Segment& h_seg : h_segments) {
      const int v_seg_x = std::get<0>(v_seg);
      const int v_seg_min_y = std::min(std::get<1>(v_seg), std::get<2>(v_seg));
      const int v_seg_max_y = std::max(std::get<1>(v_seg), std::get<2>(v_seg));
      const int h_seg_y = std::get<0>(h_seg);
      const int h_seg_min_x = std::min(std::get<1>(h_seg), std::get<2>(h_seg));
      const int h_seg_max_x = std::max(std::get<1>(h_seg), std::get<2>(h_seg));
      if (v_seg_x > h_seg_min_x && v_seg_x < h_seg_max_x && h_seg_y > v_seg_min_y && h_seg_y < v_seg_max_y) {
        intersections.push_back({v_seg_x, h_seg_y});
      }
    }
  }
  return intersections;
}

int computeNumSteps(const std::vector<std::string>& tokens, const Point& dest_pos) {
  int num_steps = 0;
  bool isMet = false;
  Point curr_pos{0, 0};
  Point next_pos{0, 0};
  for (const std::string& token : tokens) {
    const char dir = token[0];
    const int dist = std::stoi(token.substr(1));
    switch (dir) {
      case 'R': {
        next_pos.first = curr_pos.first + dist;
        if (curr_pos.second == dest_pos.second && dest_pos.first > curr_pos.first && dest_pos.first <= next_pos.first) {
          num_steps += dest_pos.first - curr_pos.first;
          isMet = true;
        }
        break;
      }
      case 'L': {
        next_pos.first = curr_pos.first - dist;
        if (curr_pos.second == dest_pos.second && dest_pos.first < curr_pos.first && dest_pos.first >= next_pos.first) {
          num_steps += curr_pos.first - dest_pos.first;
          isMet = true;
        }
        break;
      }
      case 'U': {
        next_pos.second = curr_pos.second + dist;
        if (curr_pos.first == dest_pos.first && dest_pos.second > curr_pos.second && dest_pos.second <= next_pos.second) {
          num_steps += dest_pos.second - curr_pos.second;
          isMet = true;
        }
        break;
      }
      case 'D': {
        next_pos.second = curr_pos.second - dist;
        if (curr_pos.first == dest_pos.first && dest_pos.second < curr_pos.second && dest_pos.second >= next_pos.second) {
          num_steps += curr_pos.second - dest_pos.second;
          isMet = true;
        }
        break;
      }
      default: {
        std::cerr << "Invalid direction: " << dir << std::endl;
        break;
      }
    }
    if (isMet) {
      break;
    }
    num_steps += dist;
    curr_pos = next_pos;
  }
  return num_steps;
}

int main() {
  std::string wire_1;
  std::string wire_2;
  std::cin >> wire_1;
  std::cin >> wire_2;
  const auto wire_1_tokens = ToTokens(wire_1);
  const auto wire_2_tokens = ToTokens(wire_2);
  const auto wire_1_v_and_h_segments = ToSegments(wire_1_tokens);
  const auto wire_2_v_and_h_segments = ToSegments(wire_2_tokens);
  std::vector<Point> intersections = FindIntersections(wire_1_v_and_h_segments.first, wire_2_v_and_h_segments.second);
  std::vector<Point> intersections_2 = FindIntersections(wire_2_v_and_h_segments.first, wire_1_v_and_h_segments.second);
  intersections.insert(intersections.end(), intersections_2.begin(), intersections_2.end());
  int min_dist = std::numeric_limits<int>::max();
  for (const Point& intersec : intersections) {
    /* const int dist = std::abs(intersec.first) + std::abs(intersec.second); */
    const int dist = computeNumSteps(wire_1_tokens, intersec) + computeNumSteps(wire_2_tokens, intersec);
    if (dist < min_dist) {
      min_dist = dist;
    }
  }
  std::cout << min_dist << std::endl;

  return 0;
}
