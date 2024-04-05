#include "Text.h"

Text::Text2D::Text2D(std::string fontPath)
{
    // freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::Text.cpp: Could not init freetype library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        std::cout << "ERROR::Text.cpp: Failed to load font: " << fontPath << std::endl;

    // set width to 0 so freetype calculates it automatically corresponding to the height
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    // store first 128 ascii characters in Characters map
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::Text.cpp: Failed to load glyph " << c << std::endl;
            continue;
        }

        // generate Texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        m_Characters.insert(std::pair<char, Character>(c, character));
    }

    // clear freetype's resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // enable 4 bit color values again (most texture have it just not the freetype one's)

    // set up VAO and VBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Text::Text2D::~Text2D()
{

}

void Text::Text2D::RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    s.Bind();
    s.SetUniformVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = m_Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos,     ypos,     0.0f, 1.0f },
            { xpos + w, ypos,     1.0f, 1.0f },

            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos + w, ypos,     1.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 0.0f }
        };
        // render the glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Text::Font::Font()
{
    
}

Text::Font::Font(const std::string& path)
{
    loadFont(path);
}

Text::Font::~Font()
{

}

void Text::Font::loadFont(const std::string& path)
{
    // freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::Text.cpp: Could not init freetype library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face))
        std::cout << "ERROR::Text.cpp: Failed to load font: " << path << std::endl;

    // set width to 0 so freetype calculates it automatically corresponding to the height
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    // store first 128 ascii characters in Characters map
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::Text.cpp: Failed to load glyph " << c << std::endl;
            continue;
        }

        // generate Texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    // clear freetype's resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // enable 4 bit color values again (most texture have it just not the freetype one's)
}

Text::TextComponent::TextComponent(std::string fontPath)
    : m_Text(""), m_Position(0.0f, 0.0f), m_Scale(1.0f), m_Color(1.0f, 1.0f, 1.0f),
    m_Width(0.0f), m_Height(0.0f)
{
    // freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::Text.cpp: Could not init freetype library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        std::cout << "ERROR::Text.cpp: Failed to load font: " << fontPath << std::endl;

    // set width to 0 so freetype calculates it automatically corresponding to the height
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    // store first 128 ascii characters in Characters map
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::Text.cpp: Failed to load glyph " << c << std::endl;
            continue;
        }

        // generate Texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        m_Characters.insert(std::pair<char, Character>(c, character));
    }

    // clear freetype's resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // enable 4 bit color values again (most texture have it just not the freetype one's)

    // set up VAO and VBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
Text::TextComponent::TextComponent(std::string fontPath, std::string text)
    : m_Text(text), m_Position(0.0f, 0.0f), m_Scale(1.0f), m_Color(1.0f, 1.0f, 1.0f),
    m_Width(0.0f), m_Height(0.0f)
{
    // freetype
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::Text.cpp: Could not init freetype library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        std::cout << "ERROR::Text.cpp: Failed to load font: " << fontPath << std::endl;

    // set width to 0 so freetype calculates it automatically corresponding to the height
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    // store first 128 ascii characters in Characters map
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::Text.cpp: Failed to load glyph " << c << std::endl;
            continue;
        }

        // generate Texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        m_Characters.insert(std::pair<char, Character>(c, character));
    }

    // clear freetype's resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // enable 4 bit color values again (most texture have it just not the freetype one's)

    // set up VAO and VBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    CalcWidthAndHeight();
}
Text::TextComponent::TextComponent(Font* font)
    : m_Text(""), m_Position(0.0f, 0.0f), m_Scale(1.0f), m_Color(1.0f, 1.0f, 1.0f),
m_Width(0.0f), m_Height(0.0f)
{
    m_Font = font;

    // set up VAO and VBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
Text::TextComponent::~TextComponent()
{

}

void Text::TextComponent::SetPosition(glm::vec2 position)
{
    m_Position = position;
}
void Text::TextComponent::SetScale(float scale)
{
    m_Scale = scale;
    CalcWidthAndHeight();
}
void Text::TextComponent::SetColor(glm::vec3 color)
{
    m_Color = color;
}
void Text::TextComponent::SetText(std::string text)
{
    m_Text = text;
    CalcWidthAndHeight();
}

void Text::TextComponent::Draw(Shader& s)
{
    // activate corresponding render state
    s.Bind();
    s.SetUniformVec3("textColor", m_Color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    float x = m_Position.x;
    float y = m_Position.y;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = m_Text.begin(); c != m_Text.end(); c++)
    {
        Character ch = m_Font->characters[*c];

        // don't add bearing for first glyph because the first one can be directly on the left edge of the bounding box
        // no space needed between left edge of box and glyph
        float xpos;
        if (c == m_Text.begin())
            xpos = x;
        else
            xpos = x + ch.Bearing.x * m_Scale;

        float ypos = y - (ch.Size.y - ch.Bearing.y) * m_Scale;

        float w = ch.Size.x * m_Scale;
        float h = ch.Size.y * m_Scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos,     ypos,     0.0f, 1.0f },
            { xpos + w, ypos,     1.0f, 1.0f },

            { xpos,     ypos + h, 0.0f, 0.0f },
            { xpos + w, ypos,     1.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 0.0f }
        };
        // render the glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * m_Scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::TextComponent::CalcWidthAndHeight()
{
    float width = 0.0f, maxHeight = 0.0f;
    std::string::const_iterator c;
    for (c = m_Text.begin(); c != m_Text.end(); c++)
    {
        Character ch = m_Font->characters[*c];

        // if it's not the last glyph we can say that the width of the glyph is advance,
        // because advance the space between the origins of the glyphs
        if (c != m_Text.end() - 1)
            width += (ch.Advance >> 6) * m_Scale;
        // for the last glyph we don't want to add the bearing of the end to the bounding box because the last glyphs end
        // should be on the right edge of the bounding box
        else
        {
            // add the normal width of the glyph
            width += ch.Size.x * m_Scale;
            // add the bearing between origin and start of glyph as well
            // but not the bearing between end of glyph and next origin because it's the last one
            width += ch.Bearing.x * m_Scale;
        }
        // only the tallest glyph's height is needed (height doesn't add up)
        if (ch.Size.y * m_Scale > maxHeight)
            maxHeight = ch.Size.y * m_Scale;
    }
    m_Width = width;
    m_Height = maxHeight;
}