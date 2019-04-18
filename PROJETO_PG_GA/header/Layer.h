#ifndef TESTANDO_SPRITE_H 
#define TESTANDO_SPRITE_H

class Layer {
public:
	Texture* texture;
    float offsetX;
    float offsetY;
    float z;
    float speedX;

    Layer() {

    }

	Layer(string filename, bool useAlpha, float paramOffsetX, float paramOffsetY, float paramZ, float paramSpeedX)
    {
		texture = new Texture(filename, useAlpha);
        offsetX = paramOffsetX;
        offsetY = paramOffsetY;
        z = paramZ;
        speedX = paramSpeedX;
    }

	void passUniformsToShader(Shader* shaderProgram) {
		texture->passUniformsToShader(shaderProgram, offsetX, offsetY, z);
	}

    void moveX()
    {
        offsetX += speedX;
//        if (offsetX > 1.00f)
//            offsetX -= 1.00f;
//		else if (offsetX < -1.00f)
//			offsetX += 1.00f;
    }
};

#endif