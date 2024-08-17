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
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f },{ 0, 0, 1, 1 } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f },{ 0, 0, 1, 1 } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f },{ 0, 0, 1, 1 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f },{ 0, 0, 1, 1 } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f },{ 0, 0, 1, 1 } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f },{ 0, 0, 1, 1 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f },{ 1, 0, 0, 1 } },
	{ { 0.5f,	-0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f },{ 1, 0, 0, 1 } },
	{ { 0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f },{ 1, 0, 0, 1 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f },{ 1, 0, 0, 1 } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f },{ 1, 0, 0, 1 } },
	{ { 0.5f,	 0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f },{ 1, 0, 0, 1 } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f },{ 0, 1, 0, 1 } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f },{ 0, 1, 0, 1 } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f },{ 0, 1, 0, 1 } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f },{ 0, 1, 0, 1 } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f },{ 0, 1, 0, 1 } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f },{ 0, 1, 0, 1 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } }
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

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;


MatrixStack  mvstack;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };
float R[3] = { 40.0f, 20.0f, 12.0f };
float T[3] = { 0.0f, 0.0f, 0.0f };
float Y[3] = { 0.0f, 1.0f, 0.0f };
float U[] = { 0.0f, 0.0f, 0.0f };
float Alpha = 0.0f;
bool _switch = true;


bool
translated = false,
rotated = false,
scaled = false;

enum {
	Ban,
	NganBan,//1
	ArmScr1,
	ArmScr2,		//2
	ArmScr3,
	Cua1,			//3
	NumJointAngles,	//11
	Quit			//12
};

GLfloat
theta[NumJointAngles] = {
	0.0,    // Torso
	0.0,    // Head1
	90.0,    // Head2
	50.0,
	0.0,
	45.0
},

thetaArmScreen[NumJointAngles] = {
	30.0,    // Torso
	50.0,    // Head1
	90.0,    // Head2
	10.0,
	-10.0
};

// khởi tạo đối tượng quay
GLint angle = NganBan;

// ------------------------------------------
void san()
{
	mat4 instance = identity_mat4();
	instance = scale(vec3(2.0f, 0.01f, 2.0f));

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void doi_dien()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0f, 0.7f, -1.0f)) * scale(vec3(2.0f, 1.4f, 0.01f));
	mat4 model_torso = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ben_trai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-1.0f, 0.7f, 0.0f)) * scale(vec3(0.01f, 1.4f, 2.0f));
	mat4 model_torso = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


#pragma region Tuong nha
namespace Tuong {
	void trannha() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 25, 0)) *
			scale(vec3(50.0f, 0.01f, 50.0f));

		mat4 model_left_upper_arm = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	// ------------------------------------------

	// ------------------------------------------
	// 
		// mat san
	void matsan() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance =
			scale(vec3(50.0f, 0.01f, 50.0f)) * rotate_z(90) * rotate_y(90) * rotate_x(180);

		mat4 model_left_upper_arm = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void tuongdung() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 25, 0)) *
			scale(vec3(50.0f, 25.0f, 0.01f));

		mat4 model_left_upper_arm = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
}
#pragma endregion

#pragma region Ban Lam viec
namespace BanLamViec {
	void matban()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0.0, 8.0, 2.0)) *
			scale(vec3(10, 0.1, 5)); //6, 8, 4

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void chanban()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance =
			translate(vec3(0, 4.0, 0)) *
			scale(vec3(0.5f, 8.0f, 0.5f));

		mat4 model_left_upper_arm = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}



	void nganban()
	{
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 6, 2)) *
			scale(vec3(8.5, 0.1, 5)); //6, 8, 4

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
}
#pragma endregion

#pragma region Ghe ngoi
namespace GheNgoi {
	void changhedai() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(1.5, 4, 8)) *
			scale(vec3(0.25f, 8.0f, 0.25f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void tuaghe() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 6.75, 7.75)) *
			scale(vec3(3.0f, 2.5f, 0.25f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void changhengan() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(1.5, 2, 5)) *
			scale(vec3(0.25f, 3.75f, 0.25f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void chongoi() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 4, 6.5)) *
			scale(vec3(3.5f, 0.25f, 3.5f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
}
#pragma endregion

#pragma region May tinh va Arm man hinh, chuot, ban pham
namespace MayTinh {
	void casemaytinh() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(-2, 8.25, 0.25)) *
			scale(vec3(1.0f, 0.5f, 1.0f)) *
			rotate_z(90);

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}


	void armScreen1() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.3f, 1.0f, 0.3f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void armScreen2() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.3f, 4.0f, 0.3f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void armScreen3() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.5f, 0.3f, 0.3f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void screen() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.3f, 5.0f, 3.5f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	// Vien man hinh
	void _screen() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.1f, 4.8f, 3.3f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void keyboard() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(4.0f, 0.1f, 2.0f)) * translate(vec3(0, 81, 1.2)) * rotate_x(90) * rotate_z(90);

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	// Mouse
	void mouse() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.5f, 0.5f, 0.8f)) * translate(vec3(-7, 16.5, 3.5)) * rotate_x(90) * rotate_z(90);

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();

	}
}
#pragma endregion

#pragma region Quat tran
namespace QuatTran {
	void dequat() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(1.0f, 0.3f, 1.0f)) * rotate_x(90) * rotate_z(90);

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void thanquat() {
		mvstack.push(model_mat_cpp);

		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(0.5f, 3.0f, 0.5f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void bauquat() {
		mvstack.push(model_mat_cpp);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(2.0f, 0.3f, 2.0f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void canhquat() {
		mvstack.push(model_mat_cpp);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(1.0f, 0.25f, 6.0f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void _canhquat() {
		mvstack.push(model_mat_cpp);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0, 0)) *
			scale(vec3(6.0f, 0.25f, 1.0f));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

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
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	vec3	eye(R[0], R[1], R[2]),
		at(T[0], T[1], T[2]),
		up(Y[0], Y[1], Y[2]);

	view_mat_cpp = lookat(eye, at, up) * rotate_x(theta[Ban] + U[0]) * rotate_y(theta[Ban] + U[1]) * rotate_z(theta[Ban] + U[2]);
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


	// San nha
	Tuong::matsan();

#pragma region Ve Ban Lam Viec
	// matban
	BanLamViec::matban();

	// Ngan ban
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(0.0f, 0.0f, theta[NganBan]));
	BanLamViec::nganban();
	model_mat_cpp = mvstack.pop();

	// Chan ban 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-4.5, 0, 0.0));
	BanLamViec::chanban();
	model_mat_cpp = mvstack.pop();

	// chan ban 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-4.5, 0, 4.0));
	BanLamViec::chanban();
	model_mat_cpp = mvstack.pop();

	// Chan ban 3
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(4.5, 0, 0.0));
	BanLamViec::chanban();
	model_mat_cpp = mvstack.pop();
	//// chan ban 4
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(4.5, 0, 4.0));
	BanLamViec::chanban();
	model_mat_cpp = mvstack.pop();

#pragma endregion

#pragma region Ve Ghe Ngoi
	// chan ghe dai 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 0));
	GheNgoi::changhedai();
	model_mat_cpp = mvstack.pop();

	// chan ghe dai 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-3, 0, 0));
	GheNgoi::changhedai();
	model_mat_cpp = mvstack.pop();

	// tua ghe
	GheNgoi::tuaghe();

	// chan ghe ngan 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 0));
	GheNgoi::changhengan();
	model_mat_cpp = mvstack.pop();

	// chan ghe ngan 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-3, 0, 0));
	GheNgoi::changhengan();
	model_mat_cpp = mvstack.pop();

	// cho ngoi (tren ghe);
	GheNgoi::chongoi();
#pragma endregion

#pragma region Ve May Tinh
	// Case may tinh
	MayTinh::casemaytinh();


	// Arm man hinh duoi
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 8.25, 0.15)) *
		rotate_y(thetaArmScreen[ArmScr1]);// *
		// translate(vec3(-5, 8.25, 0.25));
	MayTinh::armScreen1();
	model_mat_cpp = mvstack.pop();

	// Arm man hinh tren
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 8.25, 0.15)) *
		translate(vec3(0, 2.5, 0)) * rotate_y(thetaArmScreen[ArmScr1] + 180) *
		translate(vec3(0, -2, 0)) *
		rotate_x(thetaArmScreen[ArmScr2] + 90) *
		translate(vec3(0, -2, 0));
	/*rotate_y(thetaArmScreen[ArmScr1]) *
	translate(vec3(-0.15, 2, -0.15)) *
	rotate_x(thetaArmScreen[ArmScr2]) *
	translate(vec3(-0.15, 2, -0.15));*/
	MayTinh::armScreen2();
	model_mat_cpp = mvstack.pop();

	// Arm man hinh truoc
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 8.25, 0.15)) *
		translate(vec3(0, 2.5, 0)) * rotate_y(thetaArmScreen[ArmScr1] + 180) *
		translate(vec3(0, -2, 0)) *
		rotate_x(thetaArmScreen[ArmScr2] + 90) *
		translate(vec3(0, -2, 0)) *
		translate(vec3(0.3, -1.85, 0)) *
		rotate_x(thetaArmScreen[ArmScr3]);
	MayTinh::armScreen3();
	model_mat_cpp = mvstack.pop();

	// Man hinh
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 8.25, 0.15)) *
		translate(vec3(0, 2.5, 0)) * rotate_y(thetaArmScreen[ArmScr1] + 180) *
		translate(vec3(0, -2, 0)) *
		rotate_x(thetaArmScreen[ArmScr2] + 90) *
		translate(vec3(0, -2, 0)) *
		translate(vec3(0.3, -1.85, 0)) *
		rotate_x(thetaArmScreen[ArmScr3]) *
		translate(vec3(0.25, 0, -1));
	MayTinh::screen();
	model_mat_cpp = mvstack.pop();

	// Vien man hinh
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 8.25, 0.15)) *
		translate(vec3(0, 2.5, 0)) * rotate_y(thetaArmScreen[ArmScr1] + 180) *
		translate(vec3(0, -2, 0)) *
		rotate_x(thetaArmScreen[ArmScr2] + 90) *
		translate(vec3(0, -2, 0)) *
		translate(vec3(0.3, -1.85, 0)) *
		rotate_x(thetaArmScreen[ArmScr3]) *
		translate(vec3(0.25, 0, -1)) * rotate_y(180) *
		translate(vec3(-0.11, 0, 0));
	MayTinh::_screen();
	model_mat_cpp = mvstack.pop();

	// Ban phim
	MayTinh::keyboard();

	// Chuot
	MayTinh::mouse();
#pragma endregion

#pragma region Cac buc tuong
	// Tran nha
	Tuong::trannha();

	// Tuong ben trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, -12.5, -25)) *
		rotate_y(180);
	Tuong::tuongdung();
	model_mat_cpp = mvstack.pop();

	// Tuong ben phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, -12.5, 25));
	Tuong::tuongdung();
	model_mat_cpp = mvstack.pop();

	// Tuong dang sau
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * rotate_y(90) * translate(vec3(0, -12.5, -25));
	Tuong::tuongdung();
	model_mat_cpp = mvstack.pop();

#pragma endregion

#pragma region Ve Quat Tran
	// De quat
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 24.8, 5));
	QuatTran::dequat();
	model_mat_cpp = mvstack.pop();

	// Than quat
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 23, 5));
	QuatTran::thanquat();
	model_mat_cpp = mvstack.pop();

	// Bau quat
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 21.6, 5)) *
		rotate_y(Alpha);
	QuatTran::bauquat();
	model_mat_cpp = mvstack.pop();

	// Canh quat 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 21.6, 5)) *
		rotate_y(Alpha) * translate(vec3(0, 0, 2));
	QuatTran::canhquat();
	model_mat_cpp = mvstack.pop();

	// Canh quat 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 21.6, 5)) *
		rotate_y(Alpha) * translate(vec3(0, 0, -2));
	QuatTran::canhquat();
	model_mat_cpp = mvstack.pop();

	// Canh quat 3
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 21.6, 5)) *
		rotate_y(Alpha) * translate(vec3(-2, 0, 0));
	QuatTran::_canhquat();
	model_mat_cpp = mvstack.pop();

	// Canh quat 4
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 21.6, 5)) *
		rotate_y(Alpha) * translate(vec3(2, 0, 0));
	QuatTran::_canhquat();
	model_mat_cpp = mvstack.pop();
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
void IdleFunc(void)
{
	if (_switch) {
		Alpha += 1.0f;
		if (Alpha > 360.0f) {
			Alpha -= 360.0f;
		}
		glutPostRedisplay();
	}
	else {
		glutPostRedisplay();
	}

}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case 'l':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'L':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'k':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'K':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'j':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'J':
		r[2] += 10.0f;
		rotated = true;
		break;

	case ',':
	case '.':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '<':
	case '>':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'p':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'o':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'I':
		t[1] += 0.05f;
		translated = true;
		break;
	case 'u':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'y':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 't':
		t[2] += 0.05f;
		translated = true;
		break;
	case 'b':
		U[0] += 10.0f; break;
	case 'B':
		U[0] -= 10.0f; break;
	case 'n':
		U[1] += 10.0f; break;
	case 'N':
		U[1] -= 10.0f; break;
	case 'm':
		U[2] += 10.0f; break;
	case 'M':
		U[2] -= 10.0f; break;
	case '-':
		theta[angle] -= 0.1;
		if (theta[angle] < 0.0) { theta[angle] += 0.1; } glutPostRedisplay(); break;
	case '=':
		theta[angle] += 0.1;
		if (theta[angle] > 2.5) { theta[angle] -= 0.1; } glutPostRedisplay(); break;
	case 'z':
		R[0] += 0.1f; break;
	case 'Z':
		R[0] -= 0.1f; break;
	case 'x':
		R[1] += 0.1f; break;
	case 'X':
		R[1] -= 0.1f; break;
	case 'c':
		R[2] += 0.1f; break;
	case 'C':
		R[2] -= 0.1f; break;
	case 'a':
		T[0] += 0.1f; break;
	case 'A':
		T[0] -= 0.1f; break;
	case 's':
		T[1] += 0.1f; break;
	case 'S':
		T[1] -= 0.1f; break;
	case 'd':
		T[2] += 0.1f; break;
	case 'D':
		T[2] -= 0.1f; break;
	case 'q':
		Y[0] += 0.1f; break;
	case 'Q':
		Y[0] -= 0.1f; break;
	case 'w':
		Y[1] += 0.1f; break;
	case 'W':
		Y[1] -= 0.1f; break;
	case 'e':
		Y[2] += 0.1f; break;
	case 'E':
		Y[2] -= 0.1f; break;
	case '_':
		thetaArmScreen[angle] += 8;
		if (thetaArmScreen[angle] > 85) { thetaArmScreen[angle] -= 8; }; break;
	case '+':
		thetaArmScreen[angle] -= 8;
		if (thetaArmScreen[angle] < 0) { thetaArmScreen[angle] += 8; }; break;
	case '0':
		if (_switch) {
			_switch = false;
			break;
		}
		else {
			_switch = true;
			break;
		}
	}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
	}
}

void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		thetaArmScreen[angle] += 10;
		if (thetaArmScreen[angle] > 90) { thetaArmScreen[angle] -= 10; }
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		thetaArmScreen[angle] -= 10;
		if (thetaArmScreen[angle] < -90) { thetaArmScreen[angle] += 10; }
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
	glutAddMenuEntry("Ngan Ban", NganBan);
	glutAddMenuEntry("Arm Low Screen", ArmScr1);
	glutAddMenuEntry("Arm High Screen", ArmScr2);
	glutAddMenuEntry("Arm Screen in front of", ArmScr3);
	glutAddMenuEntry("quit", Quit);

	// kích hoạt menu bằng nhấn nút giữa chuột
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();
	return 0;
}
