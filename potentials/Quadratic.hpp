#ifndef Quadratic_hpp 
#define Quadratic_hpp

#include <array>
#include <cmath>
#include <iostream>
#include "/home/anton/Downloads/eigen/Eigen/Dense"
#include "Potential.hpp"


class Quadratic: public Potential {
private: 
    Eigen::Matrix3d qform;

public:
    Quadratic(): qform(Eigen::Matrix3d::Constant(1.0, 1.0, 1.0)) { }
    Quadratic(Eigen::Matrix3d qform): qform(qform) { }

    Eigen::Matrix3d get_qform() const { return qform; }

    Quadratic operator+(const Quadratic &oth) const {
        return Quadratic(qform + oth.qform);
    }

    bool operator==(const Quadratic &oth) const { 
        return qform == oth.qform;
    }

    void update_accelerations(std::vector<Particle> &particles) const override { 
        for (auto &particle: particles) { 
            // TODO!
            bool TODO = false;
        }

    }
};


#endif