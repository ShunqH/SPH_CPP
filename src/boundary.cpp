#include <vector> 
#include "index.h"
using namespace std; 

// fixed boundary condition
void SetGhost(std::vector<std::vector<double>>& particles, int nghost){
    for (int i=0; i<nghost; i++){
        particles[i] = particles[i]; 
        particles[particles.size()-nghost+i] = particles[particles.size()-nghost+i]; 
    }
    return; 
}
