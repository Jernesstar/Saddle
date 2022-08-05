#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

namespace Saddle {

class Font {
public:
    int Size;

public:
    Font(const std::string& font_path, int size)
        : Size(size)
    {
        m_Font = TTF_OpenFont(font_path.c_str(), size);
    }
    ~Font() { }	

    TTF_Font* GetFont() { return m_Font; }
    SDL_Surface* GetSurfaceFromText(const std::string& text, SDL_Color color)
    {
        return TTF_RenderText_Solid(m_Font, text.c_str(), color); 
    }

private:
    TTF_Font* m_Font;

};

}