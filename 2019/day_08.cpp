#include <array>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string str;
  std::cin >> str;

  const int img_width = 25;
  const int img_height = 6;
  const int img_res = img_width * img_height;
  const int num_img_layers = str.size() / img_res;
  std::vector<std::array<int, img_res>> pixels_by_img_layer_idx(num_img_layers);
  std::vector<std::array<int, 10>> num_digits_by_img_layer_idx(num_img_layers);
  for (int i = 0; i < str.size(); ++i) {
    const int d = static_cast<int>(str[i]) - static_cast<int>('0');
    pixels_by_img_layer_idx[i / img_res][i % img_res] = d;
    ++num_digits_by_img_layer_idx[i / img_res][d];
  }
  int img_layer_idx_with_fewest_zeros = 0;
  for (int i = 1; i < num_digits_by_img_layer_idx.size(); ++i) {
    if (num_digits_by_img_layer_idx[i][0] <
        num_digits_by_img_layer_idx[img_layer_idx_with_fewest_zeros][0]) {
      img_layer_idx_with_fewest_zeros = i;
    }
  }
  std::cout
      << num_digits_by_img_layer_idx[img_layer_idx_with_fewest_zeros][1] *
             num_digits_by_img_layer_idx[img_layer_idx_with_fewest_zeros][2]
      << std::endl;

  std::array<int, img_res> img_pixels;
  for (int i = 0; i < img_res; ++i) {
    int curr_img_layer_idx = 0;
    while (pixels_by_img_layer_idx[curr_img_layer_idx][i] == 2) {
      ++curr_img_layer_idx;
    }
    img_pixels[i] = pixels_by_img_layer_idx[curr_img_layer_idx][i];
  }
  for (int y = 0; y < img_height; ++y) {
    for (int x = 0; x < img_width; ++x) {
      std::cout << (img_pixels[y * img_width + x] == 1 ? 'X' : ' ');
    }
    std::cout << std::endl;
  }

  return 0;
}
