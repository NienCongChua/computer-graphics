﻿#pragma region Milk Tea Shop
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
// Front face (RED)
{ { 0.5f,  0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 1 } },
{ {-0.5f,  0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 1 } },
{ {-0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 1 } },
{ {-0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 1 } },
{ { 0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 1 } },
{ { 0.5f,  0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 1 } },

// Back face (GREEN)
{ { 0.5f,  0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, -1, 1 } },
{ {-0.5f,  0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, -1, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, -1, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, -1, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, -1, 1 } },
{ { 0.5f,  0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, -1, 1 } },

// Right face (BLUE)
{ { 0.5f,  0.5f,  0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f },{ 1, 0, 0, 1 } },
{ { 0.5f,  0.5f, -0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f },{ 1, 0, 0, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f },{ 1, 0, 0, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f },{ 1, 0, 0, 1 } },
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f },{ 1, 0, 0, 1 } },
{ { 0.5f,  0.5f,  0.5f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f },{ 1, 0, 0, 1 } },

// Left face (YELLOW) 
{ {-0.5f,  0.5f,  0.5f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 1 } },
{ {-0.5f,  0.5f, -0.5f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 1 } },
{ {-0.5f, -0.5f,  0.5f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 1 } },
{ {-0.5f,  0.5f,  0.5f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f },{ -1, 0, 0, 1 } },

// Top face (MAGENTA)
{ { 0.5f,  0.5f,  0.5f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 1, 0, 1 } },
{ { 0.5f,  0.5f, -0.5f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 1, 0, 1 } },
{ {-0.5f,  0.5f, -0.5f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 1, 0, 1 } },
{ {-0.5f,  0.5f, -0.5f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 1, 0, 1 } },
{ {-0.5f,  0.5f,  0.5f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 1, 0, 1 } },
{ { 0.5f,  0.5f,  0.5f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 1, 0, 1 } },

// Bottom face (CYAN)
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 1 } },
{ {-0.5f, -0.5f,  0.5f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 1 } },
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0, -1, 0, 1 } },

// Bottom - face (Grey)
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0, -1, 0, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0, -1, 0, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0, -1, 0, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0, -1, 0, 1 } },
{ {-0.5f, -0.5f,  0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0, -1, 0, 1 } },
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 0, -1, 0, 1 } },

// Bottom face (White)
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 1, -1, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 1, -1, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 1, -1, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 1, -1, 1 } },
{ {-0.5f, -0.5f,  0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 1, -1, 1 } },
{ { 0.5f, -0.5f,  0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1, 1, -1, 1 } },

// Front face (White)
{ { 0.5f,  0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 1 } },
{ {-0.5f,  0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 1 } },
{ {-0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 1 } },
{ {-0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 1 } },
{ { 0.5f, -0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 1 } },
{ { 0.5f,  0.5f, 0.5f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 1 } },

// Back face (Nâu đỏ)
{ { 0.5f,  0.5f, -0.5f, 1.0f },{ 0.734f, 0.4375f, 0.4375f, 1.0f },{ 0, 0, -1, 1 } },
{ {-0.5f,  0.5f, -0.5f, 1.0f },{ 0.734f, 0.4375f, 0.4375f, 1.0f },{ 0, 0, -1, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.734f, 0.4375f, 0.4375f, 1.0f },{ 0, 0, -1, 1 } },
{ {-0.5f, -0.5f, -0.5f, 1.0f },{ 0.734f, 0.4375f, 0.4375f, 1.0f },{ 0, 0, -1, 1 } },
{ { 0.5f, -0.5f, -0.5f, 1.0f },{ 0.734f, 0.4375f, 0.4375f, 1.0f },{ 0, 0, -1, 1 } },
{ { 0.5f,  0.5f, -0.5f, 1.0f },{ 0.734f, 0.4375f, 0.4375f, 1.0f },{ 0, 0, -1, 1 } },
};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);

class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;


public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

int CurrentWidth = 700,		// Định nghĩa chiều rộng của cửa sổ hiển thị
CurrentHeight = 700;		// Định nghĩa chiều cao của cửa sổ hiển thị

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;


MatrixStack  mvstack;		// Định nghĩa ma trận mvstack

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float R[3] = { 10.0f, 0.0f, -2.0f };		// Định nghĩa các thông số eye của hàm lookat
// float T[3] = { 0.0f, 0.0f, 0.0f };			// Định nghĩa các thông số at của hàm lookat
// float Y[3] = { 0.0f, 1.0f, 0.0f };			// Định nghĩa các tham số up của hàm lookat
float U[3] = { 0.0f, 0.0f, 0.0f };			// Định nghĩa các tham số quay
float S = 0.1f;								// Định nghĩa tham số chiều to nhỏ 


bool
translated = false,
rotated = false,
scaled = false;

enum {
	// Các chi tiết có thể chuyển động được liệt kê ở đây (xoay, tịnh tiến và scale)
	_main,				// Định nghĩa chi tiết _main
	_cuaNK,				// Định nghĩa chi tiết cửa nhà kho
	NumJointAngles,	
	Quit		
};

GLfloat
thetat[NumJointAngles] = {		// Hàm dùng tịnh tiến các chi tiết
	0.0,			// Giá trị ban đầu của chi tiết _main theo chức năng tịnh tiến 
	0.0

},

thetar[NumJointAngles] = {
	0.0,			// Giá trị ban đầu của chi tiết _main theo chức năng quay
	270.0
};

GLint angle = _main;	// Khởi tạo đối tượng chuyển động ban đầu

// ------------------------ Định nghĩa các hàm để vẽ ------------------------//
#pragma region Các hàm vẽ các đối tượng 
namespace Wall		// Định nghĩa namespace Wall chứa các hàm vẽ các bức tường
{
	void wall_1() 
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = scale(vec3(120.0f, 0.0f, 120.0f));	 // Kích thước sàn nhà

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan

		glDrawArrays(GL_TRIANGLES, 36, 6); // Another grey
		model_mat_cpp = mvstack.pop();
	}

	void wall_2() 
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = rotate_x(90) * rotate_z(90) *
			scale(vec3(120.0f, 0.0f, 50.0f));	 // Kích thước tường

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan
		//glDrawArrays(GL_TRIANGLES, 36, 6); // Another Grey

		model_mat_cpp = mvstack.pop();
	}

	void wall_3()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = rotate_x(90) * rotate_z(90) *
			scale(vec3(120.0f, 0.0f, 50.0f));	 // Kích thước tường

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan
		//glDrawArrays(GL_TRIANGLES, 36, 6); // Another Grey

		model_mat_cpp = mvstack.pop();
	}

	void wall_4()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = scale(vec3(120.0f, 0.0f, 120.0f)) *   // Kích thước sàn nhà
			rotate_y(90) * rotate_z(90);	 

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan
		//glDrawArrays(GL_TRIANGLES, 36, 6); // Another - Grey

		model_mat_cpp = mvstack.pop();
	}

	void wall_5()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = rotate_x(90) * rotate_z(90) *
			scale(vec3(50.0f, 0.5f, 50.0f));	 // Kích thước tường

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan
		//glDrawArrays(GL_TRIANGLES, 36, 6); // Another Grey

		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void wall_6()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = 
			scale(vec3(0.5f, 10.0f, 60.0f));	 // Kích thước tường

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan
		//glDrawArrays(GL_TRIANGLES, 36, 6); // Another Grey

		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void wall_7() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = 
			scale(vec3(0.5f, 40.0f, 35.0f));

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan

		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void wall_8() 
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance =
			scale(vec3(1.0f, 1.0f, 1.0f));

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan

		glDrawArrays(GL_TRIANGLES, 12, 36);

		model_mat_cpp = mvstack.pop();
	}
}

namespace Box		// Định nghĩa namespace Box vẽ 1 hình hộp
{
	void box() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = 
			scale(vec3(5.0f, 5.0f, 5.0f));

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);
		
		glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan

		model_mat_cpp = mvstack.pop();
	}
}

namespace Cua
{
	void cua_1() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = 
			scale(vec3(0.5f, 40.0f, 25.0f));

		mat4 model_box = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_box.m);

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Front - Red
		//glDrawArrays(GL_TRIANGLES, 6, 6); // Back - Green
		//glDrawArrays(GL_TRIANGLES, 12, 6); // Right - Blue
		//glDrawArrays(GL_TRIANGLES, 18, 6); // Left - Yellow
		//glDrawArrays(GL_TRIANGLES, 24, 6); // Top - Magenta
		//glDrawArrays(GL_TRIANGLES, 30, 6); // Bottom - Cyan

		glDrawArrays(GL_TRIANGLES, 12, 48);

		model_mat_cpp = mvstack.pop();
	}
}

#pragma endregion
// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------

void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);

	vec3	eye(R[0], R[1], R[2]),
		at(0, 0, 0),
		up(0, 1, 0);

	view_mat_cpp = lookat(eye, at, up) * scale(vec3(S, S, S)) * rotate_x(U[0]) * rotate_y(U[1]) * rotate_z(U[2]);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;

	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#pragma region Gọi các hàm vẽ
	// Các hàm vẽ sẽ được gọi trong region này
	// Box::box();

	// Vẽ sàn nhà
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, -15, 0));
	Wall::wall_1();
	model_mat_cpp = mvstack.pop();

	// Vẽ bức tường
	mvstack.push(model_mat_cpp);		// Vẽ bức tường 1 
	model_mat_cpp = model_mat_cpp * 
		translate(vec3(-60, 10, 0));	// Vẽ bức tường 1
	Wall::wall_2();						// Vẽ bức tường 1
	model_mat_cpp = mvstack.pop();		// Vẽ bức tường 1

	mvstack.push(model_mat_cpp);		// Vẽ bức tường 2
	model_mat_cpp = model_mat_cpp *
		rotate_y(90) * 
		translate(vec3(60, 10, 0));		// Vẽ bức tường 2
	Wall::wall_3();						// Vẽ bức tường 2
	model_mat_cpp = mvstack.pop();		// Vẽ bức tường 2

	mvstack.push(model_mat_cpp);		// Vẽ bức tường 3
	model_mat_cpp = model_mat_cpp *
		rotate_y(90) *
		translate(vec3(-60, 10, 0));	// Vẽ bức tường 3
	Wall::wall_3();						// Vẽ bức tường 3
	model_mat_cpp = mvstack.pop();		// Vẽ bức tường 3

	// Vẽ trần nhà
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(0, 35, 0));
	Wall::wall_4();
	model_mat_cpp = mvstack.pop();

	// Vẽ tường trong
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		rotate_y(90) *
		translate(vec3(0, 10, -35));
	Wall::wall_5();
	model_mat_cpp = mvstack.pop();

	// Vẽ phần trên của nhà bên trong
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-10, 30, 30));
	Wall::wall_6();
	model_mat_cpp = mvstack.pop();

	// Vẽ phần bên của nhà bên trong
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-10, 5, 17.5));
	Wall::wall_7();
	model_mat_cpp = mvstack.pop();

	// Vẽ cửa 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-10, 5, 47.5)) *
		translate(vec3(0, 0, 12.5)) *
		rotate_y(thetar[_cuaNK]) *
		translate(vec3(0, 0, 12.5));
	Cua::cua_1();
	model_mat_cpp = mvstack.pop();

	// Ve Khong gian 1
	Wall::wall_8();


#pragma endregion
	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
void IdleFunc(void)  // Hàm cho các thông số tự chạy
{
	glutPostRedisplay();		// Gọi lại hàm
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)  // Hàm định nghĩa các nút chức năng
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case '=':
		S += 0.05;
		if (S > 20) {
			S -= 0.05;
		}
		break;
	case'-':
		S -= 0.05;
		if (S < 0) {
			S += 0.05;
		}
		break;
	case 'w':
		R[0] += 0.5;
		break;
	case 's':
		R[0] -= 0.5;
		break;
	case 'a':
		R[1] += 0.5;
		break;
	case 'd':
		R[1] -= 0.5;
		break;
	case 'q':
		R[2] += 0.5;
		break;
	case 'e':
		R[2] -= 0.5;
		break;
	}
}
// ----------------------------------------

void SpecialFunc(int key, int x, int y)			// Hàm xử lý phím đặc biệt
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_ALT_R:;
		break;
	case GLUT_KEY_CTRL_R:
		break;
	case GLUT_KEY_INSERT:
		U[0] += 10;
		if (U[0] > 360) {
			U[0] -= 360;
		}
		break;
	case GLUT_KEY_DELETE:
		U[0] -= 10;
		if (U[0] < 0) {
			U[0] += 360;
		}
		break;
	case GLUT_KEY_PAGE_UP:
		U[2] += 10;
		if (U[2] > 360) {
			U[2] -= 360;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		U[2] -= 10;
		if (U[2] < 0) {
			U[2] += 360;
		}
		break;
	case GLUT_KEY_HOME:
		U[1] += 10;
		if (U[1] > 360) {
			U[1] -= 360;
		}
		break;
	case GLUT_KEY_END:
		U[1] -= 10;
		if (U[1] < 0) {
			U[1] += 360;
		}
		break;
	case GLUT_KEY_F1:
		thetar[_cuaNK] -= 5;
		if (thetar[_cuaNK] < 180) {
			thetar[_cuaNK] += 5;
		}
		break;
	case GLUT_KEY_F2:
		thetar[_cuaNK] += 5;
		if (thetar[_cuaNK] > 270) {
			thetar[_cuaNK] -= 5;
		}
		break;
	}
}

void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		return;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		return;
	}

	glutPostRedisplay();
}

void menu(int option)
{
	if (option == Quit) {
		exit(EXIT_SUCCESS);
	}

	angle = option;
}

// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Blinn");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	// tạo menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Main", _main);
	glutAddMenuEntry("quit", Quit);

	// kích hoạt menu bằng nhấn nút giữa chuột
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();
	return 0;
}
#pragma endregion