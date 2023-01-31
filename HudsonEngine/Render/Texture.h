#pragma once
#include "../Util/stdafx.h"
#include "../Common/IResource.h"

namespace Hudson::Render {
    class Texture : virtual public Hudson::Common::IResource
    {
    private:
        uint32_t _serialId = rand();

    public:
        // holds the ID of the texture object
        unsigned int ID;
        // texture image dimensions
        unsigned int _width, _height;
        // texture format
        unsigned int _internalFormat; // format of texture object
        unsigned int _imageFormat; // format of loaded image
        // texture configuration
        unsigned int _wrapS; // wrapping mode on S axis
        unsigned int _wrapT; // wrapping mode on T axis
        unsigned int _filterMin; // filtering mode if texture pixels < screen pixels
        unsigned int _filterMax; // filtering mode if texture pixels > screen pixels

        /**
         * \brief Create an empty texture. This is then set up by Generate.
         */
        Texture();
        // TODO: should the destructor destroy the GL texture?
        ~Texture() override = default;
        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;

        uint32_t GetSerialID() override;
        void Load() override;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(cereal::virtual_base_class<Common::IResource>(this), _serialId, _width, _height, _imageFormat, _internalFormat, _wrapS, _wrapT, _filterMin, _filterMin);
        }
    };
}

CEREAL_REGISTER_TYPE(Hudson::Render::Texture)