#include "HealActor.h"

#include "../../engine/physics/Collider.h"

namespace Game
{
	HealActor::HealActor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	:Actor(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_InteractiveObject, startPosition, startSize);

		_collider->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Enemy, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Projectile, EResponseType::ERT_Ignore);

		_heal_value = 5;
	}
	void HealActor::BeginPlay()
	{
		
	}
}