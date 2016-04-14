#include <assert.h>

#include "Mesh.h"

Mesh::MeshEntry::MeshEntry()
{
    VB = INVALID_OGL_VALUE;
    IB = INVALID_OGL_VALUE;
    NumIndices = 0;
    MaterialIndex = INVALID_MATERIAL;
}

Mesh::MeshEntry::~MeshEntry()
{
    if (VB != INVALID_OGL_VALUE){
        glDeleteBuffers(1, &VB);
    }

    if (IB != INVALID_OGL_VALUE){
        glDeleteBuffers(1, &IB);
    }
}

bool Mesh::MeshEntry::Init(const std::vector<Vertex>& Vertices,
                      const std::vector<unsigned int>& Indices)
{
    NumIndices = Indices.size();

    glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*Vertices.size(),
                    &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*NumIndices,
                    &Indices[0], GL_STATIC_DRAW);

////////////////////////////////////////////////////////////////////
	

    return true;
}

void Mesh::MeshEntry::Init_test(const std::vector<Vertex>& Vertices)
{

}

void Mesh::Clear()
{
    for (unsigned int i = 0; i < m_Textures.size(); i++){
        SAFE_DELETE(m_Textures[i]);
    }
}

bool Mesh::LoadMesh(const std::string& Filename)
{
    // Удаляем данные предыдущей модели (если она была загружена)
    Clear();

    bool Ret = false;

    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(Filename.c_str(),
                                    aiProcess_Triangulate | aiProcess_GenSmoothNormals|
                                    aiProcess_FlipUVs );

    if (pScene){
        Ret = InitFromScene(pScene, Filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }

    return Ret;
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
    m_Entries.resize(pScene->mNumMeshes);
    m_Textures.resize(pScene->mNumMaterials);

    // Инициализируем меши один за другим
    for (unsigned int i = 0; i < m_Entries.size(); i++){
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }

    return InitMaterials(pScene, Filename);
}

void Mesh::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
    m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    for (unsigned int i = 0; i< paiMesh->mNumVertices; i++){
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ?
                            &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v(sf::Vector3f(pPos->x, pPos->y, pPos->z),
			sf::Vector2f(pTexCoord->x,pTexCoord->y),
			sf::Vector3f(pNormal->x, pNormal->y, pNormal->z));
        Vertices.push_back(v);
    }

    for (unsigned int i = 0; i < paiMesh->mNumFaces; i++){
        const aiFace& Face = paiMesh->mFaces[i];
		for (int l = 0; l < Face.mNumIndices; l++) {
			Indices.push_back(Face.mIndices[l]);
		}
    }

    m_Entries[Index].Init(Vertices, Indices);
	std::vector<Vertex>().swap(Vertices);
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Извлекаем директорию из полного имени файла
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos){
        Dir = ".";
    }
    else if (SlashIndex == 0){
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool Ret = true;

    // Инициализируем материал
    for (unsigned int i = 0; i< pScene->mNumMaterials; i++){
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        m_Textures[i] = NULL;
    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path,
                                NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS){
                std::string FullPath = Dir + "/" + Path.data;
                m_Textures[i] = new Textur(FullPath.c_str());
            }
       }
        // Загружаем белую текстуру если модель не имеет собственной
   
    }

    return Ret;
}

void Mesh::Draw()
{

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0; i < m_Entries.size(); i++){
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]){
				glDisable(GL_CULL_FACE);
				m_Textures[MaterialIndex]->Bind();
				m_shader->Bind();
				m_shader->Update(m_transform, *m_camera);
				glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);

				glFrontFace(GL_BACK);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
        }

	
    }

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

void Mesh::SetShader(BasicShader & shader)
{
	m_shader = &shader;

}

void Mesh::AtachCamera(Camera & camera)
{
	m_camera = &camera;
}

void Mesh::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_transform.SetPos(glm::vec3(x, y, z));
}

sf::Vector3f Mesh::GetPosition()
{
	return sf::Vector3f(m_transform.GetPos().x, m_transform.GetPos().x, m_transform.GetPos().z);
}

void Mesh::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
	m_transform.SetRotate(glm::vec3(x, y, z));
}

sf::Vector3f Mesh::GetRotation()
{
	return sf::Vector3f(m_transform.GetRotate().x, m_transform.GetRotate().y, m_transform.GetRotate().z);
}

void Mesh::SetScale(GLfloat size)
{
	m_transform.SetScale(glm::vec3(size, size, size));
}

GLfloat Mesh::GetScale()
{
	return GLfloat(m_transform.GetScale().x);
}

void Mesh::SetTransform(Transform & transform)
{
}

