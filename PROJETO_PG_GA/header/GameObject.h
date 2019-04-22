#ifndef PROJETO_PG_GA_GAMEOBJECT_H
	#define PROJETO_PG_GA_GAMEOBJECT_H

#pragma once
class GameObject
{
public:
	Shader *shaderProgram;
	SpriteSheet* sprites;
	VerticesObject* vertices;
	Position* position;
	double previousSeconds;
	int t = 0;

	bool isOnTopJump;
	float speed;

	GameObject(Shader* shaderProgramParam, SpriteSheet* spritesParam, float width, float height, float depth, float initialPosX, float initialPosY, float speedParam) {
		shaderProgram = shaderProgramParam;
		sprites = spritesParam;
		previousSeconds = glfwGetTime();

		speed = speedParam;

		setupVertices(width, height, sprites->frames, sprites->actions);
		
		//poe na pos inicial
		position = new Position(initialPosX, initialPosY);

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

	void doingLoping(){
		position->move(speed, 0.0f);
		if (position->xCenter <= 0.0f) {
			position->move( 800.0f-position->xCenter, 0.0f );
		}
    }

	void draw() {
		// Define shaderProgram como o shader a ser utilizado
		shaderProgram->UseProgramShaders();
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
			GL_FALSE, glm::value_ptr(position->transformations));

		// Passa os offsets para o shader
		sprites->passUniformsToShader(shaderProgram);

		// Define qual textura sera desenhada pelo shader
		sprites->texture->bind(shaderProgram);

		// Define em quais vertices sera desenhado pelo shader
		vertices->bind(shaderProgram);

		if(isOnTopJump){

			position->move(0.0f, 70.0f);
            
			sprites->setActions(2);
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
        if (keys[GLFW_KEY_RIGHT] == 1) {
            if(position->xCenter < (800.00f-speed) ) {

				position->move(speed, 0.0f);
            }
        }
        if (keys[GLFW_KEY_LEFT] == 1) {
            if(position->xCenter> (speed/2.0f) ){
				
				position->move(-speed, 0.0f);
            }
        }
        if (keys[GLFW_KEY_UP] == 1) {
            if(!isOnTopJump){
                isOnTopJump = true;
                sprites->setActions(1);

				position->move(0.0f, -70.0f);
            }
        }
    }


	virtual ~GameObject();
};

GameObject::~GameObject()
{
	delete sprites;
	delete vertices;
	delete position;
}

#endif //PROJETO_PG_GA_GAMEOBJECT_H