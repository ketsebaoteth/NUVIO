#pragma once
#include "core/dna/project.h"

NUVIO_NAMESPACE_BEGIN

class ProjectManager {
    public:
        ProjectManager();
        ~ProjectManager();
        static bool loadProject(const std::string& projectPath);
        static const Projects& getProjects();
    private:
        Projects mProjects;
};

extern ProjectManager gProjectManager;

NUVIO_NAMESPACE_END
