#include "stdafx.h"
#include "CubeMesh.h"



namespace Merlin{

	GLfloat CubeMesh::cubeTriangles[] = {
		1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0,       // Front
		-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,       // Front
		1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0,        // Right
		1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,      // Right
		-1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0,     // Back
		1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0,   // Back
		-1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0,    // Left
		-1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0,    // Left
		-1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,       // Top
		1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0,       // Top
		1.0, -1.0, -1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0,     // Bottom
		-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0    // Bottom
	}; 


	GLfloat CubeMesh::cubeNormals[] = {
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
		0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
		-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
		0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0 
	};

	CubeMesh::CubeMesh(){}

	CubeMesh::~CubeMesh(){ }

	void CubeMesh::Initialise(){
		//		Populate the vectors with mesh data
		// Not strictly necessary but maintains common method for all meshes to process data
		vertices.insert(vertices.begin(), &cubeTriangles[0], &cubeTriangles[108]);
		normals.insert(normals.begin(), &cubeNormals[0], &cubeNormals[108]);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		// Create vertex buffer 
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (vertices.size() + normals.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size() , sizeof(GLfloat) * normals.size(), &normals[0]);

		// Specifies the location of the data within the buffer. 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)(sizeof(GLfloat) * (vertices.size())));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		numberVertices = vertices.size() / 3;
		vertices.clear();
		normals.clear();
	}

	void CubeMesh::Render(){
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, numberVertices);
		// Unbind the vertex array
		glBindVertexArray(0);
	}
}