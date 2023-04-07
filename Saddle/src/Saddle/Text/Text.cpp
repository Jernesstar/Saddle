#include "Text.h"

namespace Saddle {

void Text::SetText(const std::string& text, const Font& font)
{
    m_Quads.reserve(text.size());

    float x = 0.0f, y = 0.0f;
    for(auto c = text.begin(); c != text.end(); c++)
    {
        const Font::Character& ch = font.GetCharacter(*c);

        float xpos = x + ch.Bearing.x;
        float ypos = y - (ch.Size.y - ch.Bearing.y);

        float w = ch.Size.x;
        float h = ch.Size.y;

        CharacterQuad quad;
        quad.Character = ch;
        quad.Vertices[0] = { xpos,     ypos,    };
        quad.Vertices[1] = { xpos + w, ypos,    };
        quad.Vertices[2] = { xpos,     ypos + h };
        quad.Vertices[3] = { xpos + w, ypos + h };

        m_Quads.push_back(quad);
        x += (ch.Advance >> 6);
    }
}

}