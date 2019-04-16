#ifdef __APPLE__
	#include "header/Includes.h"
	#include "header/Shader.h"
	#include "header/Sprite.h"
    #include "header/GameObject.h"
	#include "header/BackgroundObject.h";
#elif _WIN64
	#include "../header/Includes.h";
	#include "../header/Shader.h";
	#include "../header/Sprite.h";
	#include "../header/GameObject.h";
	#include "../header/BackgroundObject.h";
#endif


//#define EXIT_FAILURE -1
//#define EXIT_SUCCESS 0

Shader *shaderProgram;
GLFWwindow *window;
vector<Sprite *> layers;

//Atributos janela
int NEW_WIDTH = 800;
int NEW_HEIGHT = 600;
int WIDTH = 800;
int HEIGHT = 600;

// atributos Cena
GLuint VAO_FUNDO;
GLuint EBO_FUNDO;
GLuint VBO_FUNDO;

//atributos objeto
GLuint VAO_OBJ;
GLuint EBO_OBJ;
GLuint VBO_OBJ;

//teclas pressionadas
int keys[1024];

glm::mat4 matrix_static = glm::mat4(1);
glm::mat4 matrix_translaction_OBJ = glm::mat4(1);
glm::mat4 matrix_rotation_OBJ = glm::mat4(1);
glm::mat4 matrix_scala_OBJ = glm::mat4(1);
glm::mat4 matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;

float xCentro = 0.0f;
float yCentro = 0.0f;
float value_scala = 1.2f;
float value_move = 15.0f;


//Define acoes do mouse
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            // pega pos click
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            //Realiza a proporcao do clique para projecao original
            xpos = WIDTH * xpos / NEW_WIDTH;
            ypos = HEIGHT * ypos / NEW_HEIGHT;

            matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ, glm::vec3((float)(xpos - xCentro), (float)(ypos - yCentro), 0.0f));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ;
            xCentro = xpos;
            yCentro = ypos;


        }
    }
}

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

/*
	Função que responde às teclas pressionadas
*/
void keyboard_reaction() {
	if (keys[GLFW_KEY_U] == 1) {
		matrix_rotation_OBJ = glm::rotate(matrix_rotation_OBJ, glm::radians(-20.0f), glm::vec3(0, 0, 1));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
	}
	if (keys[GLFW_KEY_R] == 1) {
		matrix_rotation_OBJ = glm::rotate(matrix_rotation_OBJ, glm::radians(20.0f), glm::vec3(0, 0, 1));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
	}
	if (keys[GLFW_KEY_RIGHT] == 1) {
		matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
			glm::vec3(value_move, 0.0f, 0.0f));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
		xCentro = xCentro + value_move;
	}
	if (keys[GLFW_KEY_LEFT] == 1) {
		matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
			glm::vec3(-value_move, 0.0f, 0.0f));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
		xCentro = xCentro - value_move;
	}
	if (keys[GLFW_KEY_DOWN] == 1) {
		matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
			glm::vec3(0.0f, value_move, 0.0f));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
		yCentro = yCentro + value_move;
	}
	if (keys[GLFW_KEY_UP] == 1) {
		matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
			glm::vec3(0.0f, -value_move, 0.0f));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
		yCentro = yCentro - value_move;
	}
	if (keys[GLFW_KEY_ESCAPE] == 1) {
		glfwSetWindowShouldClose(window, true);
	}
	if (keys[GLFW_KEY_KP_ADD] == 1)
	{
		matrix_scala_OBJ = glm::scale(matrix_scala_OBJ, glm::vec3(value_scala, value_scala, value_scala));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
	}
	if (keys[GLFW_KEY_KP_SUBTRACT] == 1)
	{
		matrix_scala_OBJ = glm::scale(matrix_scala_OBJ, glm::vec3(1.0f / value_scala, 1.0f / value_scala, 1.0f / value_scala));
		matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
	}
	
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

	/* Caso necess·rio, definiÁıes especÌficas para SOs, p. e. Apple OSX  Definir como 3.2 para Apple OS X */
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

	//os callback
	// esta para quando clicar com o mouse
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// esta para quando clicar uma tecla
	glfwSetKeyCallback(window, key_callback);
	// esta para quando redimensionar a tela
	glfwSetWindowSizeCallback(window, window_size_callback);

	//Create Objects
	string resource_path;
	#ifdef __APPLE__
		resource_path = "../resource/";
	#elif _WIN64
		resource_path = "resource/";
	#endif //APPLE
	GameObject* character = new GameObject(shaderProgram, resource_path + "megamen.png", 200.0f, 200.0f, -0.48f);
	BackgroundObject* background = new BackgroundObject(shaderProgram, (float)WIDTH, (float)HEIGHT);

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

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	

	delete background;
	delete character;
    delete shaderProgram;

    glDeleteVertexArrays(1, &VAO_FUNDO);
    glDeleteBuffers(1, &VBO_FUNDO);
    glDeleteBuffers(1, &EBO_FUNDO);

    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();

    return 0;
}
