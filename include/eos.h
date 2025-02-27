#ifndef EOS_H
#define EOS_H
#include <vector>
// #include <string>

double EosIso(double rho, double u); 
double EosAdi(double rho, double u); 
void GetPressure(std::vector<std::vector<double>>& particles, int nghost); 

#endif 