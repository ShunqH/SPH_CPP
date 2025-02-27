#ifndef DENS_H
#define DENS_H 
#include <vector>

double F_kernel(double q); 
double F_kernel_p(double q); 
double W_1order(double ra, double rb, double h); 
double W_1order_p(double ra, double rb, double h); 
void GetDensity(std::vector<std::vector<double>>& particles, int nghost); 
void Smoothing(std::vector<std::vector<double>>& particles); 

#endif 