#ifndef TESTANDO_SPRITE_H 
#define TESTANDO_SPRITE_H
#endif

class Sprite {
public:
    GLuint textureId;
    float offsetX;
    float offsetY;
    float z;
    float speedX;

    Sprite() {

    }

	Sprite(const char* filename, bool useAlpha, float paramOffsetX, float paramOffsetY, float paramZ, float paramSpeedX)
    {
        create_textures(filename, useAlpha);
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
		else if (offsetX < -1.00f)
			offsetX += 1.00f;
    }

	void create_textures(const char* filename, bool useAlpha) {

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//ou GL_REPEAT GL_CLAMP_TO_BORDER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//ou GL_LINEAR GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load and generate the texture
		int width, height, nrChannels;
		nrChannels = 0;
		
		#ifdef __APPLE__
			unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
		#elif _WIN64
			unsigned char *data = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
		#endif
        
        if (data){
			if (useAlpha)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, nrCHANEL, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glGenerateMipmap(GL_TEXTURE_2D);
            //SOIL_create_OGL_texture(data, tex_width, tex_height, nrCHANEL, texture, SOIL_FLAG_INVERT_Y);
        } else {
            std::cout << "Failed to load main character texture" << std::endl;
        }

		#ifdef __APPLE__
			stbi_image_free(data);
		#elif _WIN64
			SOIL_free_image_data(data);
		#endif
	}
};