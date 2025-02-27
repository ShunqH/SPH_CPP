#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

Config::Config() {}

void Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;  // Skip comments and empty lines

        // Remove '=' if it exists and split by space or '='
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            line.replace(pos, 1, " "); // Replace '=' with a space
        }

        std::istringstream iss(line);
        std::string key;
        double value;
        if (iss >> key >> value) {
            data[key] = value;
        } else {
            std::cerr << "Warning: Invalid line in config file: " << line << std::endl;
        }
    }
}

double Config::get(const std::string& key, double defaultValue) {
    return data.count(key) ? data[key] : defaultValue;
}

std::string Config::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}
