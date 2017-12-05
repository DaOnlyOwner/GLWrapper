//
// Created by Jan_M720 on 26.09.2017.
//

#pragma once

#include "glm/glm.hpp"
#include <vector>

namespace rl
{
    class Transform
    {
    public:
        static constexpr glm::vec3 XAxis = glm::vec3(1, 0, 0);
        static constexpr glm::vec3 YAxis = glm::vec3(0, 1, 0);
        static constexpr glm::vec3 ZAxis = glm::vec3(0, 0, 1);

        Transform() : m_position(0, 0, 0), m_rotation(0, 0, 0), m_scale(1, 1, 1)
        {}

        const glm::vec3 &GetPosition() const
        { return m_position; }

        const glm::vec3 &GetRotation() const
        { return m_rotation; }

        const glm::vec3 &GetScale() const
        { return m_scale; }

	    void SetPosition(const glm::vec3& position);

	    void SetScale(const glm::vec3& scale);

	    void SetRotation(const glm::vec3& rotation);

	    glm::mat4& GetLocalToWorld();

	    void DetachFromParent();

        void DetachAllChildren()
        {
            for (Transform *childTransform: m_children) childTransform->DetachFromParent();
        }

        void AttachToParent(Transform* parent)
        {
            DetachFromParent();
            m_parent = parent;
        }

        void AddChild(Transform* transformToAdd)
        {
            m_children.push_back(transformToAdd);
            transformToAdd->AttachToParent(this);
        }

	    ~Transform();

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
        glm::vec3 m_forward;
        glm::mat4 m_cachedModelMatrix;
        bool m_modelMatrixDirty = true;


        std::vector<Transform *> m_children;
        Transform *m_parent = nullptr;

    };
}
