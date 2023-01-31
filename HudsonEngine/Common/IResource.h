#pragma once
#include "ISerialisable.h"
#include "../Util/stdafx.h"

namespace Hudson::Common
{
    class IResource : virtual public ISerialisable
    {
    protected:
        /**
         * \brief The path this resource is stored/can be found at.
         */
        std::string _path;
        /**
         * \brief Whether or not this resource is loaded.
         */
        bool _loaded = false;

    public:
        IResource();
        IResource(std::string path);
        ~IResource() override = default;

        /**
         * \brief Get the path this resource is stored at.
         * \return The path to this resource
         */
        const std::string& GetResourcePath();
        /**
         * \brief Load this resource from the stored path.
         * \details Implementations should change the IResource::_loaded variable!
         */
        virtual void Load() = 0;
        /**
         * \brief Check whether the resource has been loaded.
         * \return Whether or not the resource has been loaded
         */
        virtual bool IsLoaded();

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(_path);
        }
    };

}

CEREAL_REGISTER_TYPE(Hudson::Common::IResource)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Hudson::Common::ISerialisable, Hudson::Common::IResource)
