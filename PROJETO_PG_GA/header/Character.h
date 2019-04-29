
#ifndef PROJETO_PG_GA_CHARACTEROBJECT_H
#define PROJETO_PG_GA_CHARACTEROBJECT_H

#pragma once

class Character: public GameObject
{
public:
    float normalY;
    float upSpeed;
    float upDeceleration = 1.0f;
	float previousReactionTime;

	Character(Shader* shaderProgram, SpriteSheet* sprites, bool *gameIsRunning)
		: GameObject(shaderProgram, sprites, 100.0f, 100.0f, 400.0f, 490.0f, 5.0f, false, gameIsRunning)
	{
		this->normalY = 490.0f;
	}
	void changeFrame() {

	}

    /*
		Função que responde às teclas pressionadas
    */
    void keyboard_reaction(int keys[1024]) {
		double currentSeconds = glfwGetTime(); 
		double elapsedSeconds = currentSeconds - previousReactionTime;
		if(*gameIsRunning && elapsedSeconds > 0.016){
			
			previousReactionTime = currentSeconds;


            if (keys[GLFW_KEY_RIGHT] == 1) {
                if(position->xCenter < (800.00f-speed) ) {

					frameChangeSpeed = 0.03;
                    position->move(speed, 0.0f);
                }
            }
            if (keys[GLFW_KEY_LEFT] == 1) {
                if(position->xCenter> (speed/2.0f) ){

					frameChangeSpeed = 0.25;
                    position->move(-speed, 0.0f);
                }
            }
			if (keys[GLFW_KEY_RIGHT] == 0 && keys[GLFW_KEY_LEFT] == 0) {
				frameChangeSpeed = 0.1;
			}
            if (keys[GLFW_KEY_UP] == 1) {
                /*
                    Caso não esteja no ar, iniciar velociade
                    do pulo em -12.5f, fazer primeiro movimento
                    e desacelerar
                */
                if (position->yCenter >= normalY) {
					upSpeed = -12.5;
                    position->move(0.0f, upSpeed);
					upSpeed += upDeceleration;
                    sprites->setActions(2);
                }
            }// end if(KEY_UP)

			/*
				Caso esteja no ar, continuar movimento upSpeed,
				e desacelerar upSpeed;
			*/
			if (position->yCenter < normalY) {
				position->move(0.0f, upSpeed);
				upSpeed += upDeceleration;
			}
			else {
				sprites->setActions(1);
			}


        }
    }


    ~Character();
};

Character::~Character()
{
    delete sprites;
    delete vertices;
    delete position;
}

#endif //PROJETO_PG_GA_CHARACTEROBJECT_H
