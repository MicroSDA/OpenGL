#ifndef MESH_H
#define MESH_H

#include <ASSIMP\Importer.hpp>      // C++ importer interface
#include <ASSIMP\scene.h>           // Output data structure
#include <ASSIMP\postprocess.h>     // Post processing flags
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include "Textur.h"
#include "BasicShader.h"
#include "Camera.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define INVALID_OGL_VALUE 0xFFFFFFFF

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

namespace ml {

	struct Vector3f
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;

	};

	struct Vector2f
	{
		GLfloat x;
		GLfloat y;
	};
};
struct Vertex
{
    sf::Vector3f m_pos;
	sf::Vector2f m_tex;
	sf::Vector3f m_normal;

    Vertex() {}

    Vertex(const sf::Vector3f& pos, const sf::Vector2f& tex, const sf::Vector3f& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};

struct VERTEX
{
	std::vector<sf::Vector3f> Position;
	std::vector<sf::Vector3f> Normal;
	std::vector<sf::Vector2f> TextureCoord;
	std::vector<unsigned int> Index;
};

class Mesh 
{
    public:
		Mesh(){};
        ~Mesh(){
            Clear();
        };
        bool LoadMesh(const std::string& Filename);
        void Draw();
		void SetShader(BasicShader &shader);
		void AtachCamera(Camera &camera);

		void SetPosition(GLfloat x, GLfloat y, GLfloat z);
		sf::Vector3f GetPosition();

		void SetRotation(GLfloat x, GLfloat y, GLfloat z);
		sf::Vector3f GetRotation();

		void SetScale(GLfloat size);
		GLfloat GetScale();
		void SetTransform(Transform &transform);
    private:
        bool InitFromScene(const aiScene* pScene, const std::string& Filename);
        void InitMesh(unsigned int Index, const aiMesh* paiMesh);
        bool InitMaterials(const aiScene* pScene, const std::string& Filename);
        void Clear();

        #define INVALID_MATERIAL 0xFFFFFFFF

        struct MeshEntry{
            MeshEntry();
            ~MeshEntry();

            bool Init(const std::vector<Vertex>& Vertices,
                      const std::vector<unsigned int>& Indices);
			void Init_test(const std::vector<Vertex>& Vertices);

            GLuint VB;
            GLuint IB;

			GLuint VBO[4];
			GLuint VOB;

            unsigned int NumIndices;
            unsigned int MaterialIndex;
        };

        std::vector<MeshEntry> m_Entries;
        std::vector<Textur*> m_Textures;
		Transform m_transform;
		BasicShader *m_shader;
		Camera *m_camera;
};

#endif /* MESH_H */

