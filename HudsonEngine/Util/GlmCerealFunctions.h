#pragma once

template<class Archive>
void serialize(Archive& archive,
    glm::vec1& m)
{
    archive(m.x);
}

template<class Archive>
void serialize(Archive& archive,
    glm::vec2& m)
{
    archive(m.x, m.y);
}

template<class Archive>
void serialize(Archive& archive,
    glm::vec3& m)
{
    archive(m.x, m.y, m.z);
}

template<class Archive>
void serialize(Archive& archive,
    glm::vec4& m)
{
    archive(m.x, m.y, m.z, m.w);
}




