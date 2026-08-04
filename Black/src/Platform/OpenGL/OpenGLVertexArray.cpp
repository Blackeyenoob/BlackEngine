#include "bkpch.h"
#include "Black/Renderer/VertexArray.h"
#include "Black/Renderer/Buffer.h"
#include "Black/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace Black {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray()
		{
			glCreateVertexArrays(1, &m_RendererID);
		}

		~OpenGLVertexArray()
		{
			glDeleteVertexArrays(1, &m_RendererID);
		}

		void Bind() const override
		{
			glBindVertexArray(m_RendererID);
		}

		void Unbind() const override
		{
			glBindVertexArray(0);
		}

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override
		{
			glBindVertexArray(m_RendererID);
			vertexBuffer->Bind();

			const auto& layout = vertexBuffer->GetLayout();
			uint32_t vertexBufferIndex = 0;
			for (const auto& element : layout)
			{
				switch (element.Type)
				{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(vertexBufferIndex);
					glVertexAttribPointer(vertexBufferIndex,
						element.GetComponentCount(),
						GL_FLOAT,
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
					vertexBufferIndex++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(vertexBufferIndex);
					glVertexAttribIPointer(vertexBufferIndex,
						element.GetComponentCount(),
						element.Type == ShaderDataType::Bool ? GL_BOOL : GL_INT,
						layout.GetStride(),
						(const void*)element.Offset);
					vertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(vertexBufferIndex);
						glVertexAttribPointer(vertexBufferIndex,
							count,
							GL_FLOAT,
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.Offset + sizeof(float) * count * i));
						vertexBufferIndex++;
					}
					break;
				}
				default:
					BK_CORE_ASSERT(false, "Unknown ShaderDataType!");
				}
			}

			m_VertexBuffers.push_back(vertexBuffer);
		}

		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override
		{
			glBindVertexArray(m_RendererID);
			indexBuffer->Bind();
			m_IndexBuffer = indexBuffer;
		}

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

	Ref<VertexArray> VertexArray::Create()
	{
		return CreateRef<OpenGLVertexArray>();
	}

}
