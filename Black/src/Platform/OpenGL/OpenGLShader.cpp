#include "bkpch.h"
#include "Black/Renderer/Shader.h"
#include "Black/Renderer/RendererAPI.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>

namespace Black {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		BK_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	static std::string ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != (size_t)-1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				BK_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			BK_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}

	static std::unordered_map<GLenum, std::string> PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			BK_CORE_ASSERT(eol != std::string::npos, "Syntax error in shader file!");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			BK_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel",
				"Invalid shader type specification!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				(pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	static GLuint CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);
		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, nullptr);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());
			glDeleteShader(shader);

			BK_CORE_ERROR("{0}", infoLog.data());
			BK_CORE_ASSERT(false, "Shader compilation failure!");
			return 0;
		}
		return shader;
	}

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath)
			: m_Name(ExtractName(filepath))
		{
			std::string source = ReadFile(filepath);
			auto shaderSources = PreProcess(source);
			Compile(shaderSources);
		}

		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
			: m_Name(name)
		{
			std::unordered_map<GLenum, std::string> shaderSources;
			shaderSources[GL_VERTEX_SHADER] = vertexSrc;
			shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
			Compile(shaderSources);
		}

		~OpenGLShader()
		{
			glDeleteProgram(m_RendererID);
		}

		void Bind() const override
		{
			glUseProgram(m_RendererID);
		}

		void Unbind() const override
		{
			glUseProgram(0);
		}

		const std::string& GetName() const override { return m_Name; }

		void SetInt(const std::string& name, int value) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniform1i(location, value);
		}

		void SetFloat(const std::string& name, float value) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniform1f(location, value);
		}

		void SetFloat2(const std::string& name, const glm::vec2& value) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniform2f(location, value.x, value.y);
		}

		void SetFloat3(const std::string& name, const glm::vec3& value) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniform3f(location, value.x, value.y, value.z);
		}

		void SetFloat4(const std::string& name, const glm::vec4& value) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}

		void SetMat3(const std::string& name, const glm::mat3& matrix) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void SetMat4(const std::string& name, const glm::mat4& matrix) override
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
		{
			GLuint program = glCreateProgram();
			BK_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now!");
			std::array<GLuint, 2> shaderIDs;
			int shaderIDIndex = 0;

			for (auto& [type, source] : shaderSources)
			{
				GLuint shader = CompileShader(type, source);
				glAttachShader(program, shader);
				shaderIDs[shaderIDIndex++] = shader;
			}

			glLinkProgram(program);

			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

				glDeleteProgram(program);
				for (int i = 0; i < shaderIDIndex; i++)
					glDeleteShader(shaderIDs[i]);

				BK_CORE_ERROR("{0}", infoLog.data());
				BK_CORE_ASSERT(false, "Shader link failure!");
				return;
			}

			for (int i = 0; i < shaderIDIndex; i++)
			{
				glDetachShader(program, shaderIDs[i]);
				glDeleteShader(shaderIDs[i]);
			}

			m_RendererID = program;
		}

		static std::string ExtractName(const std::string& filepath)
		{
			auto lastSlash = filepath.find_last_of("/\\");
			lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
			auto lastDot = filepath.rfind('.');
			auto count = (lastDot == std::string::npos) ? filepath.size() - lastSlash : lastDot - lastSlash;
			return filepath.substr(lastSlash, count);
		}

	private:
		uint32_t m_RendererID = 0;
		std::string m_Name;
	};

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		return CreateRef<OpenGLShader>(filepath);
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

}
