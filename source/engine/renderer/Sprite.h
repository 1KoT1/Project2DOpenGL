#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glad/glad.h>


namespace Renderer
{
	class ShaderProgram;
	class Texture2D;

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, 
			const std::string& initialSubtextureName, const glm::vec2& position = glm::vec2(0.f), 
			const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);
		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void SetPosition(const glm::vec2& newPosition);
		void SetSize(const glm::vec2& newSize);
		void SetRotation(const float newRotation);
		void SetNewSprite(const std::string& newSubtextureName);

		glm::vec2 GetPosition() const { return spr_pos; }
		glm::vec2 GetSize() const { return spr_size; }
		float GetRotation() const { return spr_rot; }

		std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram() { return spr_shader; }
		std::shared_ptr<Renderer::Texture2D> GetTexture() { return spr_texture; }

		virtual void Render() const;
	protected:
		std::shared_ptr<Texture2D> spr_texture;
		std::shared_ptr<ShaderProgram> spr_shader;

		glm::vec2 spr_pos, spr_size;
		float spr_rot;
		std::string spr_subtexture_name;

		GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer;
	};
}