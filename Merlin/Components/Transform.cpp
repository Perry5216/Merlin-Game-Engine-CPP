#include "stdafx.h"
#include "Transform.h"
#include "GameObject.h"

namespace Merlin{
	glm::vec3 const Transform::FORWARD(0.0, 0.0, 1.0);
	glm::vec3 const Transform::UP(0.0, 1.0, 0.0);
	glm::vec3 const Transform::RIGHT(1.0, 0.0, 0.0);

	Transform::Transform(){
		position = glm::vec3(0, 0, 0);
		rotation = glm::quat(glm::vec3(0, 0, 0));
		scale = glm::vec3(0, 0, 0);
	}

	Transform::Transform(GameObject * gameObject, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :Component(gameObject){
		this->position = position;
		// Convert euler argument to a quaternion
		float x = glm::radians(rotation.x);
		float y = glm::radians(rotation.y);
		float z = glm::radians(rotation.z);
		this->rotation = glm::quat(glm::vec3(x, y, z));
		this->scale = scale;
	}

	Transform::~Transform(){
	}

	glm::mat4x4 Transform::GetTransformation(){
		glm::mat4x4 scaleMatrix = glm::scale(glm::mat4x4(1.0f), scale);
		glm::mat4x4 rotationMatrix = glm::mat4_cast(rotation);
		glm::mat4x4 translationMatrix = glm::translate(glm::mat4x4(1), position);
		return translationMatrix * rotationMatrix * scaleMatrix;
	}
}
