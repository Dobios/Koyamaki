#pragma once

#include <array>

using namespace std;

class Solver {
public:
    /**
     * @brief Solves a quadratic equation of the form ax² + bx + c = 0
     * @param a, the value the square coefficient
     * @param b, the value of the linear coefficient
     * @param c, the constant coefficient
     * @param t, an array in which we will store our solutions
     * @returns the number of solutions found
     */
    static size_t solve_quadratic(float a, float b, float c, array<float, 2>& t);
};