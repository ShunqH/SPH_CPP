#include <iostream>  
#include <vector>     
#include <cmath>
#include <algorithm> 
#include "index.h"
#include "utils.h"
#include "dens.h"
#include "config.h"
using namespace std;

double F_kernel(double q){
    if (q>=0 && q<1){
        return 1-1.5*q*q+0.75*q*q*q;
    }else if (q>=1 && q<2){
        return 0.25*(2-q)*(2-q)*(2-q); 
    }else{
        return 0;
    }
}

double F_kernel_p(double q){
    if (q>=0 && q<1){
        return -3.*q + 3*0.75*q*q;
    }else if (q>=1 && q<2){
        return -0.75*(2-q)*(2-q); 
    }else{
        return 0;
    }
}

double W_1order(double ra, double rb, double h){
    double q = fabs(ra-rb)/h; 
    return (2./3.)*F_kernel(q)/h; 
}

double W_1order_p(double ra, double rb, double h){
    double q = fabs(ra-rb)/h; 
    if (ra==rb){
        return 0; 
    }else{
        return ((ra-rb)/fabs(ra-rb))*(2./3.)*F_kernel_p(q)/(h*h); 
    }
}

void GetDensity(std::vector<std::vector<double>>& particles, int nghost=0){
    int n = particles.size(); 
    for (int i=nghost; i<n-nghost; i++){
        particles[i][DEN] = 0; 
        for (int j=0; j<n; j++){
            particles[i][DEN] += particles[j][MAS]*W_1order(particles[i][X1], particles[j][X1], particles[i][LEN]); 
        }
    }
    return; 
}

void Smoothing(std::vector<std::vector<double>>& particles){
    double hfact = Config::getInstance().get("hfact"); 
    for (int i=0; i<particles.size(); i++){
        double new_len = hfact*(particles[i][MAS]/particles[i][DEN]);
        particles[i][LEN] = max(new_len, 1e-5);  
        // particles[i][LEN] = hfact*(particles[i][MAS]/particles[i][DEN]); 
    }
} 