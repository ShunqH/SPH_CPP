#include <iostream>  
#include <vector>     
#include "setup.h"
#include "index.h"
#include "config.h"

using namespace std;

// vector<vector<double>> Setup(int nleft, double x0, double xmin, double xmax, double rholeft, double rhoright, double pleft, double pright, double hfact, int nghost){
vector<vector<double>> Setup(){
    
    int nleft = (int)Config::getInstance().get("nleft"); 
    double x0 = Config::getInstance().get("x0");  
    double xmin = Config::getInstance().get("xmin");  
    double xmax = Config::getInstance().get("xmax"); 
    double rholeft = Config::getInstance().get("rholeft"); 
    double rhoright = Config::getInstance().get("rhoright"); 
    double pleft = Config::getInstance().get("pleft"); 
    double pright = Config::getInstance().get("pright"); 
    double hfact = Config::getInstance().get("hfact"); 
    int nghost = (int)Config::getInstance().get("nghost"); 

    double gamma = 1.4; 
    vector<vector<double>> particles; 
    vector<double> particle(10,0);
    double dxleft = (x0-xmin)/nleft;  
    double m0 = rholeft*dxleft; 
    for (int i=0; i<nleft+nghost; i++){
        particle[X1] = xmin + 0.5*dxleft + (i-nghost)*dxleft; 
        particle[DEN] = rholeft; 
        particle[MAS] = m0 ;
        particle[VEL1] = 0. ;
        particle[LEN] = hfact*dxleft ;     // 1.2*dxleft
        particle[PRE] = pleft ;
        particle[ENE] = pleft/((gamma-1.)*rholeft) ;
        particles.push_back(particle); 
    }
    double dxright = m0/rhoright ;
    // double x = x0 + 0.5*dxright ;
    double x = x0 + 0.5*dxright;
    while (x<=xmax){
        particle[X1] = x ;
        particle[DEN] = rhoright ;
        particle[MAS] = m0 ;
        particle[VEL1] = 0. ;
        particle[LEN] = hfact*dxright  ;       //1.2*dxright
        particle[PRE] = pright ;
        particle[ENE] = pright/((gamma-1.)*rhoright) ;
        particles.push_back(particle); 
        x = x+dxright; 
    }
    for (int i=0; i<nghost; i++){
        particle[X1] = x ;
        particle[DEN] = rhoright ;
        particle[MAS] = m0 ;
        particle[VEL1] = 0. ;
        particle[LEN] = hfact*dxright  ;       //1.2*dxright
        particle[PRE] = pright ;
        particle[ENE] = pright/((gamma-1.)*rhoright) ;
        particles.push_back(particle); 
        x = x+dxright; 
    }
    return particles; 
}