#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
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

    std::vector<std::string> splitIntoLines(const std::string &text, int maxWidth, TTF_Font *font)
    {
        std::vector<std::string> lines;
        std::string currentLine;
        std::string word;
        int width = 0;

        for (char c : text)
        {
            if (c == ' ' || c == '\n')
            {
                if (!word.empty())
                {
                    int wordWidth;
                    TTF_SizeText(font, word.c_str(), &wordWidth, nullptr);

                    if (width + wordWidth > maxWidth)
                    {
                        lines.push_back(currentLine);
                        currentLine = word + " ";
                        width = wordWidth + TTF_FontHeight(font);
                    }
                    else
                    {
                        currentLine += word + " ";
                        width += wordWidth + TTF_FontHeight(font);
                    }
                    word.clear();
                }
                if (c == '\n')
                {
                    lines.push_back(currentLine);
                    currentLine.clear();
                    width = 0;
                }
            }
            else
            {
                word += c;
            }
        }

        if (!currentLine.empty() || !word.empty())
        {
            currentLine += word;
            lines.push_back(currentLine);
        }

        return lines;
    }
}

#endif // UTILS_H