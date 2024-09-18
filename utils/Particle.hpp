#ifndef Particle_hpp
#define Particle_hpp


struct Particle {
    double m; 
    double x, y, z; 
    double vx, vy, vz; 
    double ax, ay, az; 

    Particle(): 
        m(.1),
        x(.0), y(.0), z(.0),  
        vx(.0), vy(.0), vz(.0), 
        ax(.0), ay(.0), az(.0) { }

    Particle(double x, double y, double z):
        m(.1),
        x(x), y(y), z(z),  
        vx(.0), vy(.0), vz(.0), 
        ax(.0), ay(.0), az(.0) { }
};


#endif