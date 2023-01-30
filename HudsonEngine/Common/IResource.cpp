#include "IResource.h"

Hudson::Common::IResource::IResource(std::string path) : _path(path)
{
}

const std::string& Hudson::Common::IResource::GetResourcePath()
{
    return _path;
}

bool Hudson::Common::IResource::IsLoaded()
{
    return _loaded;
}
