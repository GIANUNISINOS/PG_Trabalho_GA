#ifdef __APPLE__
	#include "header/Includes.h"
	#include "header/Shader.h"
	#include "header/Sprite.h"
    #include "header/GameObject.h"
#elif _WIN64
	#include "../header/Includes.h";
	#include "../header/Shader.h";
	#include "../header/Sprite.h";
	#include "../header/GameObject.h";
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

void configurarFundo(){

    float vertices_FUNDO[] = {
            // positions              // texture coords
            0.0f,   0.0f,   0.0f,     1.0f, 1.0f, // top left
            0.0f,   600.0f, 0.0f,     1.0f, 0.0f, // bottom left
            800.0f, 600.0f, 0.0f,     0.0f, 0.0f, // bottom right
            800.0f, 0.0f,   0.0f,     0.0f, 1.0f,  // top right
    };
	/*
		Aponta qual o indice do vertices_Fundo[] será usado para desenhar o trìângulo
	*/
    unsigned int indices_FUNDO[] = {
            0, 1, 2,   // first triangle
            0, 3, 2    // second triangle
    };
    glGenBuffers(1, &EBO_FUNDO);
    glGenBuffers(1, &VBO_FUNDO);

    glGenVertexArrays(1, &VAO_FUNDO);
    glBindVertexArray(VAO_FUNDO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_FUNDO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_FUNDO), vertices_FUNDO, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_FUNDO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_FUNDO), indices_FUNDO, GL_STATIC_DRAW);
	
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

void configurarObjeto(){

    float vertices_OBJ[] = {
            // positions              // texture coords
            -50.0f, -50.0f,   0.0f,     1.0f, 1.0f, // top left
            -50.0f,  50.0f,   0.0f,     1.0f, 0.0f, // bottom left
            50.0f,   50.0f,   0.0f,     0.0f, 0.0f, // bottom right
            50.0f,  -50.0f,   0.0f,     0.0f, 1.0f,  // top right
    };
    /*
        Aponta qual o indice do vertices_OBJ[] será usado para desenhar o trìângulo
    */
    unsigned int indices_OBJ[] = {
            0, 1, 2,   // first triangle
            0, 3, 2    // second triangle
    };
    glGenBuffers(1, &EBO_OBJ);
    glGenBuffers(1, &VBO_OBJ);

    glGenVertexArrays(1, &VAO_OBJ);
    glBindVertexArray(VAO_OBJ);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_OBJ);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_OBJ), vertices_OBJ, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_OBJ);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_OBJ), indices_OBJ, GL_STATIC_DRAW);

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

    // configura vertice VBO VAO EBO do fundo
    configurarFundo();

    // configura vertice VBO VAO EBO do objeto
    //configurarObjeto();

    //criacao do shader
    shaderProgram = new Shader("shader/vertexShader.txt","shader/fragmentShader.txt");

    float vertices_OBJ[] = {
            // positions              // texture coords
            -50.0f, -50.0f,   0.0f,     1.0f, 1.0f, // top left
            -50.0f,  50.0f,   0.0f,     1.0f, 0.0f, // bottom left
            300.0f,   300.0f,   0.0f,     0.0f, 0.0f, // bottom right
            300.0f,  -300.0f,   0.0f,     0.0f, 1.0f,  // top right
    };

	// define shader para uso
	shaderProgram->UseProgramShaders();
	// habilita funcao de profundidade
	glEnable(GL_DEPTH_TEST);
	// habilita função de transparencia

	string resource_path;

	#ifdef __APPLE__
		resource_path = "../resource/";
	#elif _WIN64
		resource_path = "resource/";
	#endif //APPLE
    
	//Create GameObjeto
	GameObject* character = new GameObject(resource_path + "megamen.png", shaderProgram,*vertices_OBJ);

    Sprite* t0 = new Sprite(resource_path+"fundo.jpg", false, 0.0f, 0.0f, -0.52f, 0.000f);
	Sprite* t1 = new Sprite(resource_path+"sol.png", true, 0.0f, 0.0f, -0.51f, 0.001f);
	Sprite* t2 = new Sprite(resource_path+"nuvem.png", true, 0.0f, 0.0f, -0.50f, -0.002f);
	Sprite* t3 = new Sprite(resource_path+"grama coqueiro.png", true, 0.0f, 0.0f, -0.49f, -0.004);
//	Sprite* t4 = new Sprite(resource_path+"megamen.png", true, 0.0f, 0.0f, -0.48f, 0.006);

    layers.push_back(t0);
    layers.push_back(t1);
    layers.push_back(t2);
	layers.push_back(t3);
	//layers.push_back(t4);

    //os callback
    // esta para quando clicar com o mouse
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // esta para quando clicar uma tecla
    glfwSetKeyCallback(window, key_callback);
    // esta para quando redimensionar a tela
    glfwSetWindowSizeCallback(window, window_size_callback);

    // looping do main
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glm projecao
        glm::mat4 projection =
                glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);

		keyboard_reaction();
		for (int i = 0; i < 4; i++) {

            // Define shaderProgram como o shader a ser utilizado
            shaderProgram->UseProgramShaders();

            glUniformMatrix4fv(
                    glGetUniformLocation(shaderProgram->Program, "proj"), 1,
                    GL_FALSE, glm::value_ptr(projection));

                glUniformMatrix4fv(
                        glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
                        GL_FALSE, glm::value_ptr(matrix_static));
            

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
            glBindVertexArray(VAO_FUNDO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
		character->nextFrame(projection);

        //glfwWaitEvents();
        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    delete t0;
    delete t1;
    delete t2;
    delete t3;
    //delete t4;
	delete character;
    delete shaderProgram;

    glDeleteVertexArrays(1, &VAO_FUNDO);
    glDeleteBuffers(1, &VBO_FUNDO);
    glDeleteBuffers(1, &EBO_FUNDO);

    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();

    return 0;
}
