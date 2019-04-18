//
// Created by Gian Boschetti on 2019-04-13.
//

#ifndef TESTANDO_SHADER_H
#define TESTANDO_SHADER_H

using namespace std;

class Shader {
public:
    GLuint Program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
        // A. obtem o codigo de um arquivo seja vertex/fragment
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // Garante que objetos ifstream podem lançar exceções
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try {
            //  Abre os arquivos
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            //Le o conteudo dos arquivos
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Fecha os arquivos abertos
            vShaderFile.close();
            fShaderFile.close();

            // Converte a stream em uma string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "Erro no Shader: Arquivo nao lido com sucesso;" << std::endl;
        }

        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar * fShaderCode = fragmentCode.c_str();

        // B. Compilar os shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // define Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        // Se houver imprime os erros de  compilação
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "Erro vertexShader: falha de compilação\n" << infoLog << std::endl;
        }

        // define Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        // Se houver imprime os erros de  compilação
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "Erro fragmentShader: falha de compilação\n" << infoLog << std::endl;
        }

        // criacao do ShaderProgram
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);

        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "Erro na linkagem do programa do Shader\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void UseProgramShaders() {
        glUseProgram(this->Program);
    }
};


#endif //TESTANDO_SHADER_H
