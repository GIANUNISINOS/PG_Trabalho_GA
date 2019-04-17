#pragma once

void setupVertex(float verticesPointer, GLuint VAO, GLuint VBO, GLuint EBO) {
	/*
		Aponta qual o indice do array de vértices será usado para desenhar o trìângulo
	*/

	unsigned int verticesIndex[] = {
			0, 1, 2,   // first triangle
			0, 3, 2    // second triangle
	};
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(&verticesIndex), &verticesPointer, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesIndex), verticesIndex, GL_STATIC_DRAW);

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