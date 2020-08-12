#include "solver.h"

#include <limits>
#include <math.h>

using namespace std;

#define NO_SOLUTION std::numeric_limits<float>::min()

size_t Solver::solve_quadratic(float a, float b, float c, array<float, 2>& t) {
    float delta((b * b) - (4 * a * c));

    if(delta < 0) {
        return 0;
    } else if(delta == 0) {
        t[0] = (-b) / (2 * a);
        return 1;
    } else {
        float sol_1(((-b) + sqrt(delta)) / (2 * a));
        float sol_2(((-b) - sqrt(delta)) / (2 * a));

        t[0] = sol_1;
        t[1] = sol_2;

        return 2;
    }
}