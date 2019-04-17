#pragma once
class SpriteSheet
{
public:
	GLuint textureId;
	int actions;
	int frames;

	SpriteSheet(string filename, int actionsParam, int framesParam) {
		create_textures(filename.c_str());
		actions = actionsParam;
		frames = framesParam;
	};
	~SpriteSheet();

	void create_textures(const char* filename) {

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

		if (data) {	
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
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
