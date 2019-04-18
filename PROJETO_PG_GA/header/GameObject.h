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

	bool isOnTopJump;
	float speed;

    //teclas pressionadas
    float xCentro = 0.0f;
    float yCentro = 0.0f;
    float value_scala = 1.2f;
    float value_move = 10.0f;

    glm::mat4 matrix_translaction = glm::mat4(1);
    glm::mat4 matrix_rotation = glm::mat4(1);
    glm::mat4 matrix_scala = glm::mat4(1);
    glm::mat4 transformations = matrix_translaction*matrix_rotation*matrix_scala;

	GameObject(Shader* shaderProgramParam, SpriteSheet* spritesParam, float width, float height, float depth, float initialPosX, float initialPosY) {
		shaderProgram = shaderProgramParam;
		sprites = spritesParam;
		previousSeconds = glfwGetTime();

		setupVertices(width, height, sprites->frames, sprites->actions);

		//poe na pos inicial
        xCentro = initialPosX;
        yCentro = initialPosY;
		matrix_translaction = glm::translate(matrix_translaction,glm::vec3(xCentro, yCentro, 0.0f));
		transformations = matrix_translaction*matrix_rotation*matrix_scala;

        isOnTopJump = false;
	}

	/*
		actions e o numero de linhas da imagem de sprites
		frames  e o numero de colunas da imagem de sprites
	*/
	void setupVertices(float width, float height, int frames, int actions) {
		/*
			Comeca centralizado no zero
		*/
		float verticesCoordinates[] = {
			// positions						// texture coords
			-width/2,  -height/2, 0.0f,			0.0f,                1.0f,							 // top left
			-width/2,  height/2,  0.0f,			0.0f,	             1.00f - (1.00f/(float)actions), // bottom left
			width/2,   height/2,  0.0f,			1.00f/(float)frames, 1.00f - (1.00f/(float)actions), // bottom right
			width/2, - height/2,  0.0f,			1.00f/(float)frames, 1.0f,							 // top right
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

		// Define em quais vertices sera desenhado pelo shader
		vertices->bind(shaderProgram);

		if(isOnTopJump){
            for(int i=0;i<10;i++){
                matrix_translaction = glm::translate(matrix_translaction,
                                                     glm::vec3(0.0f, value_move, 0.0f));
                transformations = matrix_translaction * matrix_rotation * matrix_scala;
                yCentro = yCentro + value_move;
            }
            isOnTopJump=false;
		}


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		/*
			Troca o sprite, a 10fps;
		*/
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		if (elapsedSeconds > 0.1) {
			sprites->nextFrame();
			previousSeconds = currentSeconds;
		}
	}


    /*
		Função que responde às teclas pressionadas
    */
    void keyboard_reaction(int keys[1024]) {
        if (keys[GLFW_KEY_U] == 1) {
            matrix_rotation = glm::rotate(matrix_rotation, glm::radians(-20.0f), glm::vec3(0, 0, 1));
            transformations = matrix_translaction * matrix_rotation * matrix_scala;
        }
        if (keys[GLFW_KEY_R] == 1) {
            matrix_rotation = glm::rotate(matrix_rotation, glm::radians(20.0f), glm::vec3(0, 0, 1));
            transformations = matrix_translaction * matrix_rotation * matrix_scala;
        }
        if (keys[GLFW_KEY_RIGHT] == 1) {
            matrix_translaction = glm::translate(matrix_translaction,
                                                 glm::vec3(value_move, 0.0f, 0.0f));
            transformations = matrix_translaction * matrix_rotation * matrix_scala;
            xCentro = xCentro + value_move;
        }
        if (keys[GLFW_KEY_LEFT] == 1) {
            matrix_translaction = glm::translate(matrix_translaction,
                                                 glm::vec3(-value_move, 0.0f, 0.0f));
            transformations = matrix_translaction * matrix_rotation * matrix_scala;
            xCentro = xCentro - value_move;
        }
        if (keys[GLFW_KEY_DOWN] == 1) {
//            matrix_translaction = glm::translate(matrix_translaction,
//                                                 glm::vec3(0.0f, value_move, 0.0f));
//            transformations = matrix_translaction * matrix_rotation * matrix_scala;
//            yCentro = yCentro + value_move;
        }
        if (keys[GLFW_KEY_UP] == 1) {
            if(!isOnTopJump){
                isOnTopJump = true;
                for(int i=0;i<10;i++){
                        matrix_translaction = glm::translate(matrix_translaction,
                                                             glm::vec3(0.0f, -value_move, 0.0f));
                        transformations = matrix_translaction * matrix_rotation * matrix_scala;
                        yCentro = yCentro - value_move;
                }

            }
        }
        if (keys[GLFW_KEY_KP_ADD] == 1)
        {
            matrix_scala = glm::scale(matrix_scala, glm::vec3(value_scala, value_scala, value_scala));
            transformations = matrix_translaction * matrix_rotation * matrix_scala;
        }
        if (keys[GLFW_KEY_KP_SUBTRACT] == 1)
        {
            matrix_scala = glm::scale(matrix_scala, glm::vec3(1.0f / value_scala, 1.0f / value_scala, 1.0f / value_scala));
            transformations = matrix_translaction * matrix_rotation * matrix_scala;
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