#ifndef FORCE_H
#define FORCE_H 
#include <vector>

void GetVisco(std::vector<double> para, std::vector<double> parb, double& qa, double& qb);
void GetAccel(std::vector<std::vector<double>>& particles, int nghost); 

#endif 