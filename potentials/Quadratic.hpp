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
    Quadratic(): qform(Eigen::Matrix3d::Identity()) { }
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
            Eigen::Vector3d force = -(qform.transpose() + qform) * Eigen::Vector3d(particle.x, particle.y, particle.z);

            particle.ax = force(0) / particle.m; 
            particle.ay = force(1) / particle.m; 
            particle.az = force(2) / particle.m;
        }
    }
};


#endif