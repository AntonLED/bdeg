#ifndef Parabolic_hpp 
#define Parabolic_hpp

#include <array>
#include <cmath>
#include <iostream>
#include "Potential.hpp"


class Parabolic: public Potential {
private:
    double offset, bias, scaling; 

public:
    Parabolic(): offset(0), bias(0), scaling(1) { }
    Parabolic(double offset, double bias, double scaling): 
        offset(offset), bias(bias), scaling(scaling) { }

    double get_offset() const { return offset; }
    double get_bias() const { return bias; }
    double get_scaling() const { return scaling; }

    Parabolic operator+(const Parabolic &oth) const {
        return Parabolic(offset + oth.offset, bias + oth.bias, scaling + oth.scaling);
    }

    bool operator==(const Parabolic &oth) const { 
        return (offset == oth.offset) && (bias == oth.bias) && (scaling == oth.scaling); 
    }

    double get_value(std::array<double, 3> coords) const override {
        double r2; 
        for (auto &coord: coords)
            r2 += coord * coord; 
        double r = std::sqrt(r2);

        return scaling * (r - offset) * (r - offset) + bias;  
    }

    void update_accelerations(std::vector<Particle> &particles) const override { 
        for (auto &particle: particles) { 
            double r2; 
            r2 = particle.x * particle.x + particle.y * particle.y + particle.z * particle.z; 

            double r = std::sqrt(r2);

            double _multiplier = 0.0; 
            
            if (r > 0)
                _multiplier = -2 * scaling * (r - offset) / r; 

            particle.ax = _multiplier * particle.x; 
            particle.ay = _multiplier * particle.y; 
            particle.az = _multiplier * particle.z;
        }

    }
};


#endif