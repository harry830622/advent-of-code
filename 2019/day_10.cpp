#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

int ToVecCode(int vec_x, int vec_y) {
  const int vec_gcd = std::gcd(vec_x, vec_y);
  const int vec_code = 1000 * (vec_x / vec_gcd) + vec_y / vec_gcd;
  return vec_code;
}

int main() {
  std::vector<std::vector<bool>> is_asteroid_by_pos;
  std::string str;
  int y = 0;
  while (std::cin >> str) {
    is_asteroid_by_pos.push_back(std::vector<bool>(str.size(), false));
    for (int x = 0; x < str.size(); ++x) {
      if (str[x] == '#') {
        is_asteroid_by_pos[y][x] = true;
      }
    }
    ++y;
  }
  std::vector<std::vector<int>> num_detectable_asteroids_by_pos(
      is_asteroid_by_pos.size(),
      std::vector<int>(is_asteroid_by_pos[0].size(), 0));
  std::vector<std::vector<
      std::array<std::unordered_map<int, std::vector<std::pair<int, int>>>, 4>>>
      sorted_vecs_by_code_by_dim_by_pos(
          is_asteroid_by_pos.size(),
          std::vector<std::array<
              std::unordered_map<int, std::vector<std::pair<int, int>>>, 4>>(
              is_asteroid_by_pos[0].size()));
  std::vector<std::vector<
      std::array<std::unordered_map<int, std::vector<std::pair<int, int>>>, 4>>>
      sorted_vecs_by_code_by_axis_by_pos(
          is_asteroid_by_pos.size(),
          std::vector<std::array<
              std::unordered_map<int, std::vector<std::pair<int, int>>>, 4>>(
              is_asteroid_by_pos[0].size()));
  for (int org_y = 0; org_y < is_asteroid_by_pos.size(); ++org_y) {
    for (int org_x = 0; org_x < is_asteroid_by_pos[org_y].size(); ++org_x) {
      if (is_asteroid_by_pos[org_y][org_x]) {
        int& curr_num_detectable_asteroids =
            num_detectable_asteroids_by_pos[org_y][org_x];
        auto& curr_sorted_vecs_by_code_by_dim =
            sorted_vecs_by_code_by_dim_by_pos[org_y][org_x];
        auto& curr_sorted_vecs_by_code_by_axis =
            sorted_vecs_by_code_by_axis_by_pos[org_y][org_x];
        for (int curr_y = 0; curr_y < is_asteroid_by_pos.size(); ++curr_y) {
          for (int curr_x = 0; curr_x < is_asteroid_by_pos[curr_y].size();
               ++curr_x) {
            if (curr_y == org_y && curr_x == org_x) {
              continue;
            }
            const int vec_x = abs(curr_x - org_x);
            const int vec_y = abs(curr_y - org_y);
            const int vec_code = ToVecCode(vec_x, vec_y);
            if (is_asteroid_by_pos[curr_y][curr_x]) {
              if (curr_y == org_y && curr_x > org_x) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_axis[0];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_y < org_y && curr_x > org_x) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_dim[0];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_x == org_x && curr_y < org_y) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_axis[1];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_y < org_y && curr_x < org_x) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_dim[1];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_y == org_y && curr_x < org_x) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_axis[2];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_y > org_y && curr_x < org_x) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_dim[2];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_x == org_x && curr_y > org_y) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_axis[3];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              } else if (curr_y > org_y && curr_x > org_x) {
                std::unordered_map<int, std::vector<std::pair<int, int>>>&
                    curr_sorted_vecs_by_code =
                        curr_sorted_vecs_by_code_by_dim[3];
                if (curr_sorted_vecs_by_code.find(vec_code) ==
                    curr_sorted_vecs_by_code.end()) {
                  curr_sorted_vecs_by_code.insert(
                      {vec_code, std::vector<std::pair<int, int>>()});
                }
                if (curr_sorted_vecs_by_code.find(vec_code)->second.size() ==
                    0) {
                  ++curr_num_detectable_asteroids;
                }
                curr_sorted_vecs_by_code.find(vec_code)->second.push_back(
                    {vec_x, vec_y});
              }
            }
          }
        }
      }
    }
  }
  for (int curr_y = 0; curr_y < is_asteroid_by_pos.size(); ++curr_y) {
    for (int curr_x = 0; curr_x < is_asteroid_by_pos[curr_y].size(); ++curr_x) {
      auto& curr_sorted_vecs_by_code_by_dim =
          sorted_vecs_by_code_by_dim_by_pos[curr_y][curr_x];
      auto& curr_sorted_vecs_by_code_by_axis =
          sorted_vecs_by_code_by_axis_by_pos[curr_y][curr_x];
      const auto comparater = [](const std::pair<int, int>& vec_1,
                                 const std::pair<int, int>& vec_2) -> bool {
        return abs(vec_1.first) + abs(vec_1.second) <
               abs(vec_2.first) + abs(vec_2.second);
      };
      for (auto& curr_sorted_vecs_by_code : curr_sorted_vecs_by_code_by_dim) {
        for (auto& p : curr_sorted_vecs_by_code) {
          std::sort(p.second.begin(), p.second.end(), comparater);
        }
      }
      for (auto& curr_sorted_vecs_by_code : curr_sorted_vecs_by_code_by_axis) {
        for (auto& p : curr_sorted_vecs_by_code) {
          std::sort(p.second.begin(), p.second.end(), comparater);
        }
      }
    }
  }

  int max_num_detectable_asteroids = 0;
  int station_y = -1;
  int station_x = -1;
  for (int curr_y = 0; curr_y < num_detectable_asteroids_by_pos.size();
       ++curr_y) {
    for (int curr_x = 0;
         curr_x < num_detectable_asteroids_by_pos[curr_y].size(); ++curr_x) {
      if (num_detectable_asteroids_by_pos[curr_y][curr_x] >
          max_num_detectable_asteroids) {
        max_num_detectable_asteroids =
            num_detectable_asteroids_by_pos[curr_y][curr_x];
        station_x = curr_x;
        station_y = curr_y;
      }
    }
  }
  std::cout << max_num_detectable_asteroids << std::endl;

  return 0;
}
