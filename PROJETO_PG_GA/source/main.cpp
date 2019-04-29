#ifdef __APPLE__
    #include "header/Includes.h";
    #include "header/Shader.h";
    #include "header/Texture.h";
    #include "header/Layer.h";
    #include "header/SpriteSheet.h";
    #include "header/VerticesObject.h";
	#include "header/Position.h";
	#include "header/GameObject.h";
	#include "header/Projectile.h";
    #include "header/Character.h";
    #include "header/BackgroundObject.h";
#elif _WIN64
	#include "../header/Includes.h";
	#include "../header/Shader.h";
	#include "../header/Texture.h";
	#include "../header/Layer.h";
	#include "../header/SpriteSheet.h";
	#include "../header/VerticesObject.h";
	#include "../header/Position.h";
	#include "../header/GameObject.h";
	#include "../header/Projectile.h";
	#include "../header/Character.h";
	#include "../header/BackgroundObject.h";
#endif

Shader *shaderProgram;
GLFWwindow *window;
bool gameIsRunning;
time_t timeEnd;

BackgroundObject* background;
Character* character;
Projectile* projetil;

//Atributos janela
int WIDTH = 800;
int HEIGHT = 600;

//teclas pressionadas
int keys[1024];

//Define acoes do redimensionamento da tela
void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/*
	Controla que teclas estão pressionadas em um dado momento
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) keys[key] = 1;
	if(action == GLFW_RELEASE) keys[key] = 0;
}

void main_keyboard_reaction() {
    if (keys[GLFW_KEY_SPACE] == 1) {
        if(gameIsRunning==false){
            // Tempo que ira acabar o jogo (30 segundos)
            timeEnd = time(NULL) + 30;
            gameIsRunning = true;
            //posicao inicial
            character->position->move(400.0f-character->position->xCenter, 490.0f-character->position->yCenter);
            projetil->position->move(900.0f-projetil->position->xCenter, 490.0f-projetil->position->yCenter);

            //remove da tela game win e game over
            background->layers[4]->z = -1.48;
            background->layers[5]->z = -1.47;
        }
    }
    if (keys[GLFW_KEY_ESCAPE] == 1) {
        glfwSetWindowShouldClose(window, true);
    }

}


GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Try to survive thirty seconds!", NULL, NULL);
    if (window == NULL) {
        printf("%s", "Houve uma falha ao criar a janela GLFW");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    return window;
}

void testGameWinOrOver(){

    //testa colisão da morte
    bool difInX =
            (character->position->xCenter + character->width / 2.0f)-40.0f > (projetil->position->xCenter - projetil->width/2.0f)
            &&(character->position->xCenter - character->width / 2.0f)+60.0f< (projetil->position->xCenter + projetil->width/2.0f)
    ;

    bool difInY =
            (character->position->yCenter + character->height/2.0f)-7.0f > (projetil->position->yCenter - projetil->height/2.0f);



    if(difInX && difInY && gameIsRunning){
        printf("VOCÊ MORREU, GAME OVER!\n");
        background->layers[5]->z = -0.47;
        gameIsRunning = false;
        //FECHAR JANELA!
        //glfwSetWindowShouldClose(window, true);
    }

    //testa o tempo se viver, ganha
    if (time(NULL) > timeEnd && gameIsRunning){
        printf("VOCÊ GANHOU, GAME WIN!\n");
        background->layers[4]->z = -0.48;
        gameIsRunning = false;
        //glfwSetWindowShouldClose(window, true);
    }
}

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "ERRO: não é possivel iniciar GLFW3\n");
		return 1;
	}

	/* needs for Apple OS X */
    #ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif // !APPLE

	window = createWindow();

	// inicia manipulador da extensao GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	//criacao do shader
	shaderProgram = new Shader("shader/vertexShader.txt", "shader/fragmentShader.txt");

	// define shader para uso
	shaderProgram->UseProgramShaders();

	// habilita funcao de profundidade
	glEnable(GL_DEPTH_TEST);

	//Create SO callbacks
	// esta para quando clicar uma tecla
	glfwSetKeyCallback(window, key_callback);

	// esta para quando redimensionar a tela
	glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // inicializa game
    gameIsRunning = false;

	//Create Objects
    SpriteSheet* knightSprites = new SpriteSheet("resource/warrior.png", 8, 2, -0.48f);
	knightSprites->setActions(1);

    SpriteSheet* projetilSprites = new SpriteSheet("resource/fire.png", 5, 1, -0.47f);

	background = new BackgroundObject(shaderProgram, (float)WIDTH, (float)HEIGHT, &gameIsRunning);

	character  = new Character(shaderProgram, knightSprites, &gameIsRunning);

	projetil   = new Projectile(shaderProgram, projetilSprites, &gameIsRunning);

    // looping do main
	while (!glfwWindowShouldClose(window)) {

	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glm projecao
		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "proj"), 1, GL_FALSE, glm::value_ptr(projection));

		//camadas do fundo
		background->draw();

        //personagem que se movimenta via teclado
		character->keyboard_reaction(keys);
		character->draw();

        //objeto inimigo que se movimenta automaticamente
		projetil->draw();
        projetil->doingLoping();

        //testa reacoes do teclado como ESC e ESPACO
        main_keyboard_reaction();

        //testa colisoes e game win ou over
        testGameWinOrOver();

        //fila eventos 
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	delete knightSprites;
	delete projetilSprites;
	delete projetil;
	delete background;
	delete character;
    delete shaderProgram;

    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();

    return 0;
}

