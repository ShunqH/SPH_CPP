#include <iostream>  
#include <vector>     
#include "setup.h"
#include "index.h"
#include "utils.h"
#include "dens.h"
#include "force.h"
#include "evolve.h"
#include "config.h"

using namespace std;

int main(int argc, char* argv[]){

    double dt, t, tmax, dtoutput; 
    int step = 0; 
    int nghost; 

    if (argc < 3 || std::string(argv[1]) != "-i") {
        std::cerr << "Usage: " << argv[0] << " -i input.in" << std::endl;
        return 1;
    }
    Config::getInstance().loadFromFile(argv[2]);

    vector<vector<double>> particles = Setup(); 

    dt = Config::getInstance().get("dt"); 
    tmax = Config::getInstance().get("tmax"); 
    dtoutput = Config::getInstance().get("dtoutput"); 
    nghost = (int)Config::getInstance().get("nghost"); 
    
    t = 0; 
    int interval = dtoutput/dt; 
    WriteParticles(particles, step); 
    while (t<tmax){
        Integral(particles, nghost, dt); 
        t = t+dt; 
        step++; 
        if (step%interval == 0){
            WriteParticles(particles, step/interval); 
        }    
    }
    
    return 0; 
}

