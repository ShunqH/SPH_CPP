#include <vector>
#include <iostream>
#include <cmath>
#include "force.h"
#include "index.h"
#include "dens.h" 
#include "config.h"
using namespace std; 

void GetVisco(vector<double> para, vector<double> parb, double& qa, double& qb){
    double alpha = Config::getInstance().get("alpha"); 
    double beta = Config::getInstance().get("beta");
    double vab = para[VEL1] - parb[VEL1]; 
    double vdotr = 0; 
    // cout<<alpha<<endl; 
    if (para[X1]!=parb[X1]){
        vdotr = vab*(para[X1]-parb[X1])/fabs(para[X1]-parb[X1]); 
    }
    if (vdotr<0){
        double nu_siga = alpha * para[SPE] - beta*vdotr; 
        double nu_sigb = alpha * parb[SPE] - beta*vdotr; 
        qa = -0.5*para[DEN]*nu_siga*vdotr; 
        qb = -0.5*parb[DEN]*nu_sigb*vdotr; 
    }
    else{
        qa = 0; 
        qb = 0; 
    }
    return; 
}

void GetAccel(std::vector<std::vector<double>>& particles, int nghost){
    int n = particles.size(); 
    // cout<<1<<endl;
    double acc = 0; 
    double accu = 0; 
    double qa, qb, wha, whb; 
    for (int a=nghost; a<n-nghost; a++){
        acc = 0; 
        accu = 0; 
        for (int b=0; b<n; b++){
            qa = 0; 
            qb = 0; 
            GetVisco(particles[a], particles[b], qa, qb ); 
            wha = W_1order_p(particles[a][X1], particles[b][X1], particles[a][LEN]); 
            whb = W_1order_p(particles[a][X1], particles[b][X1], particles[b][LEN]); 
            acc += - particles[b][MAS]*
                    (((particles[a][PRE]+qa)/(particles[a][DEN]*particles[a][DEN]))*wha 
                    +((particles[b][PRE]+qb)/(particles[b][DEN]*particles[b][DEN]))*whb); 
            accu += particles[b][MAS]
                    *((particles[a][PRE]+qa)/(particles[a][DEN]*particles[a][DEN]))
                    *(particles[a][VEL1]-particles[b][VEL1])*wha ; 
        }
        particles[a][ACC1] = acc; 
        particles[a][ACCU] = accu; 
    }
    return; 
}