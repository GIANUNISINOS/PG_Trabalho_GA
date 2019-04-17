#ifndef PROJETO_PG_GA_GAMEOBJECT_H
	#define PROJETO_PG_GA_GAMEOBJECT_H

#pragma once
class GameObject
{
public:
	Shader *shaderProgram;
	SpriteSheet* sprites;
	VerticesObject* vertices;
	double previousSeconds;
	int t = 0;

    glm::mat4 matrix_translaction = glm::mat4(1);
    glm::mat4 matrix_rotation = glm::mat4(1);
    glm::mat4 matrix_scala = glm::mat4(1);
    glm::mat4 transformations = matrix_translaction*matrix_rotation*matrix_scala;

	GameObject(Shader* shaderProgramParam, SpriteSheet* spritesParam, float width, float height, float depth) {
		shaderProgram = shaderProgramParam;
		sprites = spritesParam;
		previousSeconds = glfwGetTime();

		setupVertices(width, height, sprites->frames, sprites->actions);

		//poe na pos inicial
		matrix_translaction = glm::translate(matrix_translaction,glm::vec3(400.0f, 500.0f, 0.0f));
        transformations = matrix_translaction*matrix_rotation*matrix_scala;
	}
	/*
		actions e o numero de linhas da imagem de sprites
		frames  e o numero de colunas da imagem de sprites
	*/
	void setupVertices(float width, float height, int frames, int actions) {
		/*
			Comeca centralizado no zero.
			Fazer funcao de tranlacao pra posicao inicial depois
		*/
		float verticesCoordinates[] = {
			// positions						// texture coords
			-width/2,  -height/2, 0.0f,			0.0f,            1.0f,			   // top left
			-width/2,  height/2,  0.0f,			0.0f,	         (float)1/actions, // bottom left
			width/2,   height/2,  0.0f,			(float)1/frames, (float)1/actions, // bottom right
			width/2, - height/2,  0.0f,			(float)1/frames, 1.0f,             // top right
		};
		vertices = new VerticesObject(verticesCoordinates, 20);
	}

	void draw() {
		// Define shaderProgram como o shader a ser utilizado
		shaderProgram->UseProgramShaders();
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
			GL_FALSE, glm::value_ptr(transformations));

		// Passa os offsets para o shader
		sprites->passUniformsToShader(shaderProgram);

		// Define qual textura sera desenhada pelo shader
		sprites->texture->bind(shaderProgram);

		// Define qual vertice sera desenhado pelo shader
		vertices->bind(shaderProgram);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		
		if (elapsedSeconds > 0.1) {
			sprites->nextFrame();
			previousSeconds = currentSeconds;
		}
	}

	virtual ~GameObject();
};

GameObject::~GameObject()
{
	delete sprites;
	delete vertices;
}

#endif //PROJETO_PG_GA_GAMEOBJECT_H