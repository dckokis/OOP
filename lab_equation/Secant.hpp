#pragma once

#include "Solver.hpp"

class Secant final : public SolveStrategy {
    double execute(std::function<double(double)> function, double x1, double x2, double eps,
                   std::function<double(double)> derivative) const override;
};