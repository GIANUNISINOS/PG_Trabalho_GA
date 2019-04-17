#pragma once
class BackgroundObject
{
public:
	GLuint textureId;
	Shader *shaderProgram;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	vector<Sprite *> layers;
	
	glm::mat4 transformations = glm::mat4(1);
	
	BackgroundObject(Shader* shaderProgramParam, float width, float height){
		shaderProgram = shaderProgramParam;
		setupVertex(width, height);
		setupTextures();
	}
	void setupVertex(float width, float height) {
		float vertices[] = {
			// positions              // texture coords
			0.0f,  0.0f,   0.0f,     0.0f, 1.0f, // top left
			0.0f,  height, 0.0f,     0.0f, 0.0f, // bottom left
			width, height, 0.0f,     1.0f, 0.0f, // bottom right
			width, 0.0f,   0.0f,     1.0f, 1.0f,  // top right
		};
		/*
			Aponta qual o indice do vertices_Fundo[] será usado para desenhar o trìângulo
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
			Antes de utilizar o glVertexAttribPointer é necessário dar o bind do buffer que será lido.
			Aqui o EBO é o último buffer a receber o bind, no entanto glVertexAttribPointer continua
			funcionando no VBO. Isto deve significar que o glVertexAttribPointer atua no último
			buffer do tipo GL_ARRAY_BUFFER a receber bind
		*/

		// Passa e ativa o atributo (location) 0 no vertexShader, a partir do VBO
		// Lê o atributo de 5 em 5 floats, começando em 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Lê o atributo de 5 em 5 floats, começando em 3
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void setupTextures() {
		string resource_path;
		#ifdef __APPLE__
				resource_path = "../resource/";
		#elif _WIN64
				resource_path = "resource/";
		#endif //APPLE

		/*
			O ideal seria ler o path em um arquivo externo
		*/
		Sprite* t0 = new Sprite(resource_path + "fundo.jpg", false, 0.0f, 0.0f, -0.52f, 0.000f);
		Sprite* t1 = new Sprite(resource_path + "sol.png", true, 0.0f, 0.0f, -0.51f, 0.001f);
		Sprite* t2 = new Sprite(resource_path + "nuvem.png", true, 0.0f, 0.0f, -0.50f, -0.002f);
		Sprite* t3 = new Sprite(resource_path + "grama coqueiro.png", true, 0.0f, 0.0f, -0.49f, -0.004);

		layers.push_back(t0);
		layers.push_back(t1);
		layers.push_back(t2);
		layers.push_back(t3);
	}
	
	void draw() {
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
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	virtual ~BackgroundObject();
};

BackgroundObject::~BackgroundObject()
{
	delete layers[0];
	delete layers[1];
	delete layers[2];
	delete layers[3];
}
