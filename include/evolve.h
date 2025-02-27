#ifndef EVOLVE_H
#define EVOLVE_H 
#include <vector>

void Derivs(std::vector<std::vector<double>>& particles, int nghost); 
void Integral(std::vector<std::vector<double>>& particles, int nghost, double dt); 

#endif 