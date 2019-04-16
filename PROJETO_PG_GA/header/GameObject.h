#pragma once
class GameObject
{
public:
	GLuint textureId;
	Shader *shaderProgram;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	Sprite* sprites;

	glm::mat4 transformations = glm::mat4(1);

	GameObject(Shader* shaderProgramParam, string path, float width, float height, float depth) {
		shaderProgram = shaderProgramParam;
		setupVertex(width, height);
		/*
			Aqui sera a classe sprites adequada, e nao esta classe
			Sprite atual, que e voltada para texturas
		*/
		sprites = new Sprite(path, false, 0.0f, 0.0f, depth, 0.000f);
	}
	void setupVertex(float width, float height) {
		/*
			Comeca centralizado no zero.
			Fazer funcao de tranlacao pra posicao inicial depois
		*/
		float vertices[] = {
			// positions              // texture coords
			-width/2, -height/2, 0.0f,     1.0f, 1.0f, // top left
			-width/2, height/2,  0.0f,     1.0f, 0.0f, // bottom left
			width/2,  height/2,  0.0f,     0.0f, 0.0f, // bottom right
			width/2,  -height/2, 0.0f,     0.0f, 1.0f,  // top right
		};
		/*
			Aponta qual o indice do array de vertices sera usado para desenhar o triangulo
		*/
		unsigned int indices[] = {
				0, 1, 2,   // first triangle
				0, 3, 2    // second triangle
		};
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &VBO);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/*
			Antes de utilizar o glVertexAttribPointer e necessario dar o bind do buffer que sera lido.
			Aqui o EBO e o ultimo buffer a receber o bind, no entanto glVertexAttribPointer continua
			funcionando no VBO. Isto deve significar que o glVertexAttribPointer atua no ultimo
			buffer do tipo GL_ARRAY_BUFFER a receber bind
		*/

		// Passa e ativa o atributo (location) 0 no vertexShader, a partir do VBO
		// Le o atributo de 5 em 5 floats, comecando em 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Le o atributo de 5 em 5 floats, comecando em 3
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void draw() {
		// Define shaderProgram como o shader a ser utilizado
		shaderProgram->UseProgramShaders();
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
			GL_FALSE, glm::value_ptr(transformations));

		glUniform1f(
			glGetUniformLocation(shaderProgram->Program, "offsetX"), sprites->offsetX);
		glUniform1f(
			glGetUniformLocation(shaderProgram->Program, "offsetY"), sprites->offsetY);
		glUniform1f(
			glGetUniformLocation(shaderProgram->Program, "layer_z"), sprites->z);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprites->textureId);
		glUniform1i((glGetUniformLocation(shaderProgram->Program, "sprite")), 0);

		// Define vao como verte array atual
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	virtual ~GameObject();
};

GameObject::~GameObject()
{
	delete sprites;
}