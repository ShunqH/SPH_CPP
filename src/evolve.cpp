#include <vector>
#include "evolve.h"
#include "dens.h" 
#include "eos.h"
#include "force.h"
#include "boundary.h"
#include "index.h"
using namespace std; 

void Derivs(std::vector<std::vector<double>>& particles, int nghost){
    const int n_smooth=10; 
    SetGhost(particles, nghost); 
    for (int i=0; i<n_smooth; i++){
        GetDensity(particles, nghost); 
        Smoothing(particles); 
    }
    GetPressure(particles, nghost); 
    GetAccel(particles, nghost); 
    SetGhost(particles, nghost); 
    return; 
}

void Integral(std::vector<std::vector<double>>& particles, int nghost, double dt){
    int n = particles.size(); 
    vector<double> vhalf(n); 
    vector<double> uhalf(n);
    for (int a=nghost; a<n-nghost; a++){
        particles[a][X1] = particles[a][X1] + dt*particles[a][VEL1] 
                         + 0.5*dt*dt*particles[a][ACC1];
        vhalf[a] = particles[a][VEL1] + 0.5*dt*particles[a][ACC1];
        uhalf[a] = particles[a][ENE]  + 0.5*dt*particles[a][ACCU];
    } 
    Derivs(particles, nghost);
    for (int a=nghost; a<n-nghost; a++){
        particles[a][VEL1] = vhalf[a] + 0.5*dt*particles[a][ACC1]; 
        particles[a][ENE] = uhalf[a] + 0.5*dt*particles[a][ACCU]; 
    } 
    return; 
}