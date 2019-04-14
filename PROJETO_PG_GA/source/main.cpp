#ifdef __APPLE__
	#include "header/Includes.h"
	#include "header/Shader.h"
	#include "header/Sprite.h"
#elif _WIN64
	#include "../header/Includes.h";
	#include "../header/Shader.h";
	#include "../header/Sprite.h";
#endif


//#define EXIT_FAILURE -1
//#define EXIT_SUCCESS 0

//Shader *shader;
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

glm::mat4 matrix_translaction_OBJ = glm::mat4(1);
glm::mat4 matrix_rotation_OBJ = glm::mat4(1);
glm::mat4 matrix_scala_OBJ = glm::mat4(1);
glm::mat4 matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;

float xCentro = 0.0f;
float yCentro = 0.0f;
float value_scala = 1.2f;
float value_move = 3.0f;


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

//Define acoes do teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if ((action == GLFW_REPEAT || action == GLFW_PRESS)) {
        if (key == GLFW_KEY_U) {
            matrix_rotation_OBJ = glm::rotate(matrix_rotation_OBJ, glm::radians(-20.0f), glm::vec3(0, 0, 1));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
        }
        else if (key == GLFW_KEY_R) {
            matrix_rotation_OBJ = glm::rotate(matrix_rotation_OBJ, glm::radians(20.0f), glm::vec3(0, 0, 1));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
        }

        else if (key == GLFW_KEY_RIGHT) {
            matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
                                                 glm::vec3(value_move, 0.0f, 0.0f));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
            xCentro = xCentro + value_move;
        }
        else if (key == GLFW_KEY_LEFT) {
            matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
                                                 glm::vec3(-value_move, 0.0f, 0.0f));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
            xCentro = xCentro - value_move;
        }
        else if (key == GLFW_KEY_DOWN) {
            matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
                                                 glm::vec3(0.0f, value_move, 0.0f));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
            yCentro = yCentro + value_move;
        }
        else if (key == GLFW_KEY_UP) {
            matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ,
                                                 glm::vec3(0.0f, -value_move, 0.0f));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
            yCentro = yCentro - value_move;
        }
        else if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }
        else if (key == GLFW_KEY_KP_ADD)
        {
            matrix_scala_OBJ = glm::scale(matrix_scala_OBJ, glm::vec3(value_scala, value_scala, value_scala));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
        }
        else if (key == GLFW_KEY_KP_SUBTRACT)
        {
            matrix_scala_OBJ = glm::scale(matrix_scala_OBJ, glm::vec3(1.0f / value_scala, 1.0f / value_scala, 1.0f / value_scala));
            matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ * matrix_scala_OBJ;
        }
    }
}

GLuint create_shader(GLenum shaderType, const char* shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    return shader;
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

void colocarObjetoEmPosicaoAdequadaNoEspaco() {
    //Fazer a translacao no meio da tela
    double tmpxpos = WIDTH / 2;
    double tmpypos = HEIGHT / 2;
    matrix_translaction_OBJ = glm::translate(matrix_translaction_OBJ, glm::vec3((float)(tmpxpos), (float)(tmpypos), 0.0f));
    matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ;
    xCentro = tmpxpos;
    yCentro = tmpypos;
    // e rotaciona 180 degress
    //matrix_rotation_OBJ = glm::rotate(matrix_rotation_OBJ, glm::radians(180.0f), glm::vec3(0, 0, 1));
    //matrix_OBJ = matrix_translaction_OBJ * matrix_rotation_OBJ;
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

    float vertices[] = {
            // positions                // colors                // texture coords
            -400.0f, -300.0f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top left
            -400.0f, 300.0f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom left
            400.0f, 300.0f, 0.0f,       0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom right
            400.0f, 300.0f, 0.0f,       0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom right
            400.0f, -300.0f, 0.0f,      1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top right
            -400.0f, -300.0f, 0.0f,     1.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top left
    };

    unsigned int indices[] = {
            0, 1, 2,   // first triangle
            3, 4, 5    // second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertexShaderSource =
            "#version 410\n "
            "layout (location = 0) in vec2 aPos;"
            "layout (location = 2) in vec2 aTexCoord;"
            "out vec2 TexCoord;"
            "uniform mat4 matrix_OBJ;"
            "uniform mat4 proj;"
            "uniform float layer_z;"
            "void main() {"
            "   gl_Position = proj * matrix_OBJ * vec4(aPos,layer_z,1.0);"
            "   TexCoord = aTexCoord;"
            "}";


    const char* fragmentShaderSource =
            "#version 410\n "
            "in vec2 TexCoord;"

            "uniform sampler2D sprite;"
            "uniform float offsetX;"
            "uniform float offsetY;"

            "out vec4 frag_color;"

            "void main() {"
			"	vec4 texel0 = texture(sprite,vec2(-(TexCoord.x + offsetX),-(TexCoord.y + offsetY)));"
            "	frag_color = texel0;"
            "}";






    unsigned int vertexShader = create_shader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = create_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // posições
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //texture1 = create_textures("batman.png");
    //glUniform1i(glGetUniformLocation(shaderProgram, "texture_a"), 0);

    //texture2 = create_textures("container.jpg");
    //glUniform1i(glGetUniformLocation(shaderProgram, "texture_b"), 1);

    glUseProgram(shaderProgram);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	#ifdef __APPLE__
		Sprite* t0 = new Sprite("../resource/fundo.jpg", false, 0.0f, 0.0f, -0.52f, 0.000f);
		Sprite* t1 = new Sprite("../resource/sol.png", true, 0.0f, 0.0f, -0.51f, 0.001f);
		Sprite* t2 = new Sprite("../resource/nuvem.png", true, 0.0f, 0.0f, -0.50f, -0.003f);
		Sprite* t3 = new Sprite("../resource/grama coqueiro.png", true, 0.0f, 0.0f, -0.49f, -0.006);
		Sprite* t4 = new Sprite("../resource/megamen.png", true, 0.0f, 0.0f, -0.48f, 0.012);
	#elif _WIN64
		Sprite* t0 = new Sprite("resource/fundo.jpg", false, 0.0f, 0.0f, -0.52f, 0.000f);
		Sprite* t1 = new Sprite("resource/sol.png", true, 0.0f, 0.0f, -0.51f, 0.001f);
		Sprite* t2 = new Sprite("resource/nuvem.png", true, 0.0f, 0.0f, -0.50f, -0.003f);
		Sprite* t3 = new Sprite("resource/grama coqueiro.png", true, 0.0f, 0.0f, -0.49f, -0.006);
		Sprite* t4 = new Sprite("resource/megamen.png", true, 0.0f, 0.0f, -0.48f, 0.012);
	#endif //APPLE


    layers.push_back(t0);
    layers.push_back(t1);
    layers.push_back(t2);
	layers.push_back(t3);
	layers.push_back(t4);

    //AO INCIAR A MASCARA ESTA EM POSICAO 0,0 SEU CENTRO
    //A TEXTURA PODE ESTAR VIRARA
    //ALGUNS COMANDOS SAO EXECUTADOS
    colocarObjetoEmPosicaoAdequadaNoEspaco();


    //os callback
    // esta para quando clicar com o mouse
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // esta para quando clicar uma tecla
    glfwSetKeyCallback(window, key_callback);
    // esta para quando redimensionar a tela
    glfwSetWindowSizeCallback(window, window_size_callback);

    // glm projecao
    glm::mat4 projection =
            glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < 5; i++) {

            // Define shaderProgram como o shader a ser utilizado
            glUseProgram(shaderProgram);

            glUniformMatrix4fv(
                    glGetUniformLocation(shaderProgram, "proj"), 1,
                    GL_FALSE, glm::value_ptr(projection));

            glUniformMatrix4fv(
                    glGetUniformLocation(shaderProgram, "matrix_OBJ"), 1,
                    GL_FALSE, glm::value_ptr(matrix_OBJ));

            // realiza movimento da camada em X
            layers[i]->moveX();

            glUniform1f(
                    glGetUniformLocation(shaderProgram, "offsetX"), layers[i]->offsetX);
            glUniform1f(
                    glGetUniformLocation(shaderProgram, "offsetY"), layers[i]->offsetY);
            glUniform1f(
                    glGetUniformLocation(shaderProgram, "layer_z"), layers[i]->z);

            // bind Texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, layers[i]->textureId);
            glUniform1i((glGetUniformLocation(shaderProgram, "sprite")), 0);

            // Define vao como verte array atual
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }


        glfwWaitEvents();
//        glfwPollEvents();
        glfwSwapBuffers(window);

    }

    delete t0;
    delete t1;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();

    return 0;
}
