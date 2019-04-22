
#ifndef PROJETO_PG_GA_CHARACTEROBJECT_H
#define PROJETO_PG_GA_CHARACTEROBJECT_H

#pragma once
class CharacterObject
{
public:
    Shader *shaderProgram;
    SpriteSheet* sprites;
    VerticesObject* vertices;
    Position* position;
    double previousSeconds;
    int t = 0;

    float speed;

    float normalY;

    float upSpeed;
    float upDeceleration = 4.0f;

    float width;
    float height;

    CharacterObject(Shader* shaderProgramParam, SpriteSheet* spritesParam, float width, float height, float depth, float initialPosX, float initialPosY, float speedParam) {
        shaderProgram = shaderProgramParam;
        sprites = spritesParam;
        previousSeconds = glfwGetTime();

        speed = speedParam;
        normalY = initialPosY;	// Posição Y sem o pulo

        this->width = width;
        this->height = height;

        setupVertices(sprites->frames, sprites->actions);

        //poe na pos inicial
        position = new Position(initialPosX, initialPosY);
    }

    /*
        actions e o numero de linhas da imagem de sprites
        frames  e o numero de colunas da imagem de sprites
    */
    void setupVertices(int frames, int actions) {
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
                GL_FALSE, glm::value_ptr(position->transformations));

        // Passa os offsets para o shader
        sprites->passUniformsToShader(shaderProgram);

        // Define qual textura sera desenhada pelo shader
        sprites->texture->bind(shaderProgram);

        // Define em quais vertices sera desenhado pelo shader
        vertices->bind(shaderProgram);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /*
            Troca o sprite, e faz o movimento do pulo a 10fps;
        */
        double currentSeconds = glfwGetTime();
        double elapsedSeconds = currentSeconds - previousSeconds;
        if (elapsedSeconds > 0.075) {
            sprites->nextFrame();
            previousSeconds = currentSeconds;


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
            /*
                Caso não esteja no ar, iniciar velociade
                do pulo em -20.0f, fazer primeiro movimento
                e desacelerar
            */
            if (position->yCenter >= normalY) {
                upSpeed = -20.0f;
                position->move(0.0f, upSpeed);
                upSpeed += upDeceleration;
                sprites->setActions(2);
            }
        }
    }


    virtual ~CharacterObject();
};

CharacterObject::~CharacterObject()
{
    delete sprites;
    delete vertices;
    delete position;
}

#endif //PROJETO_PG_GA_CHARACTEROBJECT_H
