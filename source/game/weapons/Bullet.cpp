#include "Bullet.h"

#include "../../engine/managers/PhysicsManager.h"

namespace Game
{
	Bullet::Bullet(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
		:Actor(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		
	}
	void Bullet::Update(float deltaTime)
	{
		if (PhysicsManager::CanMove(this, _move_vector * _speed * deltaTime))
		{
			SetPosition(GetPosition() + _move_vector * _speed * deltaTime);
			Actor::Update(deltaTime);
		}
	}
}
