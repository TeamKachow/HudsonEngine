#pragma once
#include "ISerialisable.h"
#include "../Util/stdafx.h"

namespace Hudson::Common
{
    class IResource : public ISerialisable
    {
    protected:
        std::string _path;
        bool _loaded = false;

    public:
        IResource(std::string path);

        const std::string& GetResourcePath();
        bool IsLoaded();

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(_path);
        }
    };

}

CEREAL_REGISTER_POLYMORPHIC_RELATION(Hudson::Common::ISerialisable, Hudson::Common::IResource)
