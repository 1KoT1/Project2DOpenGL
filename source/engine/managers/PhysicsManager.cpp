#include "PhysicsManager.h"
#include "GameManager.h"

#include "../../game/Actor.h"

#include "../physics/Collider.h"

#include "../../main.h"

bool PhysicsManager::CanMove(Game::Actor* checkActor, const glm::vec2& nextPosition)
{
	std::shared_ptr<Physics::Collider> checkCollider = checkActor->GetCollider();
	const glm::vec2& sizeActor = checkCollider->GetSize();
	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		std::shared_ptr<Physics::Collider> currentActorCollider = actor->GetCollider();
		glm::vec2 posCurrentCollider = actor->GetPosition(), sizeCurrentCollider = currentActorCollider->GetSize();
		if (IsBlocking(posCurrentCollider, nextPosition, sizeActor, sizeCurrentCollider, checkCollider, currentActorCollider))
			return false;
	}
	return true;
}

void PhysicsManager::CheckOverlapping(std::shared_ptr<Physics::Collider> checkCollider)
{
	std::shared_ptr<Game::Actor> ownerCollider;
	const glm::vec2& sizeActor = checkCollider->GetSize(), checkPosition = checkCollider->GetPosition();
	std::vector<std::shared_ptr<Game::Actor>>::iterator it = all_actors.begin();
	for (; it < all_actors.end(); it++)
	{
		std::shared_ptr<Physics::Collider> currentActorCollider = it->get()->GetCollider();
		glm::vec2 posCurrentCollider = currentActorCollider->GetPosition(), sizeCurrentCollider = currentActorCollider->GetSize();
		if (IsOverlap(posCurrentCollider, checkPosition, sizeActor, sizeCurrentCollider, checkCollider, currentActorCollider))
		{
			ownerCollider = checkCollider->GetOwner();
			if(ownerCollider)
				ownerCollider->Overlap(*it);
			break;
		}
			
	}
}

bool PhysicsManager::IsOverlap(const glm::vec2& posCurrentCollider, const glm::vec2& checkPosition, const glm::vec2& sizeActor, const glm::vec2& sizeCurrentCollider,
	std::shared_ptr<Physics::Collider> checkCollider,
	std::shared_ptr<Physics::Collider> currentActorCollider)
{
	return ((posCurrentCollider.x <= checkPosition.x + sizeActor.x && posCurrentCollider.x >= checkPosition.x && ((posCurrentCollider.y >= checkPosition.y && posCurrentCollider.y + sizeCurrentCollider.y <= checkPosition.y + sizeActor.y)
		|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y && posCurrentCollider.y <= checkPosition.y)
		|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y + sizeActor.y && posCurrentCollider.y <= checkPosition.y + sizeActor.y)))
		|| (posCurrentCollider.x + sizeCurrentCollider.x >= checkPosition.x && posCurrentCollider.x <= checkPosition.x && ((posCurrentCollider.y >= checkPosition.y && posCurrentCollider.y + sizeCurrentCollider.y <= checkPosition.y + sizeActor.y)
			|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y && posCurrentCollider.y <= checkPosition.y)
			|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y + sizeActor.y && posCurrentCollider.y <= checkPosition.y + sizeActor.y))))
		&& checkCollider->GetResponseType(currentActorCollider->GetObjectType()) == EResponseType::ERT_Overlap;
}

bool PhysicsManager::IsBlocking(const glm::vec2& posCurrentCollider, const glm::vec2& nextPosition, const glm::vec2& sizeActor, const glm::vec2& sizeCurrentCollider,
	std::shared_ptr<Physics::Collider> checkCollider,
	std::shared_ptr<Physics::Collider> currentActorCollider)
{
	return ((posCurrentCollider.x <= nextPosition.x + sizeActor.x && posCurrentCollider.x >= nextPosition.x && ((posCurrentCollider.y >= nextPosition.y && posCurrentCollider.y + sizeCurrentCollider.y <= nextPosition.y + sizeActor.y)
		|| (posCurrentCollider.y + sizeCurrentCollider.y >= nextPosition.y && posCurrentCollider.y <= nextPosition.y)
		|| (posCurrentCollider.y + sizeCurrentCollider.y >= nextPosition.y + sizeActor.y && posCurrentCollider.y <= nextPosition.y + sizeActor.y)))
		|| (posCurrentCollider.x + sizeCurrentCollider.x >= nextPosition.x && posCurrentCollider.x <= nextPosition.x && ((posCurrentCollider.y >= nextPosition.y && posCurrentCollider.y + sizeCurrentCollider.y <= nextPosition.y + sizeActor.y)
			|| (posCurrentCollider.y + sizeCurrentCollider.y >= nextPosition.y && posCurrentCollider.y <= nextPosition.y)
			|| (posCurrentCollider.y + sizeCurrentCollider.y >= nextPosition.y + sizeActor.y && posCurrentCollider.y <= nextPosition.y + sizeActor.y))))
		&& checkCollider->GetResponseType(currentActorCollider->GetObjectType()) == EResponseType::ERT_Block;
}

