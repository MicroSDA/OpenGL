#include "Landscape.h"

Landscape::Landscape()
{
}

Landscape::~Landscape()
{
}

bool Landscape::LoadHeightMap(const std::string & filename)
{



	/*
	ТОЛЬКО ПРОПОРЦИОНАЛНЫЕ КАРТИНКИ !!!!!!!
	*/
	float height=9;

	glm::vec3 p;
	glm::vec3 q;
	glm::vec3 n;
	glm::vec3 n_t;
	if (!m_image.loadFromFile(filename.c_str())) {
		return false;
	}
	else {
		int x_i = (m_image.getSize().x-1);//размер по x
		int z_i = (m_image.getSize().y-1);//размер по y
		//Проходимся по всему массиву и считываем яркость и позицию в массив
		for (int i_x = 0; i_x < x_i;  i_x++) {
			for (int i_z = 0; i_z < z_i ; i_z++) {

				//Координаты вершин 
				//Первый треугольник
				m_landscape_i.positions.push_back(glm::vec3(i_x, -(m_image.getPixel(i_x, i_z).r + m_image.getPixel(i_x, i_z).g + m_image.getPixel(i_x, i_z).b)/3/ height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -(m_image.getPixel(i_x+1, i_z).r + m_image.getPixel(i_x+1, i_z).g + m_image.getPixel(i_x+1, i_z).b) /3/ height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x, -(m_image.getPixel(i_x, i_z + 1).r + m_image.getPixel(i_x, i_z + 1).g +m_image.getPixel(i_x, i_z + 1).b)/3/ height, i_z + 1));

				//Текстуры UV
				m_landscape_i.texCoords.push_back(glm::vec2(i_x , i_z));
				m_landscape_i.texCoords.push_back(glm::vec2(i_x+1, i_z));
				m_landscape_i.texCoords.push_back(glm::vec2(i_x, i_z+1));

				//Нормали

				p = glm::vec3(i_x + 1, -(m_image.getPixel(i_x+1, i_z).r + m_image.getPixel(i_x+1, i_z).g + m_image.getPixel(i_x+1, i_z).b) / 3 / height, i_z) - glm::vec3(i_x, -(m_image.getPixel(i_x, i_z).r + m_image.getPixel(i_x, i_z).g + m_image.getPixel(i_x, i_z).b) / 3 / height, i_z);
				q = glm::vec3(i_x, -(m_image.getPixel(i_x, i_z+1).r + m_image.getPixel(i_x, i_z+1).g + m_image.getPixel(i_x, i_z+1).b) / 3 / height, i_z + 1) - glm::vec3(i_x, -(m_image.getPixel(i_x, i_z).r + m_image.getPixel(i_x, i_z).g + m_image.getPixel(i_x, i_z).b) / 3 / height, i_z);
				n = glm::cross(p,q);
				n = glm::normalize(n);
				m_landscape_i.normals.push_back(n);
				m_landscape_i.normals.push_back(n);
				m_landscape_i.normals.push_back(n);
				
				//Второй треугольник
				m_landscape_i.positions.push_back(glm::vec3(i_x, -(m_image.getPixel(i_x, i_z + 1).r+m_image.getPixel(i_x, i_z + 1).g+ m_image.getPixel(i_x, i_z + 1).b) /3/ height, i_z + 1));
				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -(m_image.getPixel(i_x + 1, i_z).r+m_image.getPixel(i_x + 1, i_z).g+ m_image.getPixel(i_x + 1, i_z).b) /3/ height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -(m_image.getPixel(i_x + 1, i_z + 1).r+ m_image.getPixel(i_x + 1, i_z + 1).g+ m_image.getPixel(i_x + 1, i_z + 1).b) /3/ height, i_z + 1));
				//Текстуры UV
				m_landscape_i.texCoords.push_back(glm::vec2(i_x, i_z+1));
				m_landscape_i.texCoords.push_back(glm::vec2(i_x + 1, i_z));
				m_landscape_i.texCoords.push_back(glm::vec2(i_x+1, i_z + 1));
				
				//Нормали
				p = glm::vec3(i_x + 1, -(m_image.getPixel(i_x + 1, i_z).r+ m_image.getPixel(i_x + 1, i_z).g+ m_image.getPixel(i_x + 1, i_z).b) /3 / height, i_z) - glm::vec3(i_x, -(m_image.getPixel(i_x, i_z + 1).r+ m_image.getPixel(i_x, i_z + 1).g+ m_image.getPixel(i_x, i_z + 1).b) /3/ height, i_z + 1);
				q = glm::vec3(i_x + 1, -(m_image.getPixel(i_x + 1, i_z + 1).r+ m_image.getPixel(i_x + 1, i_z + 1).g+ m_image.getPixel(i_x + 1, i_z + 1).b)/ 3 / height, i_z + 1) - glm::vec3(i_x, -(m_image.getPixel(i_x, i_z + 1).r+ m_image.getPixel(i_x, i_z + 1).g+ m_image.getPixel(i_x, i_z + 1).b) /3 / height, i_z + 1);

				//std::cout <<"X::"<< p.x <<"::Y::"<< p.y <<"::Z::"<< p.z << std::endl;
				
				n = glm::cross(p, q);
				n = glm::normalize(n);
				m_landscape_i.normals.push_back(n);
				m_landscape_i.normals.push_back(n);
				m_landscape_i.normals.push_back(n);
				

			
				
			}
			
		}


		//Сглааживание
		glm::vec3 n_teamp;

for (int i = 0; i < m_landscape_i.normals.size()-11; i++) {

			
			n_teamp = (m_landscape_i.normals[i] + m_landscape_i.normals[i + 3] + m_landscape_i.normals[i + 6]+ m_landscape_i.normals[i + 9]);
			n_teamp = glm::vec3(n_teamp.x / 4, n_teamp.y / 4, n_teamp.z / 4);
			m_landscape_i.normals[i] = n_teamp;
			m_landscape_i.normals[i + 1] = n_teamp;
			m_landscape_i.normals[i + 2] = n_teamp;
			m_landscape_i.normals[i + 3] = n_teamp;
			m_landscape_i.normals[i + 4] = n_teamp;
			m_landscape_i.normals[i + 5] = n_teamp;
			m_landscape_i.normals[i + 6] = n_teamp;
			m_landscape_i.normals[i + 7] = n_teamp;
			m_landscape_i.normals[i + 8] = n_teamp;
			m_landscape_i.normals[i + 9] = n_teamp;
			m_landscape_i.normals[i + 10] = n_teamp;
			m_landscape_i.normals[i + 11] = n_teamp;
			i = i + 4;
		}


		/*for (int i = 0; i < m_landscape_i.normals.size() - 6; i++) {


			n_teamp = (m_landscape_i.normals[i] + m_landscape_i.normals[i + 3]);
			n_teamp = glm::vec3(n_teamp.x / 2, n_teamp.y / 2, n_teamp.z / 2);
			m_landscape_i.normals[i] = n_teamp;
			m_landscape_i.normals[i + 1] = n_teamp;
			m_landscape_i.normals[i + 2] = n_teamp;
			m_landscape_i.normals[i + 3] = n_teamp;
			m_landscape_i.normals[i + 4] = n_teamp;
			m_landscape_i.normals[i + 5] = n_teamp;
			
			i = i + 2;
		}*/

		std::cout << m_landscape_i.positions.size();
		num_vertex = m_landscape_i.positions.size();
		glGenVertexArrays(1, &m_vertexArrayObject);
		glBindVertexArray(m_vertexArrayObject);

		glGenBuffers(3, m_vertexArrayBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_landscape_i.positions[0]) * m_landscape_i.positions.size(), &m_landscape_i.positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_landscape_i.texCoords[0]) * m_landscape_i.texCoords.size(), &m_landscape_i.texCoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_landscape_i.normals[0]) * m_landscape_i.normals.size(), &m_landscape_i.normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, 0);

		glBindVertexArray(0);



		//Удаляем и высвобождаем память 
		m_landscape_i.normals.erase(m_landscape_i.normals.begin(), m_landscape_i.normals.end());
		std::vector<glm::vec3>(m_landscape_i.normals).swap(m_landscape_i.normals);

		m_landscape_i.positions.erase(m_landscape_i.positions.begin(), m_landscape_i.positions.end());
		std::vector<glm::vec3>(m_landscape_i.positions).swap(m_landscape_i.positions);

		m_landscape_i.texCoords.erase(m_landscape_i.texCoords.begin(), m_landscape_i.texCoords.end());
		std::vector<glm::vec2>(m_landscape_i.texCoords).swap(m_landscape_i.texCoords);
	}
	
}

void Landscape::Draw()
{
	
	
	texture.Bind();
	shader->Bind();
	shader->Update(transform, *camera);
	//glColor3f(0.8f, 0.8f, 0.8f);
	glBindVertexArray(m_vertexArrayObject);
	//glDrawElementsBaseVertex(GL_TRIANGLES, m_landscape_i.indices.size(), GL_UNSIGNED_INT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, num_vertex);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {

		texture.Unbind();
		glColor3f(0.8f, 0.8f, 0.8f);
		glDrawArrays(GL_LINES, 0, num_vertex);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {

		texture.Unbind();
		glColor3f(0.8f, 0.8f, 0.8f);
		glDrawArrays(GL_POINTS, 0, num_vertex);
	}
	
	

	glBindVertexArray(0);
	shader->UnBind();
	texture.Unbind();


	
}

void Landscape::AtachCamera(Camera & camera)
{
	this->camera = &camera;
}

void Landscape::loadTextureFromFile(const std::string & filename)
{
	texture.loadFromFile(filename);
}

void Landscape::SetShader(Shader & shader)
{
	this->shader = &shader;
}

void Landscape::SetScale(GLfloat x)
{
	transform.SetScale(glm::vec3(x, x, x));
}

void Landscape::SetRotaited(GLfloat x, GLfloat y, GLfloat z)
{
	transform.GetRotate().x = x;
	transform.GetRotate().y = y;
	transform.GetRotate().z = z;
}

void Landscape::LoadHeightMap_TEST(const std::string & filename)
{
	m_image.loadFromFile(filename.c_str());


	float height = 1;
	int x_i = (m_image.getSize().x-1);//размер по x
	int z_i = (m_image.getSize().y-1);//размер по y

	float teamp = 0;
	float teamp_2 = 0;
	for (int i_x = 0; i_x < x_i; i_x++) {
		for (int i_z = 0; i_z < z_i; i_z++) {

			if (i_x== 0 && i_z!=0 && i_z!= 2) {
		
				m_landscape_i.positions.push_back(glm::vec3(i_x, -m_image.getPixel(i_x, i_z).r / height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -m_image.getPixel(i_x + 1, i_z).r / height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x, -m_image.getPixel(i_x, i_z + 1).r / height, i_z + 1));

				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -m_image.getPixel(i_x + 1, i_z + 1).r / height, i_z + 1));
				m_landscape_i.indices.push_back(0);
				m_landscape_i.indices.push_back(1);
				m_landscape_i.indices.push_back(2);

				m_landscape_i.indices.push_back(2);
				m_landscape_i.indices.push_back(1);
				m_landscape_i.indices.push_back(3);

				teamp =1;
				
			}

			if (i_x != 0 && i_z != 0&& i_z!=2) {

				teamp = teamp + 1;

				m_landscape_i.positions.push_back(glm::vec3(i_x, -m_image.getPixel(i_x, i_z).r / height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -m_image.getPixel(i_x + 1, i_z).r / height, i_z));
				m_landscape_i.positions.push_back(glm::vec3(i_x, -m_image.getPixel(i_x, i_z + 1).r / height, i_z + 1));

				m_landscape_i.positions.push_back(glm::vec3(i_x + 1, -m_image.getPixel(i_x + 1, i_z + 1).r / height, i_z + 1));

				m_landscape_i.indices.push_back(teamp + 1);
				m_landscape_i.indices.push_back(teamp + 2);
				m_landscape_i.indices.push_back(teamp + 3);

				
				teamp = teamp + 1;
				m_landscape_i.indices.push_back(teamp + 3);
				m_landscape_i.indices.push_back(teamp + 2);
				m_landscape_i.indices.push_back(teamp + 4);			
			}


			

			if (i_x == 0 && i_z >= 2) {
				
				
			}

			if (i_x != 0 && i_z >= 2) {
			

			}

							
		}

	}

	/*for (int i = 0; i < m_landscape_i.indices.size(); i++) {
		std::cout << m_landscape_i.indices[i] << std::endl;
	}*/

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);


	glGenBuffers(4, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_landscape_i.positions[0]) * m_landscape_i.positions.size(), &m_landscape_i.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/*glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_landscape_i.texCoords[0]) * m_landscape_i.texCoords.size(), &m_landscape_i.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_landscape_i.normals[0]) * m_landscape_i.normals.size(), &m_landscape_i.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, 0);*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_landscape_i.indices[0]) * m_landscape_i.indices.size(), &m_landscape_i.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}
