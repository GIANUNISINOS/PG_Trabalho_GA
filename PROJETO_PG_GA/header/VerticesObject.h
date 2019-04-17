#pragma once
class VerticesObject
{
public:
	GLuint VAO;
	
	/*
		E necessario receber o size pois o array sera enviado
		para o construtor por ponteiro, e o ponteiro nao guarda
		o tamanho.

		Todo array enviado por parametro se transforma em um
		ponteiro, seja ele 
	
		*array, array[] ou array[n];
	*/

	VerticesObject(float verticesCoordinates[], int size);
	~VerticesObject();

	void setup(float verticesCoordinates[], int size);

};

VerticesObject::VerticesObject(float verticesCoordinates[], int size){
	setup(verticesCoordinates, size);
}

void VerticesObject::setup(float verticesCoordinates[], int size) {
	GLuint VBO;
	GLuint EBO;
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
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), verticesCoordinates, GL_STATIC_DRAW);

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


VerticesObject::~VerticesObject()
{
}
