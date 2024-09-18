#ifndef Force_hpp
#define Force_hpp


struct Force { 
    double fx;
    double fy; 
    double fz; 

    Force(double fx, double fy, double fz):
        fx(fx), fy(fy), fz(fz) { }
}; 


#endif