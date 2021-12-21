#ifndef OPENGL_STATICMESH_H
#define OPENGL_STATICMESH_H

#include <QtOpenGL>
#include <QOpenGLFunctions_4_5_Core>
#include <QVector>

template <size_t nverts = 3, size_t nnorms = 3, size_t ntexcs = 2>
class StaticMesh
{
    // interleave stride
    static constexpr size_t stride = (nverts + nnorms + ntexcs) * sizeof(float);
    // offset per attribute type
    static constexpr size_t offset_vertex = 0;
    static constexpr size_t offset_norm = nverts * sizeof(float);
    static constexpr size_t offset_tex = (nverts + nnorms) * sizeof(float);
    // glsl attribute locations
    static constexpr GLuint vertex_loc = 0;
    static constexpr GLuint normal_loc = vertex_loc + (nverts > 0);
    static constexpr GLuint texcoord_loc = normal_loc + (nnorms > 0);

    size_t d_vertex_count;
    GLuint d_attribute_object;
    GLuint d_buffer_object;
    QOpenGLFunctions_4_5_Core *d_gl; // non owning

    public:
        StaticMesh(QOpenGLFunctions_4_5_Core *gl45);
        ~StaticMesh();

        StaticMesh(StaticMesh &&other) noexcept;
        StaticMesh &operator=(StaticMesh &&other) noexcept;
        void swap(StaticMesh &other) noexcept;

        // utility
        bool is_valid() const noexcept;
        size_t vertex_count() const noexcept;

        // rendering
        void render() const noexcept;
        void render(GLuint drawtype) const noexcept;

        // modification
        void update(QVector<float> const &data, GLuint storage_flag = GL_STATIC_DRAW);
        void initialize();

        /* Check whether the template parameters are valid */
        static_assert(nverts != 0 && nverts <= 4, "Vertex dimension should be at least 1 and max 4");
        static_assert(nnorms <= 4, "Normal dimension can be max 4");
        static_assert(ntexcs <= 4, "Tex coords can be max 4");
};

#include "staticmesh.f"

#endif