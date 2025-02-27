#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip> 
#include <iostream>
#include <string>
#include "utils.h" 
using namespace std;

void WriteParticles(vector<vector<double>> particles, int step){
    int rows = particles.size(); 
    int cols = particles[0].size(); 

    // string Path = "./output/"; 
    ostringstream filename_stream;
    filename_stream << "output_" << setw(5) << setfill('0') << step;  
    string filename = filename_stream.str(); 

    ofstream outFile(filename, ios::binary);

    // write rows and cols
    outFile.write(reinterpret_cast<char*>(&rows), sizeof(rows));
    outFile.write(reinterpret_cast<char*>(&cols), sizeof(cols));

    // write data
    for (int i = 0; i < rows; ++i) {
        outFile.write(reinterpret_cast<char*>(particles[i].data()), cols*sizeof(double));
    }

    outFile.close();

    return; 
}