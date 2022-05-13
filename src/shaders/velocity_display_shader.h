#ifndef VELOCITY_DISPLAY_SHADER_H
#define VELOCITY_DISPLAY_SHADER_H

#include <string>

#include <Corrade/Containers/Reference.h>
#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Matrix3.h>

#include "shader_path.h"

using namespace Magnum;

class VelocityDisplayShader : public GL::AbstractShaderProgram
{

    public:
        
        typedef GL::Attribute<0, Vector2> Position;
        typedef GL::Attribute<1, Vector2> TextureCoordinates;

        explicit VelocityDisplayShader(NoCreateT): GL::AbstractShaderProgram{NoCreate} {}
        
        explicit VelocityDisplayShader()
        {
            MAGNUM_ASSERT_GL_VERSION_SUPPORTED(GL::Version::GL330);

            GL::Shader Vert{GL::Version::GL330, GL::Shader::Type::Vertex};
            GL::Shader Frag{GL::Version::GL330, GL::Shader::Type::Fragment};

            Vert.addFile(Path_+"texture_base_shader.vert");
            Frag.addFile(Path_+"velocity_display_shader.frag");

            CORRADE_INTERNAL_ASSERT_OUTPUT(GL::Shader::compile({Vert, Frag}));

            attachShaders({Vert, Frag});

            CORRADE_INTERNAL_ASSERT_OUTPUT(link());

            setUniform(uniformLocation("u_texture"), TextureUnit);
            ScaleUniform_ = uniformLocation("u_scale");
            ShowOnlyMagnitudeUniform_ = uniformLocation("u_show_only_magnitude");
            TransformationMatrixUniform_ = uniformLocation("u_matrix");
        }

        VelocityDisplayShader& setScale(const Float s)
        {
            setUniform(ScaleUniform_, s);
            return *this;
        }
        
        VelocityDisplayShader& setShowOnlyMagnitude(const bool b)
        {
            setUniform(ShowOnlyMagnitudeUniform_, b);
            return *this;
        }

        VelocityDisplayShader& setTransformation(const Matrix3& t)
        {
            setUniform(TransformationMatrixUniform_, t);
            return *this;
        }
        
        VelocityDisplayShader& bindTexture(GL::Texture2D& Texture)
        {
            Texture.bind(TextureUnit);
            return *this;
        }

    private:
        
        enum: Int { TextureUnit = 0 };

        std::string Path_{SHADER_PATH};

        Int TransformationMatrixUniform_;
        Float ScaleUniform_ = 1.0f;
        GLboolean ShowOnlyMagnitudeUniform_ = false;
};

#endif // VELOCITY_DISPLAY_SHADER_H
