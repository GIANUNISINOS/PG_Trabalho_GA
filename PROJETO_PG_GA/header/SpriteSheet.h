#ifndef PROJETO_PG_GA_SPRITESHEET_H
	#define PROJETO_PG_GA_SPRITESHEET_H

#pragma once
class SpriteSheet
{
public:
	GLuint textureId;
	int actions;
	int frames;
	int width;
	int height;
	int currentAction;
	int currentFrame;
	float z;

	SpriteSheet(string filename, int framesParam, int actionsParam, float zParam) {
		create_textures(filename.c_str());
		actions = actionsParam;
		frames = framesParam;
		currentAction = 0;
		currentFrame = 0;
		z = zParam;

	};
	~SpriteSheet();

	float getOffsetX() {
		return (float)1 / frames * (currentFrame%frames);
	}
	float getOffsetY() {
		return (float)1 / actions * (currentAction%actions);
	}
	void nextFrame() {
		currentFrame++;
	}
	void setActions(int a) {
		currentAction = a;
	}

	void create_textures(const char* filename) {

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//ou GL_REPEAT GL_CLAMP_TO_BORDER
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//ou GL_LINEAR GL_NEAREST
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		int nrChannels;
		nrChannels = 0;

		unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (data) {	
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Falha ao carregar images." << std::endl;
		}

		stbi_image_free(data);

	}
};

SpriteSheet::~SpriteSheet()
{
}
#endif
