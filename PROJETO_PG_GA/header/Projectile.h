#pragma once
class Projectile : public GameObject
{
public:
	float previousReactionTime;

	Projectile(Shader* shaderProgram, SpriteSheet* sprites, bool *gameIsRunning);
	~Projectile();

	void doingLoping();
};

Projectile::Projectile(Shader* shaderProgram, SpriteSheet* sprites, bool *gameIsRunning)
	: GameObject(shaderProgram, sprites, 70.0f, 70.0f, 900.0f, 490.0f, -10.0f, true, gameIsRunning)
{
}

void Projectile::doingLoping() {
	double currentSeconds = glfwGetTime();
	double elapsedSeconds = currentSeconds - previousReactionTime;
	if (*gameIsRunning && elapsedSeconds > 0.016) {
		previousReactionTime = currentSeconds;

		position->move(speed, 0.0f);
		if (position->xCenter <= 0.0f) {
			position->move(800.0f - position->xCenter, 0.0f);
		}
	}
}


Projectile::~Projectile()
{
}
