#ifndef Utils_hpp
#define Utils_hpp

#include <vector>
#include <iostream>
#include "Particle.hpp"


namespace utils {
    void report_particles(const std::vector<Particle> &particles, std::ostream &os) { 
        os << particles.size() << std::endl; 
        os << "fckmpls" << std::endl; 

        for (auto &particle: particles) 
            os << 
                particle.x << " " << particle.y << " " << particle.z << " " << 
                particle.vx << " " << particle.vy << " " << particle.vz << " " <<
                std::endl;
    }

    
}


#endif 