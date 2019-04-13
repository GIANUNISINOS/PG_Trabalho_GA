#ifndef TESTANDO_SPRITE_H
#define TESTANDO_SPRITE_H

class Sprite {
public:
    GLuint textureId;
    float offsetX;
    float offsetY;
    float z;
    float speedX;

    Sprite() {

    }

    Sprite(const char* filename, float paramOffsetX, float paramOffsetY, float paramZ, float paramSpeedX)
    {
        create_textures(filename);
        offsetX = paramOffsetX;
        offsetY = paramOffsetY;
        z = paramZ;
        speedX = paramSpeedX;
    }

    void moveX()
    {
        offsetX += speedX;
        if (offsetX > 1.00f)
            offsetX -= 1.00f;
    }

    void create_textures(const char* filename) {

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//ou GL_REPEAT GL_CLAMP_TO_BORDER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//ou GL_LINEAR GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load and generate the texture
        int charWidth, charHeight, charNrChannels;
        charNrChannels =0;

        unsigned char *data = stbi_load(filename, &charWidth, &charHeight, &charNrChannels, 0);
        //unsigned char *data = SOIL_load_image(filename, &tex_width, &tex_height, 0, SOIL_LOAD_RGBA);
        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, charWidth, charHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, nrCHANEL, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
            //SOIL_create_OGL_texture(data, tex_width, tex_height, nrCHANEL, texture, SOIL_FLAG_INVERT_Y);
        } else {
            std::cout << "Failed to load main character texture" << std::endl;
        }


        stbi_image_free(data);
        //SOIL_free_image_data(data);

    }
};
#endif //SPRITE