#ifndef PROJETO_PG_GA_SPRITESHEET_H
	#define PROJETO_PG_GA_SPRITESHEET_H

#pragma once
class SpriteSheet
{
public:
	Texture* texture;
	int actions;
	int frames;
	int currentAction;
	int currentFrame;
	float z;

	SpriteSheet(string filename, int framesParam, int actionsParam, float zParam) {
		texture = new Texture(filename, true);
		actions = actionsParam;
		frames = framesParam;
		currentAction = 0;
		currentFrame = 0;
		z = zParam;

	};
	~SpriteSheet();

	void passUniformsToShader(Shader* shaderProgram) {
		texture->passUniformsToShader(shaderProgram, getOffsetX(), getOffsetY(), z );
	}

	float getOffsetX() {
		return (float)1 / frames * (currentFrame%frames);
	}
	float getOffsetY() {
		return (float)1 / actions * (currentAction%actions);
	}
	void nextFrame() {
		currentFrame++;
	}
	void setActions(int a) {
		currentAction = a;
	}

};

SpriteSheet::~SpriteSheet()
{
	delete texture;
}
#endif
