#pragma once
class Texture
{
public:
	GLuint id;
	int width;
	int height;

	Texture(string filename, bool useAlpha);
	~Texture();

	void create_texture(const char* filename, bool useAlpha);
	void bind(Shader* shaderProgram);
	void passUniformsToShader(Shader* shaderProgram, float offsetX, float offsetY, float layer_z);
};

Texture::Texture(string filename, bool useAlpha)
{
	/*
		c._str() pra passar de string para char*
	*/
	create_texture(filename.c_str(), useAlpha);
}
void Texture::bind(Shader* shaderProgram) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glUniform1i((glGetUniformLocation(shaderProgram->Program, "sprite")), 0);
}

void Texture::passUniformsToShader(Shader* shaderProgram, float offsetX, float offsetY, float layer_z) {
	glUniform1f(
		glGetUniformLocation(shaderProgram->Program, "offsetX"), offsetX);
	glUniform1f(
		glGetUniformLocation(shaderProgram->Program, "offsetY"), offsetY);
	glUniform1f(
		glGetUniformLocation(shaderProgram->Program, "layer_z"), layer_z);
}

void Texture::create_texture(const char* filename, bool useAlpha) {

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

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
		if (useAlpha)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Falha ao carregar images." << std::endl;
	}

	stbi_image_free(data);

}

Texture::~Texture()
{
}
