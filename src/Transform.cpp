#include "tools3d/Transform.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <algorithm>


void rl::Transform::SetPosition(const glm::vec3& position)
{
	glm::vec3 offset = position - m_position;
	m_position = position;
	for (Transform* childTransform : m_children)
	{
		childTransform->SetPosition(childTransform->GetPosition() + offset);
	}

	m_modelMatrixDirty = true;
}

void rl::Transform::SetScale(const glm::vec3& scale)
{
	glm::vec3 scaleChange = scale / m_scale;
	m_scale = scale;
	for (Transform* childTransform : m_children)
	{
		childTransform->SetRotation(scaleChange * childTransform->GetRotation());
	}

	m_modelMatrixDirty = true;
}

void rl::Transform::SetRotation(const glm::vec3& rotation)
{
	glm::vec3 rotationOffset = rotation - m_rotation;
	m_rotation = rotation;

	for (Transform* childTransform : m_children)
	{
		childTransform->SetRotation(rotationOffset + childTransform->GetRotation());
	}
	m_modelMatrixDirty = true;
}

glm::mat4& rl::Transform::GetLocalToWorld()
{
	if (m_modelMatrixDirty)
	{

		glm::mat4 rotation = glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z);
		glm::mat4 scale = glm::

		m_cachedModelMatrix = glm::scale(glm::mat4(1), m_scale) * glm::translate(dummy, m_position) * rotation;
		m_modelMatrixDirty = false;
	}

	return m_cachedModelMatrix;
}

void rl::Transform::DetachFromParent()
{
	if (m_parent)
	{
		std::vector<Transform *>& parentAttached = m_parent->m_children;
		auto it = std::find(parentAttached.begin(), parentAttached.end(), this);
		if (it != parentAttached.end())
		{
			std::swap(*it, parentAttached.back());
			parentAttached.pop_back();
		}
		m_parent = nullptr;
	}
}

rl::Transform::~Transform()
{
	DetachAllChildren();
	DetachFromParent();
}
