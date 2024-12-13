// Created by Arija

#include "../external/glad.h"
#include <cmath>
#include <vector>

class Noise {
  public:
    double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
    double lerp(double t, double a, double b) { return a + t * (b - a); }
    double grad(int hash, double x, double y, double z);
    double perlin_noise(float x, float y, std::vector<int> &p);
    std::vector<int> get_permutation_vector();

};