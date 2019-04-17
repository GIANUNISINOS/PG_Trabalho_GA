#ifdef __APPLE__
    #include "header/Includes.h";
    #include "header/Shader.h";
    #include "header/Texture.h";
    #include "header/Layer.h";
    #include "header/SpriteSheet.h";
    #include "header/VerticesObject.h";
    #include "header/GameObject.h";
    #include "header/BackgroundObject.h";
#elif _WIN64
	#include "../header/Includes.h";
	#include "../header/Shader.h";
	#include "../header/Texture.h";
	#include "../header/Layer.h";
	#include "../header/SpriteSheet.h";
	#include "../header/VerticesObject.h";
	#include "../header/GameObject.h";
	#include "../header/BackgroundObject.h";
#endif


//#define EXIT_FAILURE -1
//#define EXIT_SUCCESS 0

Shader *shaderProgram;
GLFWwindow *window;

//Atributos janela
int NEW_WIDTH = 800;
int NEW_HEIGHT = 600;
int WIDTH = 800;
int HEIGHT = 600;

//teclas pressionadas
int keys[1024];

//Define acoes do redimensionamento da tela
void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    NEW_WIDTH = width;
    NEW_HEIGHT = height;
}

/*
	Controla que teclas estão pressionadas em um dado momento
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS) keys[key] = 1;
	if(action == GLFW_RELEASE) keys[key] = 0;
}

GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triângulo Maluco", NULL, NULL);
    if (window == NULL) {
        printf("%s", "Houve uma falha ao criar a janela GLFW");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    return window;
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

	// inicia manipulador da extens„o GLEW
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

	//Create Objects
	/*
		Juntar as duas as 2 ações dessa imagem do megaman em 1 só
	*/
	SpriteSheet* megamanSprites = new SpriteSheet("resource/sprites_megaman-runnnig.png", 5, 2, -0.48f);

	BackgroundObject* background = new BackgroundObject(shaderProgram, (float)WIDTH, (float)HEIGHT);
    GameObject* character = new GameObject(shaderProgram,megamanSprites, 100.0f, 100.0f, -0.48f);

    // looping do main
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glm projecao
		glm::mat4 projection =
			glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "proj"), 1,
			GL_FALSE, glm::value_ptr(projection));


		background->draw();
		character->draw();
        character->keyboard_reaction(keys);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	

	delete background;
	delete character;
    delete shaderProgram;

    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();

    return 0;
}
