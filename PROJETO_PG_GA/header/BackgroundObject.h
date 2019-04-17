#pragma once
#ifndef PROJETO_PG_GA_BACKGROUNDOBJECT_H
	#define PROJETO_PG_GA_BACKGROUNDOBJECT_H
	
class BackgroundObject
{
public:
	GLuint textureId;
	Shader *shaderProgram;
	VerticesObject* vertices;
	vector<Layer *> layers;
	
	glm::mat4 transformations = glm::mat4(1);
	
	BackgroundObject(Shader* shaderProgramParam, float width, float height);
	virtual ~BackgroundObject();

	void setupTextures();
	void draw();
};

BackgroundObject::BackgroundObject(Shader* shaderProgramParam, float width, float height) {
	shaderProgram = shaderProgramParam;
	float verticesCoordinates[] = {
		// positions              // texture coords
		0.0f,  0.0f,   0.0f,     0.0f, 1.0f, // top left
		0.0f,  height, 0.0f,     0.0f, 0.0f, // bottom left
		width, height, 0.0f,     1.0f, 0.0f, // bottom right
		width, 0.0f,   0.0f,     1.0f, 1.0f,  // top right
	};

	vertices = new VerticesObject(verticesCoordinates, 20);
	setupTextures();
}
void BackgroundObject::setupTextures() {
	string resource_path;
	resource_path = "resource/";

	/*
		O ideal seria ler o path em um arquivo externo
	*/
	Layer* t0 = new Layer(resource_path + "fundo.jpg", false, 0.0f, 0.0f, -0.52f, 0.000f);
	Layer* t1 = new Layer(resource_path + "sol.png", true, 0.0f, 0.0f, -0.51f, -0.001f);
	Layer* t2 = new Layer(resource_path + "nuvem.png", true, 0.0f, 0.0f, -0.50f, 0.002f);
	Layer* t3 = new Layer(resource_path + "grama coqueiro.png", true, 0.0f, 0.0f, -0.49f, 0.004);

	layers.push_back(t0);
	layers.push_back(t1);
	layers.push_back(t2);
	layers.push_back(t3);
}

void BackgroundObject::draw() {
	for (int i = 0; i < 4; i++) {

		// Define shaderProgram como o shader a ser utilizado
		shaderProgram->UseProgramShaders();
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
			GL_FALSE, glm::value_ptr(transformations));

		// realiza movimento da camada em X
		layers[i]->moveX();

		glUniform1f(
			glGetUniformLocation(shaderProgram->Program, "offsetX"), layers[i]->offsetX);
		glUniform1f(
			glGetUniformLocation(shaderProgram->Program, "offsetY"), layers[i]->offsetY);
		glUniform1f(
			glGetUniformLocation(shaderProgram->Program, "layer_z"), layers[i]->z);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, layers[i]->textureId);
		glUniform1i((glGetUniformLocation(shaderProgram->Program, "sprite")), 0);

		// Define vao como verte array atual
		glBindVertexArray(vertices->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

BackgroundObject::~BackgroundObject()
{
	delete layers[0];
	delete layers[1];
	delete layers[2];
	delete layers[3];

	delete vertices;
}
#endif
