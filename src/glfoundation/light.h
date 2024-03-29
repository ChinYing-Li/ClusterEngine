#pragma once

#include "glincludes.h"
#include "framebuffer.h"
#include "texture.h"

namespace Cluster{

/*
 *
 */
class Light
{
public:
    Light();
    virtual ~Light() = default;

    bool is_enabled();

    enum Type
    {
      SPOTLIGHT,
      POINTLIGHT,
      DIRECTIONAL,
    };

    void turn_off();
    void turn_on();

    Type get_type() const;
    virtual std::shared_ptr<Texture> get_shadowmap() = 0;
    void setup_shadowbuffer(unsigned int width, unsigned int height);
    virtual void setup_shadow_map(const std::vector<int>& dimensions) = 0;

    void set_color(const glm::vec3 new_color);
    void set_const_attenuation(const float const_atten);
    void set_linear_attenuation(const float linear_atten);
    void set_quadratic_attenuation(const float quad_atten);
    void set_ambient_strength(const glm::vec3 new_amb_strength);

    void virtual set_shader(int index, GLuint& shaderID);

protected:
    bool m_on_state = true;
    bool m_is_spotlight = false; // TODO: remove this redundant variable
    bool m_is_local = false;

    float m_const_atten;
    float m_linear_atten;
    float m_quadratic_atten;

    glm::vec3 m_ambient_strength;
    glm::vec3 m_color;

    FrameBuffer m_shadowbuffer;
    const Type m_type = Type::SPOTLIGHT;
};

/*
 *
 */
class SpotLight final : public Light
{
public:
    SpotLight();
    SpotLight(const glm::vec3 position, glm::vec3 conedirection, const float cutoff, const float exponent);
    ~SpotLight() = default;

    void set_shader(int index, GLuint& shaderID) override;
    virtual void setup_shadow_map(const std::vector<int>& dimensions) override {};

protected:
    class Deferred;
    class Forward;
    class DeferredCluster;
    class ForwardCluster;

    float m_cutoff;
    float m_exponent;
    glm::vec3 m_position;
    glm::vec3 m_conedirection;
    const Type m_type = Type::SPOTLIGHT;
};

/*
 *
 */
class PointLight final : public Light
{
public:
    PointLight();
    PointLight(const glm::vec3 position);
    ~PointLight() = default;

    void set_shader(int index, GLuint& shaderID) override;
    virtual void setup_shadow_map(const std::vector<int>& dimensions) override;
    std::shared_ptr<Texture> get_shadowmap() override;

protected:
    std::shared_ptr<TextureCubemap> m_shadow_cubemap;
    glm::vec3 m_position;
    const Type m_type = Type::POINTLIGHT;
};

/*!
 *
 */
class DirectionalLight final : public Light
{
public:
    DirectionalLight() = default;
    DirectionalLight(const glm::vec3 halfvec);
    ~DirectionalLight() = default;

    void set_shader(int index, GLuint& shaderID) override;
    void set_direction(const glm::vec3 halfvec);
    virtual void setup_shadow_map(const std::vector<int>& dimensions) override;
    std::shared_ptr<Texture> get_shadowmap() override;

protected:
    std::shared_ptr<Texture2D> m_shadow_map;
    glm::vec3 m_direction;
    glm::mat4 m_shadowspace;
    const Type m_type = Type::DIRECTIONAL;
};

} // namespace Cluster
