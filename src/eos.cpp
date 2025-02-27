#include <vector>
#include <cmath>
#include "eos.h"
#include "index.h"
#include "config.h"
using namespace std; 

double EosIso(double rho, double u){
    double cs = 1.0; 
    return cs*cs*rho; 
}

double EosAdi(double rho, double u){
    double gamma = Config::getInstance().get("gamma"); 
    double cs2 = (gamma-1.)*u; 
    return cs2*rho; 
}

void GetPressure(vector<vector<double>>& particles, int nghost){
    int n = particles.size(); 
    int eosid = (int)Config::getInstance().get("EoS"); 
    if (eosid==0){
        for (int i=nghost; i<n-nghost; i++){
            particles[i][PRE] = EosAdi(particles[i][DEN], particles[i][ENE]); 
            particles[i][SPE] = sqrt(particles[i][PRE]/particles[i][DEN]); 
        }
    }else if (eosid==1){
        for (int i=nghost; i<n-nghost; i++){
            particles[i][PRE] = EosIso(particles[i][DEN], particles[i][ENE]); 
            particles[i][SPE] = sqrt(particles[i][PRE]/particles[i][DEN]); 
        }
    }
    return; 
}