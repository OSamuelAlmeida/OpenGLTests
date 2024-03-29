#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string &path);
    ~Texture();

    void bind(unsigned int slot = 0);

private:
    unsigned int id;

    void load(const std::string &path);
};
