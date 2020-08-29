
#pragma once

#include "EngineCommon.h"

namespace Game
{

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

private:
    unsigned int rendererId;
    std::string filepath;
    unsigned char* buffer;
    int width, height, bpp;
};

}