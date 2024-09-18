#include <iostream>
#include <fstream>
#include "Particle.hpp"
#include "VelVerlet.hpp"
#include "Utils.hpp"
#include "Parabolic.hpp"


std::ostream& operator<<(std::ostream &os, Force &force) { 
    os << force.fx << ' ' << force.fy << ' ' << force.fz << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream &os, const Parabolic &trap) { 
    os << trap.get_scaling() << " * " << '(' << 'r' << " - " << trap.get_offset() << ')' << '^' << "2" << " - " << trap.get_bias() << std::endl;

    return os;
}

int main(int argc, const char *argv[]) { 
    auto trap = Parabolic(0, 0, 1); 
    auto trap1 = Parabolic(1, 1, 1);

    auto trap2 = trap + trap1; 

    auto engine = VelVerlet(0.001);

    std::cout << trap + trap1; 
    std::cout << trap2; 

    if (false) {
        std::ofstream outfile; 

        std::vector particles = {Particle(0, 0.5, 1), Particle(0, -0.5, 1)};

        engine.make_step(particles, trap, true);
        for (unsigned i = 0; i < 100'000; i++) { 
            if (i % 100 == 0) {
                outfile.open("/home/anton/bdeg/snapshots/snap_" + std::to_string(i) + ".xyz");
                utils::report_particles(particles, outfile);
                outfile.close();
            }
            engine.make_step(particles, trap);
        }

        utils::report_particles(particles, std::cout);
    }
    
    return 0; 
}