#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>

namespace Utils {
    std::string removeWordFromString(const std::string &path, const std::string &toRemove = "build/") {
        size_t pos = path.find(toRemove);
        if (pos != std::string::npos) {
            std::string modifiedPath = path;
            modifiedPath.erase(pos, toRemove.length());
            return modifiedPath;
        }
        return path;
    }
}

#endif // UTILS_H