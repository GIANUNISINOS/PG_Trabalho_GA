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
	double previousSeconds;
	glm::mat4 transformations = glm::mat4(1);
    bool *gameIsRunning;

    BackgroundObject(Shader* shaderProgramParam, float width, float height, bool *gameIsRunning);
	virtual ~BackgroundObject();

	void setupTextures();
	void draw();
};

BackgroundObject::BackgroundObject(Shader* shaderProgramParam, float width, float height, bool *gameIsRunning) {
	shaderProgram = shaderProgramParam;
	previousSeconds = glfwGetTime();
	float verticesCoordinates[] = {
		// positions              // texture coords
		0.0f,  0.0f,   0.0f,     0.0f, 1.0f, // top left
		0.0f,  height, 0.0f,     0.0f, 0.0f, // bottom left
		width, height, 0.0f,     1.0f, 0.0f, // bottom right
		width, 0.0f,   0.0f,     1.0f, 1.0f,  // top right
	};

	vertices = new VerticesObject(verticesCoordinates, 20);
    this->gameIsRunning =gameIsRunning;
    setupTextures();
}
void BackgroundObject::setupTextures() {
	string resource_path;
	resource_path = "resource/";

	/*
		O ideal seria ler o path em um arquivo externo
	*/
	Layer* t0 = new Layer(resource_path + "fundo.jpg", false, 0.0f, 0.0f, -0.52f, 0.00f);
	Layer* t1 = new Layer(resource_path + "sol.png", true, 0.0f, 0.0f, -0.51f, -0.0001f);
	Layer* t2 = new Layer(resource_path + "nuvem.png", true, 0.0f, 0.0f, -0.50f, 0.003f);
	Layer* t3 = new Layer(resource_path + "grama coqueiro.png", true, 0.0f, 0.0f, -0.49f, 0.012);
    Layer* t4 = new Layer(resource_path + "gamewin.png", true, 0.0f, 0.0f, -1.48f, 0.00f);
    Layer* t5 = new Layer(resource_path + "gameover.png", true, 0.0f, 0.0f, -1.47f, 0.00f);

	layers.push_back(t0);
	layers.push_back(t1);
    layers.push_back(t2);
    layers.push_back(t3);
    layers.push_back(t4);
    layers.push_back(t5);
}

void BackgroundObject::draw() {
	/*
		Realiza o movimento das camadas, a 60fps;		
	*/
	double currentSeconds = glfwGetTime();
	double elapsedSeconds = currentSeconds - previousSeconds;
	if (elapsedSeconds > 0.015&&*gameIsRunning) {
		for (int i = 0; i < 4; i++) {
			layers[i]->moveX();
			
		}
		previousSeconds = currentSeconds;
	}
	/*
		Desenha as 4 texturas, uma apos a outra
	*/
	for (int i = 0; i < 6; i++) {

		// Define shaderProgram como o shader a ser utilizado
		shaderProgram->UseProgramShaders();
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
			GL_FALSE, glm::value_ptr(transformations));
		
		// Passa os offsets para o shader
		layers[i]->passUniformsToShader(shaderProgram);

		// Define qual textura sera desenhada pelo shader
		layers[i]->texture->bind(shaderProgram);

		// Define em quais vertices sera desenhado pelo shader
		vertices->bind(shaderProgram);
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
