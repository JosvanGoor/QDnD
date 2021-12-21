#include "staticmesh.h"

#define THDR template <size_t nverts, size_t nnorms, size_t ntexcs>
#define TSTATICMESH StaticMesh<nverts, nnorms, ntexcs>

////////////////////
//  Constructors  //
////////////////////

THDR TSTATICMESH::StaticMesh(QOpenGLFunctions_4_5_Core *gl45)
:   d_vertex_count(0),
    d_attribute_object(0),
    d_buffer_object(0),
    d_gl(gl45)
{
    initialize();
}


THDR TSTATICMESH::~StaticMesh()
{
    if (d_attribute_object)
        d_gl->glDeleteVertexArrays(1, &d_attribute_object);
    
    if (d_buffer_object)
        d_gl->glDeleteBuffers(1, &d_buffer_object);
}


THDR TSTATICMESH::StaticMesh(StaticMesh &&other) noexcept
:   d_vertex_count(other.d_vertex_count),
    d_attribute_object(other.d_attribute_object),
    d_buffer_object(other.d_buffer_object),
    d_gl(other.d_gl)
{
    other.d_vertex_count = 0;
    other.d_attribute_object = 0;
    other.d_buffer_object = 0;
}


THDR TSTATICMESH &TSTATICMESH::operator=(StaticMesh &&other) noexcept
{
    swap(other);
    return *this;
}


THDR void TSTATICMESH::swap(StaticMesh &other) noexcept
{
    std::swap(d_vertex_count, other.d_vertex_count);
    std::swap(d_attribute_object, other.d_attribute_object);
    std::swap(d_buffer_object, other.d_buffer_object);
    std::swap(d_gl, other.d_gl);
}


////////////////////
//    Utility     //
////////////////////

THDR bool TSTATICMESH::is_valid() const noexcept
{
    return d_attribute_object != 0;
}


THDR size_t TSTATICMESH::vertex_count() const noexcept
{
    return d_vertex_count * (nverts + nnorms + ntexcs);
}


////////////////////
//   Rendering    //
////////////////////

THDR void TSTATICMESH::render() const noexcept
{
    render(GL_TRIANGLES);
}


THDR void TSTATICMESH::render(GLuint drawtype) const noexcept
{
    d_gl->glBindVertexArray(d_attribute_object);
    d_gl->glDrawArrays(drawtype, 0, d_vertex_count);
    d_gl->glBindVertexArray(0);
}


////////////////////
//  Modification  //
////////////////////

THDR void TSTATICMESH::update(QVector<float> const &data, GLuint storage_flag)
{
    if (!is_valid())
        initialize();

    d_gl->glBindBuffer(GL_ARRAY_BUFFER, d_buffer_object);
    d_gl->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), storage_flag);
    d_gl->glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_vertex_count = data.size() / (nverts + nnorms + ntexcs);
}


THDR void TSTATICMESH::initialize()
{
    d_gl->glGenVertexArrays(1, &d_attribute_object);
    d_gl->glBindVertexArray(d_attribute_object);

    d_gl->glGenBuffers(1, &d_buffer_object);
    d_gl->glBindBuffer(GL_ARRAY_BUFFER, d_buffer_object);
    d_gl->glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

    // vertices are bound always.
    d_gl->glVertexAttribPointer
    (
        vertex_loc,
        nverts,
        GL_FLOAT,
        GL_FALSE,
        stride,
        reinterpret_cast<void*>(offset_vertex)
    );
    d_gl->glEnableVertexAttribArray(vertex_loc);

    if constexpr (nnorms > 0)
    {
        d_gl->glVertexAttribPointer
        (
            normal_loc,
            nnorms,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offset_norm)
        );
        d_gl->glEnableVertexAttribArray(normal_loc);
    }

    if constexpr (ntexcs > 0)
    {
        d_gl->glVertexAttribPointer
        (
            texcoord_loc,
            ntexcs,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offset_tex)
        );
        d_gl->glEnableVertexAttribArray(texcoord_loc);
    }

    d_gl->glBindVertexArray(0);
    d_gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#undef THDR
#undef TSTATICMESH