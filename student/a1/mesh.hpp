#pragma once
#include "course.hpp"
using namespace course;

struct Mesh 
{
    GLuint vao=0,vbo=0,ebo=0;
    GLsizei indexCount=0;
    Mesh()=default;
    Mesh(const Mesh&)=delete; 
    Mesh& operator=(const Mesh&)=delete;
    ~Mesh()
    {
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vbo);
        glDeleteBuffers(1,&ebo);
    }
};

inline std::vector<Vertex> houseVertices()
{
    // TODO A1.1: build wall, roof, door, and window vertices (x,y,r,g,b).
    // Hint: Build CPU positions and colors in std::vector<Vertex>; no OpenGL calls are needed here.
    // In A1, (0, 0) maps to the screen center; x/y are normalized coordinates, not pixels.
    // Build the whole house around local (0, 0), using the center of its outer bounds
    // as the origin: (minX + maxX) / 2 = (minY + maxY) / 2 = 0.
    // A2 rotates/scales about this local origin, then places it at Object::position in TRS mode.
    // Center the whole house, not each roof/wall/door/window separately.
    // The starter roof below is only a drawing check; it is not a centered complete house.

    // TODO A1.1: 벽, 지붕, 문, 창문의 정점(x,y,r,g,b)을 만든다.
    // 힌트: CPU 쪽 위치와 색을 std::vector<Vertex>에 만든다. 여기서는 OpenGL 호출이 필요 없다.
    // A1에서 (0, 0)은 화면 중앙에 대응한다. x/y는 픽셀이 아니라 정규화된 좌표다.
    // 집 전체를 로컬 (0, 0)을 중심으로 만든다. 집 전체 외곽 범위의 중심을
    // 원점으로 삼는다: (minX + maxX) / 2 = (minY + maxY) / 2 = 0.
    // A2의 TRS 모드는 이 로컬 원점을 기준으로 회전·크기 조절한 뒤, Object::position 위치에 배치한다.
    // 지붕/벽/문/창문을 각각 중앙에 맞추지 말고, 집 전체를 중앙에 맞춘다.
    // 아래의 스타터 지붕은 그리기 확인용일 뿐이며, 중심이 맞춰진 완성된 집이 아니다.

    float pixelSize = 0.1f;

    std::vector<Vertex> vec;

    //벽
    Vertex h_v1 = {0,0,1,1,1};
    Vertex h_v2 = { 1,1,1,1,1 };
    Vertex h_v3 = { 1,0,1,1,1 };
    Vertex h_v4 = { 0,1,1,1,1 };

    h_v1 *= pixelSize;
    h_v2 *= pixelSize;
    h_v3 *= pixelSize;
    h_v4 *= pixelSize;

    vec.push_back(h_v1);
    vec.push_back(h_v2);
    vec.push_back(h_v3);
    vec.push_back(h_v4);

    //지붕
    Vertex r_v1 = { -.5,1,1,1,1 };
    Vertex r_v2 = { 0.5,2,1,1,1 };
    Vertex r_v3 = { 1.5,1,1,1,1 };

    r_v1 *= pixelSize;
    r_v2 *= pixelSize;
    r_v3 *= pixelSize;

    vec.push_back(r_v1);
    vec.push_back(r_v2);
    vec.push_back(r_v3);

    //문

    Vertex d_v1 = { 0.3,0,0,1,0 };
    Vertex d_v2 = { 0.7,0.75,0,1,0 };
    Vertex d_v3 = { 0.7,0,0,1,0 };
    Vertex d_v4 = { 0.3,0.75,0,1,0 };

    d_v1 *= pixelSize;
    d_v2 *= pixelSize;
    d_v3 *= pixelSize;
    d_v4 *= pixelSize;

    vec.push_back(d_v1);
    vec.push_back(d_v2);
    vec.push_back(d_v3);
    vec.push_back(d_v4);

    //창문

    Vertex w_v1 = { 0.3f,1,0,0,1 };
    Vertex w_v2 = { 0.7f,1.5f,0,0,1 };
    Vertex w_v3 = { 0.7f,1.0f,0,0,1 };
    Vertex w_v4 = { 0.3f,1.5f,0,0,1 };

    w_v1 *= pixelSize;
    w_v2 *= pixelSize;
    w_v3 *= pixelSize;
    w_v4 *= pixelSize;

    vec.push_back(w_v1);
    vec.push_back(w_v2);
    vec.push_back(w_v3);
    vec.push_back(w_v4);


    //return {{-.55f,.25f,1,.3f,.3f},{.55f,.25f,1,.3f,.3f},{0,.7f,1,.3f,.3f}};
    return vec;
}
inline std::vector<unsigned> houseIndices()
{
    // TODO A1.2: add triangle indices for all four house parts.
    // Hint: Add vertex indices to std::vector<unsigned>, with three indices per triangle.

    // TODO A1.2: 집의 네 부분 모두에 대한 삼각형 인덱스를 추가한다.
    // 힌트: 정점 인덱스를 std::vector<unsigned>에 추가한다. 삼각형 하나당 인덱스 세 개다.
    return 
    {
        0,1,2,
        0,3,1,
        4,5,6,
        7,8,9,
        7,10,8,
        11,12,13,
        11,14,12,
    };
}
inline void createMesh(Mesh& mesh,const std::vector<Vertex>& vertices,const std::vector<unsigned>& indices)
{
    require(mesh.vao==0,"Create each immutable mesh only once");
    if(vertices.empty()||indices.empty())
        return;
    // TODO A1.3: glCreateBuffers + glNamedBufferStorage for VBO/EBO; byte sizes, flags=0.
    // Hint: Use glCreateBuffers(count, names) and glNamedBufferStorage(buffer, byteSize, data, flags). Use size() * sizeof(element type) and data().
    // Create names in mesh.vbo / mesh.ebo and upload the supplied arrays.
    // TODO A1.4: create VAO, attach VBO to binding 0, attach EBO.
    // Hint: Use glCreateVertexArrays, glVertexArrayVertexBuffer(vao, binding, buffer, offset, stride), and glVertexArrayElementBuffer.
    // Binding index 0; offset 0; stride sizeof(Vertex).
    // TODO A1.5: configure position (location 0, 2 floats) and color (location 1, 3 floats).
    // Hint: Use glVertexArrayAttribFormat, glVertexArrayAttribBinding, and glEnableVertexArrayAttrib. Use offsetof(Vertex, x) / offsetof(Vertex, r) for byte offsets.
    // Both attributes use VBO binding index 0. u/v are not enabled yet.

    // TODO A1.3: VBO/EBO를 glCreateBuffers + glNamedBufferStorage로 만든다. 크기는 바이트 단위, flags=0.
    // 힌트: glCreateBuffers(개수, 이름들)와 glNamedBufferStorage(버퍼, 바이트크기, 데이터, 플래그)를 사용한다. size() * sizeof(원소 타입)과 data()를 사용한다.
    // mesh.vbo / mesh.ebo에 이름(ID)을 만들고, 전달받은 배열을 업로드한다.
    // TODO A1.4: VAO를 만들고, VBO를 binding 0에 연결하고, EBO를 연결한다.
    // 힌트: glCreateVertexArrays, glVertexArrayVertexBuffer(vao, 바인딩, 버퍼, 오프셋, 스트라이드), glVertexArrayElementBuffer를 사용한다.
    // 바인딩 인덱스 0, 오프셋 0, 스트라이드 sizeof(Vertex).
    // TODO A1.5: 위치(location 0, float 2개)와 색상(location 1, float 3개)을 설정한다.
    // 힌트: glVertexArrayAttribFormat, glVertexArrayAttribBinding, glEnableVertexArrayAttrib를 사용한다. 바이트 오프셋은 offsetof(Vertex, x) / offsetof(Vertex, r)을 사용한다.
    // 두 속성 모두 VBO 바인딩 인덱스 0을 사용한다. u/v는 아직 활성화하지 않는다.

    mesh.indexCount=GLsizei(indices.size());
    glCreateBuffers(1, &mesh.vbo);
    glCreateBuffers(1, &mesh.ebo);
    glNamedBufferStorage(mesh.vbo, sizeof(Vertex) * vertices.size(), &vertices[0], 0);
    glNamedBufferStorage(mesh.ebo,sizeof(unsigned) * indices.size(), &indices[0], 0);

    glCreateVertexArrays(1, &mesh.vao);
    glVertexArrayVertexBuffer(mesh.vao,0,mesh.vbo,0,sizeof(Vertex));
    glVertexArrayElementBuffer(mesh.vao,mesh.ebo);

    glVertexArrayAttribFormat(mesh.vao,0,2,GL_FLOAT,GL_FALSE,offsetof(Vertex,x));
    glVertexArrayAttribBinding(mesh.vao,0,0);
    glEnableVertexArrayAttrib(mesh.vao,0);

    glVertexArrayAttribFormat(mesh.vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, r));
    glVertexArrayAttribBinding(mesh.vao, 1, 0);
    glEnableVertexArrayAttrib(mesh.vao, 1);
}
inline void drawMesh(const Mesh& mesh)
{
    if(!mesh.vao)
        return; // Keeps an unfinished starter runnable.
                // 미완성 스타터도 실행될 수 있게 해 둔 처리다.

    // TODO A1.6: bind VAO and issue the indexed draw call.
    // Hint: Use glBindVertexArray followed by glDrawElements(mode, count, type, indices), with GL_TRIANGLES, GL_UNSIGNED_INT, and nullptr for the EBO start offset.
    // Count means number of indices, not number of triangles.

    // TODO A1.6: VAO를 바인딩하고 인덱스 기반 그리기 호출을 한다.
    // 힌트: glBindVertexArray 다음에 glDrawElements(모드, 개수, 타입, 인덱스)를 호출한다. GL_TRIANGLES, GL_UNSIGNED_INT, EBO 시작 오프셋으로 nullptr를 사용한다.
    // 개수(count)는 삼각형 수가 아니라 인덱스 수다.

    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES,mesh.indexCount,GL_UNSIGNED_INT,nullptr);
}
