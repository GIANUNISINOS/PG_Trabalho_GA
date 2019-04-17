#ifndef TESTANDO_SPRITE_H 
#define TESTANDO_SPRITE_H

class Layer {
public:
    GLuint textureId;
    float offsetX;
    float offsetY;
    float z;
    float speedX;

    Layer() {

    }

	Layer(string filename, bool useAlpha, float paramOffsetX, float paramOffsetY, float paramZ, float paramSpeedX)
    {
        create_textures(filename.c_str(), useAlpha);
        offsetX = paramOffsetX;
        offsetY = paramOffsetY;
        z = paramZ;
        speedX = paramSpeedX;
    }

    void moveX()
    {
        offsetX += speedX;
//        if (offsetX > 1.00f)
//            offsetX -= 1.00f;
//		else if (offsetX < -1.00f)
//			offsetX += 1.00f;
    }

	void create_textures(const char* filename, bool useAlpha) {

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//ou GL_REPEAT GL_CLAMP_TO_BORDER
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//ou GL_LINEAR GL_NEAREST
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load and generate the texture
		int width, height, nrChannels;
		nrChannels = 0;

		unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
        
        if (data){
			if (useAlpha)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Falha ao carregar images." << std::endl;
        }

		stbi_image_free(data);

	}
};

#endif