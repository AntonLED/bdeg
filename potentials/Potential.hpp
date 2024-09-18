#ifndef Potential_hpp
#define Potential_hpp

#include <array>
#include <vector>
#include "../utils/Force.hpp"
#include "../utils/Particle.hpp"


class Potential { 
public: 
    virtual double get_value(std::array<double, 3> coords) const = 0; 
    virtual void update_accelerations(std::vector<Particle> &particles) const = 0;
};

#endif 