#include "bkpch.h"
#include "Black/Renderer/Buffer.h"
#include "Black/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace Black {

	// VertexBuffer
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size)
		{
			glCreateBuffers(1, &m_RendererID);
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}

		~OpenGLVertexBuffer()
		{
			glDeleteBuffers(1, &m_RendererID);
		}

		void Bind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		}

		void Unbind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	// IndexBuffer
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size)
			: m_Count(size / sizeof(uint32_t))
		{
			glCreateBuffers(1, &m_RendererID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
		}

		~OpenGLIndexBuffer()
		{
			glDeleteBuffers(1, &m_RendererID);
		}

		void Bind() const override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		}

		void Unbind() const override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		return CreateRef<OpenGLIndexBuffer>(indices, size);
	}

}
