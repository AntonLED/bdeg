#ifndef VelVerlet_hpp
#define VelVerlet_hpp

#include <vector>
#include "../utils/Force.hpp"
#include "../utils/Particle.hpp"
#include "../potentials/Potential.hpp"


class VelVerlet { 
private: 
    double dt;

public:
    VelVerlet(): dt(.001) { }
    VelVerlet(double dt): dt(dt) { }

    void make_step(std::vector<Particle> &particles, const Potential &potential, bool is_first = false) { 
        if (is_first) 
            potential.update_accelerations(particles);

        for (auto &particle: particles) { 
            particle.x += particle.vx * dt + 0.5 * particle.ax * dt * dt; 
            particle.y += particle.vy * dt + 0.5 * particle.ay * dt * dt; 
            particle.z += particle.vz * dt + 0.5 * particle.az * dt * dt; 

            particle.vx += 0.5 * particle.ax * dt; 
            particle.vy += 0.5 * particle.ay * dt; 
            particle.vz += 0.5 * particle.az * dt; 
        }

        potential.update_accelerations(particles); 

        for (auto &particle: particles) { 
            particle.vx += 0.5 * particle.ax * dt; 
            particle.vy += 0.5 * particle.ay * dt; 
            particle.vz += 0.5 * particle.az * dt; 
        }
    }     
};


#endif