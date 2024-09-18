#include <iostream>
#include <fstream>
#include "Particle.hpp"
#include "VelVerlet.hpp"
#include "Utils.hpp"
#include "Quadratic.hpp"
#include "/home/anton/Downloads/eigen/Eigen/Dense"


std::ostream& operator<<(std::ostream &os, Force &force) { 
    os << force.fx << ' ' << force.fy << ' ' << force.fz << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream &os, const Quadratic &trap) { 
    os << trap.get_qform() << std::endl;

    return os;
}

int main(int argc, const char *argv[]) { 
    auto trap1 = Quadratic(Eigen::DiagonalMatrix<double, 3> {10.0, 0.0, 10.0}); 
    auto trap2 = Quadratic(Eigen::DiagonalMatrix<double, 3> {0.0, 10.0, 10.0});

    auto trap = trap1 + trap2; 

    auto engine = VelVerlet(0.001);

    std::cout << trap + trap1 << std::endl; 
    std::cout << trap2 << std::endl; 
    std::cout << (trap + trap1 == trap2) << std::endl;
 
    if (true) {
        std::ofstream outfile; 

        std::vector particles = {Particle(0, 0.5, 0), Particle(0, -0.5, 0)};

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