//
// Created by Gian Boschetti on 2019-04-15.
//

#ifndef PROJETO_PG_GA_GAMEOBJECT_H
#define PROJETO_PG_GA_GAMEOBJECT_H
#endif //PROJETO_PG_GA_GAMEOBJECT_H


class GameObject{
public:
	Shader *shaderProgram;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    float vertices;
    GLuint indices[6] ={
            0, 1, 2,   // first triangle
            0, 3, 2    // second triangle
    };


    GameObject(Shader* shaderProgramParam, float verticesParam) {
        shaderProgram = shaderProgramParam;
		vertices = verticesParam;
        setup();
    }


//    GameObject(GLuint shaderProgram,float verticesParam[]) {
//        vertices = verticesParam;
//        indices = {
//            0, 1, 2,   // first triangle
//            0, 3, 2    // second triangle
//        };
//        setup();
//    }



    void setup(){

        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices), &vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }


};

