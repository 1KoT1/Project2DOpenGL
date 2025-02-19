#include "Actor.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/TextureRender.h"
#include "../engine/renderer/ShaderRender.h"

#include "../engine/managers/ResourcesManager.h"
#include "../engine/managers/GameManager.h"
#include "../engine/managers/PhysicsManager.h"

#include "../engine/physics/Collider.h"

namespace Game
{
	Actor::Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	{
		_anim_sprite = std::make_unique<Renderer::AnimSprite>(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation);

		_position = startPosition;
		_rotation = startRotation;

	}

	Actor::~Actor()
	{
		
	}


	void Actor::Update(float deltaTime)
	{
		_anim_sprite->Update(deltaTime);
		_anim_sprite->Render();

		PhysicsManager::CheckOverlapping(_collider);
	}

	void Actor::BeginPlay()
	{
	}

	std::shared_ptr<Renderer::AnimSprite> Actor::GetAnimSprite()
	{
		return std::move(_anim_sprite);
	}

	void Actor::SetPosition(const glm::vec2& newPosition)
	{
		_position = newPosition;
		_anim_sprite->SetPosition(newPosition);
		_collider->SetPosition(newPosition);
	}
	void Actor::SetSize(const glm::vec2& newSize)
	{
		_anim_sprite->SetSize(newSize);
		_collider->SetSize(newSize);
	}
	void Actor::SetRotation(const float newRotation)
	{
		_rotation = newRotation;
		_anim_sprite->SetRotation(newRotation);
	}
	void Actor::AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration)
	{
		_anim_sprite->InsertState(stateName, subTextureDuration);
	}
	void Actor::PlayAnim(const std::string& stateName)
	{
		_anim_sprite->SetState(stateName);
	}
	void Actor::DestroyActor()
	{
		std::vector<std::shared_ptr<Game::Actor>>::iterator it = all_actors.begin();
		for (; it != all_actors.end(); it++)
		{
			if (it->get() == this)
			{

				GameManager::SetIterator(all_actors.erase(it));
				break;
			}
		}
	}
}