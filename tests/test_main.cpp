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
    auto trap = Quadratic(Eigen::Matrix3d::Random(3,3)); 
    auto trap1 = Quadratic(Eigen::Matrix3d::Random(3,3));

    auto trap2 = trap + trap1; 

    auto engine = VelVerlet(0.001);

    std::cout << trap + trap1 << std::endl; 
    std::cout << trap2 << std::endl; 
    std::cout << (trap + trap1 == trap2) << std::endl;

    // if (false) {
    //     std::ofstream outfile; 

    //     std::vector particles = {Particle(0, 0.5, 1), Particle(0, -0.5, 1)};

    //     engine.make_step(particles, trap, true);
    //     for (unsigned i = 0; i < 100'000; i++) { 
    //         if (i % 100 == 0) {
    //             outfile.open("/home/anton/bdeg/snapshots/snap_" + std::to_string(i) + ".xyz");
    //             utils::report_particles(particles, outfile);
    //             outfile.close();
    //         }
    //         engine.make_step(particles, trap);
    //     }

    //     utils::report_particles(particles, std::cout);
    // }
    
    return 0; 
}