#include "bkpch.h"
#include "Project.h"

#include "ProjectSerializer.h"

namespace Black {

	Ref<Project> Project::New()
	{
		s_ActiveProject = CreateRef<Project>();
		return s_ActiveProject;
	}

	Ref<Project> Project::Load(const std::filesystem::path& path)
	{
#ifndef BK_NO_YAML
		Ref<Project> project = CreateRef<Project>();

		ProjectSerializer serializer(project);
		if (serializer.Deserialize(path))
		{
			project->m_ProjectDirectory = path.parent_path();
			s_ActiveProject = project;
			return s_ActiveProject;
		}

		return nullptr;
#else
		BK_CORE_ERROR("Project::Load requires yaml-cpp which is not available");
		return nullptr;
#endif
	}

	bool Project::SaveActive(const std::filesystem::path& path)
	{
#ifndef BK_NO_YAML
		ProjectSerializer serializer(s_ActiveProject);
		if (serializer.Serialize(path))
		{
			s_ActiveProject->m_ProjectDirectory = path.parent_path();
			return true;
		}

		return false;
#else
		BK_CORE_ERROR("Project::SaveActive requires yaml-cpp which is not available");
		return false;
#endif
	}

}
