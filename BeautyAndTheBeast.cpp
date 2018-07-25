#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

float temp = 0.0;

///// stand animation variables /////
bool standAnimationSwitch = false;
float standTransX = 0.0;
float standTransY = 0.0;
float standTransZ = 0.0;
float standTransXNew = 0.0;
float standTransYNew = 0.0;
float standTransZNew = 0.0;
float standRotX = 0.0;
float standRotY = 0.0;
float standRotZ = 0.0;
///// teapot animation variables /////
bool teapotAnimationSwitch = false;
float t = 0.0;
float teapotTransX = 0.0;
float teapotTransY = 0.0;
float teapotTransZ = 0.0;
float teapotTransXNew = 0.0;
float teapotTransYNew = 0.0;
float teapotTransZNew = 0.0;
float teapotRotX = 0.0;
float teapotRotY = 0.0;
float teapotRotZ = 0.0;
///// featherdust animation variables /////
bool featherdustAnimationSwitch = false;
float featherdustT = 0.0;
float featherdustTNew = 0.0;
float featherdustTransX = 0.0;
float featherdustTransY = 0.0;
float featherdustTransZ = 0.0;
float featherdustTransXNew = 0.0;
float featherdustTransYNew = 0.0;
float featherdustTransZNew = 0.0;
float featherdustRotX = 0.0;
float featherdustRotY = 0.0;
float featherdustRotZ = 0.0;
///// cup animation variables /////
bool cupAnimationSwitch = false;
float cupRotZ = 0.0;
float cupX = 0.0;
float newCupX = 0.0;
float cupY = 0.0;
float newCupY = 0.0;
///// candle animation variables /////
bool candleAnimationSwitch = false;
float candleRotZ = 0.0;
float candleX = 0.0;
float newCandleX = 0.0;
float candleY = 0.0;
float newCandleY = 0.0;
float centerCandleY = 0.0;
float centerCandleYNew = 0.0;
float centerCandleRotZ = 0.0;
float lowerCenterCandleY = 0.0;
float lowerCenterCandleYNew = 0.0;
float lowerCenterCandleRotY = 0.0;
///// candle animation2 variables /////
bool candleAnimationSwitch2 = false;
float candleT2 = 0.0;
float candleTransX2 = 0.0;
float candleTransZ2 = 0.0;
float candleScale2 = 1.0;
float candleScale2New = 1.0;
float candleTransX2New = 0.0;
float candleTransZ2New = 0.0;
float candleTransX2New2 = 0.0;
float candleTransZ2New2 = 0.0;
///// chandelier animation variables /////
bool chandelierAnimationSwitch = false;
float chandelierRotY = 0.0;
float chandelierTransY = 0.0;
float chandelierTransYNew = 0.0;
///// chandelier animation2 variables /////
bool chandelierAnimationSwitch2 = false;
float chandelierT2 = 0.0;
float chandelierTransX2 = 0.0;
float chandelierTransY2 = 0.0;
float chandelierScale2 = 1.0;
float chandelierScale2New = 1.0;
///// global animation variables /////
bool globalAnimationSwitch = false;
bool frontView = true;
bool topView = false;
bool sideView = false;
///// camera animation variables /////
bool cameraAnimationSwitch = false;
float d = 0.05;
int counter = 3;


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.2f, float eyeY = 1.2f, float eyeZ = 1.2f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void reset() {
		eye = Vector3f(1.2f, 1.2f, 1.2f);
		center = Vector3f(0.0f, 0.0f, 0.0f);
		up = Vector3f(0.0f, 1.0f, 0.0f);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void drawWall(double thickness) {
	glColor3f(0.34117647058f, 0.25490196078f, 0.18431372549f);
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(20.0, 20.0*thickness, 20.0);
	glutSolidCube(1);
	glPopMatrix();
}

void drawCandle() {
	glPushMatrix();
	/////LOWER CENTER/////
	glTranslatef(0.0, lowerCenterCandleY+ lowerCenterCandleYNew, 0.0);
	glTranslatef(-0.0, -0.2 + lowerCenterCandleY+ lowerCenterCandleYNew, 0.1);
	glRotatef(lowerCenterCandleRotY, 0, 1, 0);
	glTranslatef(0.0, 0.2 - lowerCenterCandleY- lowerCenterCandleYNew, -0.1);
	/////primitive #1/////
	/////center sphere/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.0, 0.0, 0.1);
	glutWireSphere(0.04, 1000, 1000);
	glPopMatrix();
	/////primitive #2/////
	/////upper half body/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.0, 0.0, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.02, 0.06, 0.4, 1000, 1000);
	glPopMatrix();
	/////primitive #3/////
	/////lower sphere/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.0, -0.4, 0.1);
	glutWireSphere(0.075, 1000, 1000);
	glPopMatrix();
	/////primitive #4/////
	/////lower half body/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.0, -0.4, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	GLUquadricObj * qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_LINE);
	gluCylinder(qobj1, 0.04, 0.08, 0.4, 1000, 1000);
	glPopMatrix();
	/////LOWER CENTER/////
	glPopMatrix();

	glPushMatrix();
	/////LOWER LEFT CENTER/////
	/*glTranslatef(-0.15, -0.08, 0.1);
	glRotatef(lowerLeftAndRightCenterCandleY, 0, 1, 0);
	glTranslatef(0.15, 0.08, -0.1);*/
	/////primitive #6/////
	/////left hook/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(-0.015, -0.015, 0.1);
	glRotated(-45, 0, 1, 0);
	GLUquadricObj * qobj3;
	qobj3 = gluNewQuadric();
	gluQuadricDrawStyle(qobj3, GLU_LINE);
	gluCylinder(qobj3, 0.012, 0.012, 0.15, 1000, 1000);
	glPopMatrix();
	/////primitive #8/////
	/////left sphere/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(-0.3, -0.15, 0.1);
	glutWireSphere(0.035, 1000, 1000);
	glPopMatrix();
	/////LOWER LEFT CENTER/////
	glPopMatrix();

	glPushMatrix();
	/////LOWER RIGHT CENTER/////
	/*glTranslatef(lowerRightCenterCandleX, 0.0, 0.0);
	glTranslatef(-0.225 - lowerRightCenterCandleX, -0.08, 0.1);
	glRotatef(lowerLeftAndRightCenterCandleY, 0, 1, 0);
	glTranslatef(0.225 + lowerRightCenterCandleX, 0.08, -0.1);*/
	/////primitive #5/////
	/////right hook/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.23, 0.11, 0.1);
	glRotated(-45, 0, 1, 0);
	GLUquadricObj * qobj2;
	qobj2 = gluNewQuadric();
	gluQuadricDrawStyle(qobj2, GLU_LINE);
	gluCylinder(qobj2, 0.012, 0.012, 0.13, 1000, 1000);
	glPopMatrix();
	/////primitive #7/////
	/////right sphere/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.25, 0.12, 0.1);
	glutWireSphere(0.025, 1000, 1000);
	glPopMatrix();
	/////LOWER RIGHT CENTER/////
	glPopMatrix();

	glPushMatrix();
	/////CENTER/////
	glTranslatef(0.0, centerCandleY+ centerCandleYNew, 0.0);
	glTranslatef(-0.0, 0.055+centerCandleY+ centerCandleYNew, 0.1);
	glRotatef(centerCandleRotZ, 0, 0, 1);
	glTranslatef(0.0, -0.055-centerCandleY- centerCandleYNew, -0.1);
	/////primitive #11/////
	/////center column/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.0, 0.35, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj6;
	qobj6 = gluNewQuadric();
	gluQuadricDrawStyle(qobj6, GLU_LINE);
	gluCylinder(qobj6, 0.012, 0.012, 0.35, 1000, 1000);
	glPopMatrix();
	/////primitive #14/////
	/////center rest/////
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.0, 0.48, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj12;
	qobj12 = gluNewQuadric();
	gluQuadricDrawStyle(qobj12, GLU_LINE);
	gluCylinder(qobj12, 0.065, 0.012, 0.15, 1000, 1000);
	glPopMatrix();
	/////primitive #15/////
	/////center candle/////
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(0.0, 0.68, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj9;
	qobj9 = gluNewQuadric();
	gluQuadricDrawStyle(qobj9, GLU_LINE);
	gluCylinder(qobj9, 0.025, 0.025, 0.2, 1000, 1000);
	glPopMatrix();
	/////primitive #20/////
	/////center candle flame/////
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(0.0, 0.73, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj15;
	qobj15 = gluNewQuadric();
	gluQuadricDrawStyle(qobj15, GLU_LINE);
	gluCylinder(qobj15, 0.000001, 0.024, 0.05, 2000, 2000);
	glPopMatrix();
	/////CENTER/////
	glPopMatrix();

	glPushMatrix();
	/////LEFT/////
	glTranslatef(-0.3, 0.045, 0.1);
	glRotatef(candleRotZ, 0, 0, 1);
	glTranslatef(0.3, -0.045, -0.1);
	/////primitive #10/////
	/////left column///// ---left---
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(-0.3, 0.045, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj5;
	qobj5 = gluNewQuadric();
	gluQuadricDrawStyle(qobj5, GLU_LINE);
	gluCylinder(qobj5, 0.012, 0.012, 0.3, 1000, 1000);
	glPopMatrix();
	/////primitive #13/////
	/////left rest/////  ---left---
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(-0.3, 0.13, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj8;
	qobj8 = gluNewQuadric();
	gluQuadricDrawStyle(qobj8, GLU_LINE);
	gluCylinder(qobj8, 0.065, 0.012, 0.15, 1000, 1000);
	glPopMatrix();
	/////primitive #16/////
	/////left candle///// ---left---
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(-0.3, 0.3, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj10;
	qobj10 = gluNewQuadric();
	gluQuadricDrawStyle(qobj10, GLU_LINE);
	gluCylinder(qobj10, 0.025, 0.025, 0.2, 1000, 1000);
	glPopMatrix();
	/////primitive #19/////
	/////left candle flame/////  ---left---
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(-0.3, 0.35, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj14;
	qobj14 = gluNewQuadric();
	gluQuadricDrawStyle(qobj14, GLU_LINE);
	gluCylinder(qobj14, 0.000001, 0.024, 0.05, 2000, 2000);
	glPopMatrix();
	/////LEFT/////
	glPopMatrix();

	glPushMatrix();
	/////RIGHT/////
	glTranslated(0.26, 0.28, 0.1);
	glRotatef(-candleRotZ, 0, 0, 1);
	glTranslated(-0.26, -0.28, -0.1);
	/////primitive #9/////
	/////right column///// ---right---
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.26, 0.28, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj4;
	qobj4 = gluNewQuadric();
	gluQuadricDrawStyle(qobj4, GLU_LINE);
	gluCylinder(qobj4, 0.012, 0.012, 0.25, 1000, 1000);
	glPopMatrix();
	/////primitive #12/////
	/////right rest/////  ---right---
	glPushMatrix();
	glColor3f(1.0f, 0.871f, 0.0f);
	glTranslated(0.265, 0.37, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj7;
	qobj7 = gluNewQuadric();
	gluQuadricDrawStyle(qobj7, GLU_LINE);
	gluCylinder(qobj7, 0.05, 0.012, 0.1, 1000, 1000);
	glPopMatrix();
	/////primitive #17/////
	/////right candle/////  ---right---
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(0.265, 0.5, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj11;
	qobj11 = gluNewQuadric();
	gluQuadricDrawStyle(qobj11, GLU_LINE);
	gluCylinder(qobj11, 0.02, 0.02, 0.15, 1000, 1000);
	glPopMatrix();
	/////primitive #18/////
	/////right candle flame/////  ---right---
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(0.265, 0.55, 0.1);
	glRotated(45, 0, 1, 0);
	//glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj13;
	qobj13 = gluNewQuadric();
	gluQuadricDrawStyle(qobj13, GLU_LINE);
	gluCylinder(qobj13, 0.000001, 0.02, 0.05, 2000, 2000);
	glPopMatrix();
	/////RIGHT/////
	glPopMatrix();
}

void drawStand() {
	/////primitive #01/////
	glPushMatrix();
	glColor3f(0.647f, 0.1647f, 0.1647f);
	glTranslated(0.2, -0.1, -1.0);
	glScaled(1.0, 1.5, 1.0);
	glutSolidCube(0.4);
	glPopMatrix();
	/////primitive #02/////
	glPushMatrix();
	glColor3f(0.81176f, 0.7098f, 0.23137f);
	glTranslated(0.2, -0.5, -1.0);
	glScaled(0.75, 0.5, 1.0);
	glutSolidCube(0.4);
	glPopMatrix();
	/////primitive #03/////
	glPushMatrix();
	glColor3f(0.647f, 0.1647f, 0.1647f);
	glTranslated(0.2, -0.7, -1.0);
	glScaled(1.25, 0.5, 1.0);
	glutSolidCube(0.4);
	glPopMatrix();
	/////primitive #04/////
	glPushMatrix();
	glColor3f(0.81176f, 0.7098f, 0.23137f);
	glTranslated(0.05, -0.9, -1.0);
	glScaled(0.25, 0.5, 1.0);
	glutSolidCube(0.4);
	glPopMatrix();
	/////primitive #05/////
	glPushMatrix();
	glColor3f(0.81176f, 0.7098f, 0.23137f);
	glTranslated(0.35, -0.9, -1.0);
	glScaled(0.25, 0.5, 1.0);
	glutSolidCube(0.4);
	glPopMatrix();
	/////primitive #06/////
	/*glPushMatrix();
	glTranslated(0.5, 0.5, -0.25);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(75, 0, 1, 0);
	glRotated(50, 1, 0, 0);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.12, 0.12, 0.2, 1000, 1000);
	glPopMatrix();*/
}

void drawFeatherDust() {
	/////primitive #01/////
	glPushMatrix();
	//glColor3f(0.54296875f, 0.26953125f, 0.07421875f);
	glColor3f(0.625f, 0.625f, 0.2734375f);
	glTranslated(-3.4, -0.6, -1.0);
	glScaled(0.1, 0.4, 0.1);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	/////primitive #02/////
	glPushMatrix();
	glColor3f(0.80078125f, 0.49609375f, 0.1953125f);
	glTranslated(-3.4, -1.0, -1.0);
	glRotated(90.0, 1, 0, 0);
	glRotated(20.0, 0, 1, 0);
	glScaled(0.1, 0.2, 0.1);
	glutWireTorus(0.5, 0.3, 1000, 1000);
	glPopMatrix();
	/////primitive #03/////
	glPushMatrix();
	glColor3f(0.625f, 0.625f, 0.2734375f);
	glTranslated(-3.4, -1.05, -1.0);
	glRotated(55, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	glScaled(2.0, 1.0, 1.0);
	GLUquadricObj * qobj14;
	qobj14 = gluNewQuadric();
	gluQuadricDrawStyle(qobj14, GLU_LINE);
	gluCylinder(qobj14, 0.02, 0.05, 2.0, 2000, 2000);
	glPopMatrix();
	/////primitive #04/////
	glPushMatrix();
	glColor3f(0.80078125f, 0.49609375f, 0.1953125f);
	glTranslated(-3.26, -3.06, -1.0);
	glRotated(90.0, 1, 0, 0);
	glRotated(20.0, 0, 1, 0);
	glScaled(0.1, 0.1, 0.1);
	//glutWireTorus(0.5, 0.3, 1000, 1000);
	glPopMatrix();
	/////primitive #05/////
	glPushMatrix();
	glColor3f(0.80078125f, 0.49609375f, 0.1953125f);
	glTranslated(-3.28, -3.08, -1.0);
	glRotated(80.0, 1, 0, 0);
	glRotated(20.0, 0, 1, 0);
	glScaled(0.1, 0.1, 0.1);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	/////primitive #06/////
	glPushMatrix();
	glColor3f(0.625f, 0.625f, 0.2734375f);
	glTranslated(-3.3, -3.25, -1.0);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(2.0, 1.0, 1.0);
	GLUquadricObj * qobj15;
	qobj15 = gluNewQuadric();
	gluQuadricDrawStyle(qobj15, GLU_LINE);
	gluCylinder(qobj15, 0.08, 0.08, 0.2, 2000, 2000);
	glPopMatrix();
	/////primitive #07/////
	glPushMatrix();
	glColor3f(0.390625f, 0.25390625f, 0.640625f);
	glTranslated(-3.3, -3.45, -1.0);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(2.0, 1.0, 1.0);
	GLUquadricObj * qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_LINE);
	gluCylinder(qobj1, 0.4, 0.08, 1.5, 2000, 2000);
	glPopMatrix();
}

void drawTeapot() {
	glPushMatrix();
	/////primitive #01/////
	glPushMatrix();
	glColor3f(0.95703125f, 0.95703125f, 0.859375f);
	glTranslated(0.84, 0.6, 0.7);
	glScaled(0.1, 0.18, 0.1);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();
	/////primitive #02/////
	glPushMatrix();
	glColor3f(0.828125f, 0.88359375f, 0.21484375f);
	glTranslated(0.85, 0.525, 0.7);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.28, 0.2, 0.2);
	GLUquadricObj * qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_LINE);
	gluCylinder(qobj1, 0.08, 0.08, 0.2, 2000, 2000);
	glPopMatrix();
	/////primitive #03/////
	glPushMatrix();
	glColor3f(1.0f, 0.078125f, 0.5f);
	glTranslated(0.85, 0.499, 0.7);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	GLUquadricObj * qobj2;
	qobj2 = gluNewQuadric();
	gluQuadricDrawStyle(qobj2, GLU_LINE);
	gluCylinder(qobj2, 0.08, 0.18, 0.16, 2000, 2000);
	glPopMatrix();
	/////primitive #04/////
	glPushMatrix();
	glColor3f(0.828125f, 0.88359375f, 0.21484375f);
	glTranslated(0.85, 0.48, 0.7);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	GLUquadricObj * qobj3;
	qobj3 = gluNewQuadric();
	gluQuadricDrawStyle(qobj3, GLU_LINE);
	gluCylinder(qobj3, 0.18, 0.18, 0.1, 2000, 2000);
	glPopMatrix();
	/////primitive #05/////
	glPushMatrix();
	glColor3f(0.328125f, 0.0859375f, 0.703125f);
	glTranslated(0.84, 0.74, 0.71);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(5, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	GLUquadricObj * qobj4;
	qobj4 = gluNewQuadric();
	gluQuadricDrawStyle(qobj4, GLU_LINE);
	gluCylinder(qobj4, 0.018, 0.18, 0.3, 2000, 2000);
	glPopMatrix();
	/////primitive #06/////
	glPushMatrix();
	glColor3f(1.0f, 0.098125f, 0.6f);
	glTranslated(0.84, 0.741, 0.71);
	glScaled(0.1, 0.1, 0.1);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();
	///// /////
	glPopMatrix();
}

void drawCup(){
	/////primitive #01/////
	glPushMatrix();
	glColor3f(0.828125f, 0.88359375f, 0.21484375f);
	glTranslated(0.9, 0.515, 0.5);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	GLUquadricObj * qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_LINE);
	gluCylinder(qobj1, 0.082, 0.082, 0.1, 2000, 2000);
	glPopMatrix();
	/////primitive #02/////
	glPushMatrix();
	glColor3f(1.0f, 0.078125f, 0.5f);
	glTranslated(0.9, 0.499, 0.5);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	GLUquadricObj * qobj2;
	qobj2 = gluNewQuadric();
	gluQuadricDrawStyle(qobj2, GLU_LINE);
	gluCylinder(qobj2, 0.08, 0.18, 0.16, 2000, 2000);
	glPopMatrix();
	/////primitive #03/////
	glPushMatrix();
	glColor3f(0.828125f, 0.88359375f, 0.21484375f);
	glTranslated(0.9, 0.48, 0.5);
	glRotated(55, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(12, 0, 0, 1);
	glRotated(5, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	GLUquadricObj * qobj3;
	qobj3 = gluNewQuadric();
	gluQuadricDrawStyle(qobj3, GLU_LINE);
	gluCylinder(qobj3, 0.18, 0.18, 0.1, 2000, 2000);
	glPopMatrix();
	/////primitive #04/////
	glPushMatrix();
	glColor3f(0.95703125f, 0.95703125f, 0.859375f);
	glTranslated(0.9, 0.565, 0.5);
	glScaled(0.1, 0.1, 0.1);
	glRotated(85, 1, 0, 0);
	glRotated(2, 0, 1, 0);
	GLUquadricObj * qobj4;
	qobj4 = gluNewQuadric();
	gluQuadricDrawStyle(qobj4, GLU_LINE);
	gluCylinder(qobj4, 0.5, 0.18, 0.5, 2000, 2000);
	glPopMatrix();
	/////primitive #05/////
	glPushMatrix();
	glColor3f(0.828125f, 0.88359375f, 0.21484375f);
	glTranslated(0.9, 0.5765, 0.5);
	glScaled(0.1, 0.1, 0.1);
	glRotated(85, 1, 0, 0);
	glRotated(2, 0, 1, 0);
	GLUquadricObj * qobj5;
	qobj5 = gluNewQuadric();
	gluQuadricDrawStyle(qobj5, GLU_LINE);
	gluCylinder(qobj5, 0.5, 0.5, 0.1, 2000, 2000);
	glPopMatrix();
}

void drawChandelier() {

	/*glPushMatrix();
	/////GLOBAL/////
	glTranslatef(0.0, chandelierTransY + chandelierTransYNew, 0.0);
	glPushMatrix();
	/////MAIN HOOK/////
	/////TRANSFORMATION/////
	/////primitive #1/////
	/////hook/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.23, 0.5, 0.1);
	glRotated(-45, 0, 1, 0);
	GLUquadricObj * qobj2;
	qobj2 = gluNewQuadric();
	gluQuadricDrawStyle(qobj2, GLU_LINE);
	gluCylinder(qobj2, 0.015, 0.015, 0.4, 1000, 1000);
	glPopMatrix();
	/////primitive #2/////
	/////right sphere/////
	glPushMatrix();
	glColor3f(1.0f, 0.85882352941f, 0.44509803921f);
	glTranslated(-0.23, 0.5, 0.1);
	glutWireSphere(0.025, 1000, 1000);
	glPopMatrix();
	/////primitive #3/////
	/////left sphere/////
	glPushMatrix();
	glColor3f(1.0f, 0.85882352941f, 0.44509803921f);
	glTranslated(-1.04, 0.341, 0.2);
	glutWireSphere(0.03, 1000, 1000);
	glPopMatrix();
	/////MAIN HOOK/////
	glPopMatrix();

	glPushMatrix();
	/////LOWER COLUMNS/////
	/////TRANSFORMATION/////
	/////primitive #4/////
	/////right column///// ---right---
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.35, 0.46, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj4;
	qobj4 = gluNewQuadric();
	gluQuadricDrawStyle(qobj4, GLU_LINE);
	gluCylinder(qobj4, 0.01, 0.01, 0.15, 1000, 1000);
	glPopMatrix();
	/////primitive #5/////
	/////right sphere///// ---right---
	glPushMatrix();
	glColor3f(1.0f, 0.85882352941f, 0.44509803921f);
	glTranslated(-0.42, 0.255, 0.05);
	glutWireSphere(0.025, 1000, 1000);
	glPopMatrix();
	/////primitive #6/////
	/////left column///// ---left---
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-1.05, 0.3, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj5;
	qobj5 = gluNewQuadric();
	gluQuadricDrawStyle(qobj5, GLU_LINE);
	gluCylinder(qobj5, 0.012, 0.012, 0.2, 1000, 1000);
	glPopMatrix();
	/////primitive #7/////
	/////left sphere///// ---left---
	glPushMatrix();
	glColor3f(1.0f, 0.85882352941f, 0.44509803921f);
	glTranslated(-1.144, 0.05, 0.05);
	glutWireSphere(0.03, 1000, 1000);
	glPopMatrix();
	/////primitive #8/////
	/////center column///// ---center---
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.625, 0.4, 0.1);
	glRotated(45, 0, 1, 0);
	glRotated(100, 1, 0, 0);
	glRotated(-50, 0, 0, 1);
	GLUquadricObj * qobj6;
	qobj6 = gluNewQuadric();
	gluQuadricDrawStyle(qobj6, GLU_LINE);
	gluCylinder(qobj6, 0.012, 0.012, 0.11, 1000, 1000);
	glPopMatrix();
	/////primitive #9/////
	/////center sphere///// ---center---
	glPushMatrix();
	glColor3f(1.0f, 0.85882352941f, 0.44509803921f);
	glTranslated(-0.7, 0.24, 0.05);
	glutWireSphere(0.03, 1000, 1000);
	glPopMatrix();
	/////LOWER COLUMNS/////
	glPopMatrix();*/


	glPushMatrix();
	/////UPPER SECTION/////
	glTranslated(-0.275+chandelierTransX2, 0.87 + chandelierTransY + chandelierTransYNew + chandelierTransY2, 0.27);
	glRotated(chandelierRotY, 0, 1, 0);
	glTranslated(0.275-chandelierTransX2, -0.87 - chandelierTransY - chandelierTransYNew - chandelierTransY2, -0.27);
	/////primitive #10/////
	/////big holder/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glRotated(45, 0, 1, 0);
	glTranslated(-0.385, 0.6, 0.02);
	glScaled(1.5, 0.3, 1.0);
	glutSolidCube(0.2);
	glPopMatrix();
	/////primitive #11/////
	/////medium holder/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glRotated(45, 0, 1, 0);
	glTranslated(-0.385, 0.645, 0.02);
	glScaled(1.2, 0.4, 1.0);
	glutSolidCube(0.15);
	glPopMatrix();
	/////primitive #12/////
	/////small holder/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glRotated(45, 0, 1, 0);
	glTranslated(-0.385, 0.7, 0.02);
	glScaled(1.0, 0.4, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	/////primitive #13/////
	/////lower right candle column/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.17, 0.68, 0.2);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj7;
	qobj7 = gluNewQuadric();
	gluQuadricDrawStyle(qobj7, GLU_LINE);
	gluCylinder(qobj7, 0.012, 0.012, 0.09, 1000, 1000);
	glPopMatrix();
	/////primitive #14/////
	/////lower right candle holder/////
	glPushMatrix();
	glColor3f(0.33203125f, 0.2890625f, 0.234375f);
	glTranslated(-0.17, 0.72, 0.2);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj8;
	qobj8 = gluNewQuadric();
	gluQuadricDrawStyle(qobj8, GLU_LINE);
	gluCylinder(qobj8, 0.024, 0.012, 0.04, 1000, 1000);
	glPopMatrix();
	/////primitive #15/////
	/////lower right candle/////
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(-0.17, 0.78, 0.2);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj17;
	qobj17 = gluNewQuadric();
	gluQuadricDrawStyle(qobj17, GLU_LINE);
	gluCylinder(qobj17, 0.012, 0.012, 0.06, 1000, 1000);
	glPopMatrix();
	/////primitive #16/////
	/////lower right candle flame/////
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(-0.17, 0.8, 0.2);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj170;
	qobj170 = gluNewQuadric();
	gluQuadricDrawStyle(qobj170, GLU_LINE);
	gluCylinder(qobj170, 0.001, 0.012, 0.02, 1000, 1000);
	glPopMatrix();
	/////primitive #17/////
	/////middle right candle column/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.2, 0.74, 0.24);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj18;
	qobj18 = gluNewQuadric();
	gluQuadricDrawStyle(qobj18, GLU_LINE);
	gluCylinder(qobj18, 0.012, 0.012, 0.06, 1000, 1000);
	glPopMatrix();
	/////primitive #18/////
	/////middle right candle holder/////
	glPushMatrix();
	glColor3f(0.33203125f, 0.2890625f, 0.234375f);
	glTranslated(-0.2, 0.78, 0.24);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj19;
	qobj19 = gluNewQuadric();
	gluQuadricDrawStyle(qobj19, GLU_LINE);
	gluCylinder(qobj19, 0.024, 0.012, 0.04, 1000, 1000);
	glPopMatrix();
	/////primitive #19/////
	/////middle right candle/////
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(-0.2, 0.84, 0.24);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj20;
	qobj20 = gluNewQuadric();
	gluQuadricDrawStyle(qobj20, GLU_LINE);
	gluCylinder(qobj20, 0.012, 0.012, 0.06, 1000, 1000);
	glPopMatrix();
	/////primitive #20/////
	/////middle right candle flame/////
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(-0.2, 0.86, 0.24);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj201;
	qobj201 = gluNewQuadric();
	gluQuadricDrawStyle(qobj201, GLU_LINE);
	gluCylinder(qobj201, 0.001, 0.012, 0.02, 1000, 1000);
	glPopMatrix();
	/////primitive #21/////
	/////middle holder/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.275, 0.87, 0.27);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj9;
	qobj9 = gluNewQuadric();
	gluQuadricDrawStyle(qobj9, GLU_LINE);
	gluCylinder(qobj9, 0.012, 0.012, 0.15, 1000, 1000);
	glPopMatrix();
	/////primitive #22/////
	/////middle left candle column/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.32, 0.73, 0.32);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj10;
	qobj10 = gluNewQuadric();
	gluQuadricDrawStyle(qobj10, GLU_LINE);
	gluCylinder(qobj10, 0.012, 0.012, 0.08, 1000, 1000);
	glPopMatrix();
	/////primitive #23/////
	/////middle left candle holder/////
	glPushMatrix();
	glColor3f(0.33203125f, 0.2890625f, 0.234375f);
	glTranslated(-0.32, 0.77, 0.32);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj100;
	qobj100 = gluNewQuadric();
	gluQuadricDrawStyle(qobj100, GLU_LINE);
	gluCylinder(qobj100, 0.024, 0.012, 0.04, 1000, 1000);
	glPopMatrix();
	/////primitive #24/////
	/////middle left candle/////
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(-0.32, 0.83, 0.32);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj101;
	qobj101 = gluNewQuadric();
	gluQuadricDrawStyle(qobj101, GLU_LINE);
	gluCylinder(qobj101, 0.012, 0.012, 0.06, 1000, 1000);
	glPopMatrix();
	/////primitive #25/////
	/////middle left candle flame/////
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(-0.32, 0.85, 0.32);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj1011;
	qobj1011 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1011, GLU_LINE);
	gluCylinder(qobj1011, 0.001, 0.012, 0.02, 1000, 1000);
	glPopMatrix();
	/////primitive #26/////
	/////lower left candle column/////
	glPushMatrix();
	glColor3f(0.80392156862f, 0.60784313725f, 0.11372549019f);
	glTranslated(-0.345, 0.68, 0.38);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj110;
	qobj110 = gluNewQuadric();
	gluQuadricDrawStyle(qobj110, GLU_LINE);
	gluCylinder(qobj110, 0.012, 0.012, 0.08, 1000, 1000);
	glPopMatrix();
	/////primitive #27/////
	/////lower left candle holder/////
	glPushMatrix();
	glColor3f(0.33203125f, 0.2890625f, 0.234375f);
	glTranslated(-0.345, 0.725, 0.38);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj111;
	qobj111 = gluNewQuadric();
	gluQuadricDrawStyle(qobj111, GLU_LINE);
	gluCylinder(qobj111, 0.024, 0.012, 0.04, 1000, 1000);
	glPopMatrix();
	/////primitive #28/////
	/////lower left candle/////
	glPushMatrix();
	glColor3f(0.955f, 0.880f, 0.63f);
	glTranslated(-0.345, 0.78, 0.38);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj112;
	qobj112 = gluNewQuadric();
	gluQuadricDrawStyle(qobj112, GLU_LINE);
	gluCylinder(qobj112, 0.012, 0.012, 0.06, 1000, 1000);
	glPopMatrix();
	/////primitive #29/////
	/////lower left candle flame/////
	glPushMatrix();
	glColor3f(0.695f, 0.133f, 0.133f);
	glTranslated(-0.345, 0.8, 0.38);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj113;
	qobj113 = gluNewQuadric();
	gluQuadricDrawStyle(qobj113, GLU_LINE);
	gluCylinder(qobj113, 0.001, 0.012, 0.02, 1000, 1000);
	glPopMatrix();
	/////UPPER SECTION/////
	glPopMatrix();

	/*/////GLOBAL/////
	glPopMatrix();*/
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setupCamera();
	setupLights();

	glPushMatrix();
	glTranslated(-0.1, 0.0, 0.0);
	glTranslated(candleTransX2+candleTransX2New+candleTransX2New2, 0.0, candleTransZ2 + candleTransZ2New + candleTransZ2New2);
	glScaled(candleScale2New, candleScale2New, candleScale2New);
	glScaled(candleScale2, candleScale2, candleScale2);
	glScaled(0.6, 0.6, 0.6);
	drawCandle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(teapotTransX, teapotTransY, teapotTransZ);
	glRotatef(teapotRotX, 1, 0, 0);
	glRotatef(teapotRotY, 0, 1, 0);
	glRotatef(teapotRotZ, 0, 0, 1);
	glScalef(0.8, 0.8, 0.8);
	drawTeapot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(featherdustTransX, featherdustTransY, featherdustTransZ);
	glTranslatef(featherdustTransXNew, featherdustTransYNew, featherdustTransZNew);
	glRotatef(featherdustRotX, 1, 0, 0);
	glRotatef(featherdustRotY, 0, 1, 0);
	glRotatef(featherdustRotZ, 0, 0, 1);
	glScalef(0.3, 0.3, 0.3);
	glTranslatef(-1.9, -1.5, -0.5);
	drawFeatherDust();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.9, 0.9, 0.9);
	glTranslatef(0.9+cupX+newCupX, 0.5+cupY+newCupY, 0.5);
	glRotatef(cupRotZ, 0, 0, 1);
	glTranslatef(-0.9-cupX-newCupX, -0.5-cupY-newCupY, -0.5);
	glTranslatef(cupX+newCupX, cupY+newCupY, 0.0);
	drawCup();
	glPopMatrix();

	glPushMatrix();
	glRotatef(standRotX, 1, 0, 0);
	glRotatef(standRotY, 0, 1, 0);
	glRotatef(standRotZ, 0, 0, 1);
	glTranslatef(-standTransX, -standTransY, standTransZ);
	glTranslatef(standTransXNew, standTransYNew, standTransZNew);
	glTranslatef(-0.4, 0.0, -0.8);
	glScalef(0.6, 0.6, 0.6);
	drawStand();
	glPopMatrix();

	glPushMatrix();

	glTranslatef(chandelierTransX2, chandelierTransY + chandelierTransYNew + chandelierTransY2, 0.0);

	glTranslated(-0.275+chandelierTransX2, 0.87 + chandelierTransY + chandelierTransYNew + chandelierTransY2, 0.27);
	glScalef(chandelierScale2New, chandelierScale2New, chandelierScale2New);
	glTranslated(0.275 - chandelierTransX2, -0.87 - chandelierTransY - chandelierTransYNew - chandelierTransY2, -0.27);

	glTranslated(-0.275 + chandelierTransX2, 0.87 + chandelierTransY + chandelierTransYNew + chandelierTransY2, 0.27);
	glScalef(chandelierScale2, chandelierScale2, chandelierScale2);
	glTranslated(0.275 - chandelierTransX2, -0.87 - chandelierTransY - chandelierTransYNew - chandelierTransY2, -0.27);
	
	
	drawChandelier();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0, -5.0, -5.0);
	drawWall(0.02);
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	drawWall(0.02);
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();
	glPopMatrix();
	
	glFlush();
}

void Anim() {
	/////stand animation/////
	if (globalAnimationSwitch || standAnimationSwitch) {
		standTransY += 0.00001;
		if (standTransX <= 3.5) {
			standTransX += 0.25;
			standTransY = sin(standTransX);
			temp = standTransX;
		}
		else {
			if (temp == standTransX) {
				standTransY += 0.8;
				temp++;
			}
			if (standTransXNew < 3.5) {
				standTransXNew += 0.25;
				standTransYNew = sin(standTransXNew);
			}
			else {
				if (standRotX <= 50.0) {
					standRotX += 5;
				}
				else {
					standTransX = 0.0;
					standTransY = 0.0;
					standTransZ = 0.0;
					standTransXNew = 0.0;
					standTransYNew = 0.0;
					standTransZNew = 0.0;
					standRotX = 0.0;
				}
			}
		}
	}
	/////teapot animation/////
	if (globalAnimationSwitch || teapotAnimationSwitch) {
		t += 0.75;
		teapotTransX = (1 * cos(t) + 0) / 10;
		teapotTransY = (1 * sin(t) + 0) / 10;
	}
	/////featherdust animation/////
	if (globalAnimationSwitch || featherdustAnimationSwitch) {
		featherdustT += 0.15;
		if (featherdustT<3.65) {
			featherdustTransX = featherdustT / 2 * cos(5 * featherdustT);
			featherdustTransY = featherdustT / 2 * sin(5 * featherdustT);
			featherdustTransZ = -featherdustT;
		}
		else {
			if (featherdustTNew == 0) {
				featherdustTNew = featherdustT;
			}
			else {
				if (featherdustTNew > 0) {
					featherdustTNew -= 0.1;
					featherdustTransX = featherdustTNew / 2 * cos(5 * featherdustTNew);
					featherdustTransY = featherdustTNew / 2 * sin(5 * featherdustTNew);
					featherdustTransZ = -featherdustTNew;
				}
				else {
					featherdustT = 0;
					featherdustTNew = 0;
				}

			}
		}
	}
	/////cup animation/////
	if (globalAnimationSwitch || cupAnimationSwitch) {
		if (cupRotZ <= 360) {
			cupRotZ += 90;
		}
		else {
			if (cupY <= 0.3) {
				cupY += 0.05;
			}
			else {
				if (cupX >= -0.2) {
					cupX -= 0.05;
				}
				else {
					if (newCupY >= -0.3) {
						newCupY -= 0.05;
					}
					else {
						if (newCupX <= 0.2) {
							newCupX += 0.05;
						}
						else {
							cupRotZ = 0.0;
							cupX = 0.0;
							newCupX = 0.0;
							cupY = 0.0;
							newCupY = 0.0;
						}
					}
				}
			}
			cupRotZ = 0;
		}
	}
	/////candle animation/////
	if (globalAnimationSwitch || candleAnimationSwitch) {
		//left and right candles
		candleRotZ += 45;
		//upper-center
		if (centerCandleY <= 0.4) {
			centerCandleY += 0.1;
		}
		else {
			if (centerCandleRotZ < 360) {
				centerCandleRotZ += 45;
			}
			else {
				if (centerCandleYNew >= -0.4) {
					centerCandleYNew -= 0.1;
				}
				else {
					centerCandleRotZ = 0.0;
					centerCandleY = 0.0;
					centerCandleYNew = 0.0;
				}
			}

		}
		//lower-center
		if (lowerCenterCandleY >= -0.5) {
			lowerCenterCandleY -= 0.1;
		}
		else {
			if (lowerCenterCandleRotY < 360) {
				lowerCenterCandleRotY += 45;
			}
			else {
				if (lowerCenterCandleYNew <= 0.5) {
					lowerCenterCandleYNew += 0.1;
				}
				else {
					lowerCenterCandleY = 0.0;
					lowerCenterCandleRotY = 0.0;
					lowerCenterCandleYNew = 0.0;
				}
			}

		}
	}
	/////chandelier animation/////
	if (globalAnimationSwitch || chandelierAnimationSwitch) {
		if (chandelierTransY > -1.5) {
			chandelierTransY -= 0.2;
		}
		else {
			if (chandelierTransYNew < 1.5) {
				chandelierTransYNew += 0.2;
			}
			else {
				chandelierTransY = 0.0;
				chandelierTransYNew = 0.0;
			}
		}
		chandelierRotY += 30;
	}
	/////camera animation/////
	if (cameraAnimationSwitch) {
		if (counter >= 3 && counter <= 7) {
			camera.moveX(-d);
		}
		if (counter >= 8 && counter <= 9) {
			camera.moveZ(d);
			camera.rotateY(5.0);
		}
		if (counter >= 10 && counter <= 12) {
			camera.moveX(-d);
			camera.rotateY(2.5);
		}
		if (counter >= 13 && counter <= 17) {
			camera.moveX(-d);
			//camera.rotateY(5.0);
		}
		if (counter >= 18 && counter <= 20) {
			camera.moveX(-d);
			camera.rotateY(2.5);
		}
		if (counter >= 21 && counter <= 27) {
			camera.moveZ(-d);
			camera.moveX(-d);
			//camera.rotateY(2.5);
		}
		if (counter >= 28 && counter <= 31) {
			camera.moveZ(-d);
			camera.moveX(-d);
			camera.rotateY(2.5);
		}
		if (counter >= 32 && counter <= 36) {
			camera.moveX(-d);
		}
		if (counter >= 37 && counter <= 40) {
			camera.moveX(-d);
			camera.rotateY(2.5);
		}
		if (counter >= 41 && counter <= 46) {
			camera.moveX(-d);
			//camera.rotateY(2.5);
		}
		if (counter >= 47 && counter <= 65) {
			camera.moveX(-2 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 66 && counter <= 75) {
			camera.moveZ(-2 * d);
		}
		if (counter >= 76 && counter <= 80) {
			camera.moveZ(-2 * d);
			camera.moveX(-2 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 81 && counter <= 98) {
			camera.moveZ(-2 * d);
			camera.moveX(-3 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 99 && counter <= 105) {
			camera.moveY(-d);
			camera.moveZ(-5 * d);
			camera.moveX(-3 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 106 && counter <= 108) {
			camera.moveX(-5 * d);
			camera.moveY(-5 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 109 && counter <= 118) {
			camera.moveX(-5 * d);
		}
		if (counter >= 119 && counter <= 128) {
			camera.moveX(-d);
			camera.rotateY(2.5);
		}
		if (counter >= 129 && counter <= 145) {
			camera.moveY(-d);
			camera.moveX(-6 * d);
			camera.moveZ(-d);
			camera.rotateY(2.5);
		}
		if (counter >= 146 && counter <= 159) {
			camera.moveY(-d);
			camera.moveX(-6 * d);
			camera.moveZ(d);
			camera.rotateY(2.5);
		}
		if (counter >= 160 && counter <= 165) {
			camera.moveX(-d);
			camera.moveZ(2 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 166 && counter <= 170) {
			camera.moveY(d);
			camera.moveX(-d);
			camera.moveZ(2 * d);
		}
		if (counter >= 171 && counter <= 175) {
			camera.moveY(d);
			camera.moveX(-2 * d);
			camera.moveZ(2 * d);
			camera.rotateY(2.5);
		}
		if (counter >= 176 && counter <= 180) {
			camera.moveZ(3 * d);
		}
		if (counter >= 181) {
			camera.reset();
			counter = 3;
		}
		counter++;
	}
	/////chandelier animation2/////
	if (chandelierAnimationSwitch2) {
		chandelierT2 += 0.5;
		chandelierTransX2 = (1.0 * cos(chandelierT2) + 0) / 10;
		chandelierTransY2 = (1.0 * sin(chandelierT2) + 0) / 10;

		if (chandelierScale2 >= 0.5) {
			chandelierScale2 *= 0.8;
		}
		else {
			if (chandelierScale2New <= 2.0) {
				chandelierScale2New *= 1.2;
			}
			else {
				chandelierScale2 = 1.0;
				chandelierScale2New = 1.0;
			}

		}
	}

	/////candle animation2/////
	if (candleAnimationSwitch2) {
		if (candleTransZ2 < 0.5) {
			candleTransX2 += 0.1;
			candleTransZ2 += 0.1;
		}
		else {
			if (candleScale2 > 0.5) {
				candleScale2 *= 0.9;
			}
			else {
				if (candleT2 < 360) {
					candleT2 += 45;
					candleTransX2New = (1 * cos(candleT2) + 0) / 10;
					candleTransZ2New = (1 * sin(candleT2) + 0) / 10;
				}
				else {
					if (candleScale2New < 1.8) {
						candleScale2New *= 1.1;
					}
					else {
						if (candleTransZ2New2 > -0.5) {
							candleTransX2New2 -= 0.1;
							candleTransZ2New2 -= 0.1;
						}
						else {
							candleT2 = 0.0;
							candleTransX2 = 0.0;
							candleTransZ2 = 0.0;
							candleScale2 = 1.0;
							candleScale2New = 1.0;
							candleTransX2New = 0.0;
							candleTransZ2New = 0.0;
							candleTransX2New2 = 0.0;
							candleTransZ2New2 = 0.0;
						}
					}
				}
				
			}
		}
	}
	
	glutPostRedisplay();

}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	///// animation controls /////
	case 'q':
		//stand animation
		standAnimationSwitch = standAnimationSwitch ? false : true;
		if (!standAnimationSwitch) {
			standTransX = 0.0;
			standTransY = 0.0;
			standTransZ = 0.0;
			standTransXNew = 0.0;
			standTransYNew = 0.0;
			standTransZNew = 0.0;
			standRotX = 0.0;
			standRotY = 0.0;
			standRotZ = 0.0;
		}
		break;
	case 'w':
		//teapot animation
		teapotAnimationSwitch = teapotAnimationSwitch ? false : true;
		if (!teapotAnimationSwitch) {
			t = 0.0;
			teapotTransX = 0.0;
			teapotTransY = 0.0;
			teapotTransZ = 0.0;
			teapotTransXNew = 0.0;
			teapotTransYNew = 0.0;
			teapotTransZNew = 0.0;
			teapotRotX = 0.0;
			teapotRotY = 0.0;
			teapotRotZ = 0.0;
		}
		break;
	case 'e':
		//featherdust animation
		featherdustAnimationSwitch = featherdustAnimationSwitch ? false : true;
		if (!featherdustAnimationSwitch) {
			featherdustT = 0.0;
			featherdustTNew = 0.0;
			featherdustTransX = 0.0;
			featherdustTransY = 0.0;
			featherdustTransZ = 0.0;
			featherdustTransXNew = 0.0;
			featherdustTransYNew = 0.0;
			featherdustTransZNew = 0.0;
			featherdustRotX = 0.0;
			featherdustRotY = 0.0;
			featherdustRotZ = 0.0;
		}
		break;
	case 'r':
		//cup animation
		cupAnimationSwitch = cupAnimationSwitch ? false : true;
		if (!cupAnimationSwitch) {
			cupRotZ = 0.0;
			cupX = 0.0;
			newCupX = 0.0;
			cupY = 0.0;
			newCupY = 0.0;
		}
		break;
	case 't':
		//candle animation
		candleAnimationSwitch = candleAnimationSwitch ? false : true;
		if (!candleAnimationSwitch) {
			candleRotZ = 0.0;
			candleX = 0.0;
			newCandleX = 0.0;
			candleY = 0.0;
			newCandleY = 0.0;
			centerCandleY = 0.0;
			centerCandleYNew = 0.0;
			centerCandleRotZ = 0.0;
			lowerCenterCandleY = 0.0;
			lowerCenterCandleYNew = 0.0;
			lowerCenterCandleRotY = 0.0;
		}
		break;
	case 'y':
		//chandelier animation
		chandelierAnimationSwitch = chandelierAnimationSwitch ? false : true;
		if (!chandelierAnimationSwitch) {
			chandelierRotY = 0.0;
			chandelierTransY = 0.0;
			chandelierTransYNew = 0.0;
		}
		break;
	case 'u':
		//global animation
		globalAnimationSwitch = globalAnimationSwitch ? false : true;
		if (!globalAnimationSwitch) {
			///// stand /////
			standTransX = 0.0;
			standTransY = 0.0;
			standTransZ = 0.0;
			standTransXNew = 0.0;
			standTransYNew = 0.0;
			standTransZNew = 0.0;
			standRotX = 0.0;
			standRotY = 0.0;
			standRotZ = 0.0;
			///// teapot /////
			t = 0.0;
			teapotTransX = 0.0;
			teapotTransY = 0.0;
			teapotTransZ = 0.0;
			teapotTransXNew = 0.0;
			teapotTransYNew = 0.0;
			teapotTransZNew = 0.0;
			teapotRotX = 0.0;
			teapotRotY = 0.0;
			teapotRotZ = 0.0;
			///// featherdust /////
			featherdustT = 0.0;
			featherdustTNew = 0.0;
			featherdustTransX = 0.0;
			featherdustTransY = 0.0;
			featherdustTransZ = 0.0;
			featherdustTransXNew = 0.0;
			featherdustTransYNew = 0.0;
			featherdustTransZNew = 0.0;
			featherdustRotX = 0.0;
			featherdustRotY = 0.0;
			featherdustRotZ = 0.0;
			///// cup /////
			cupRotZ = 0.0;
			cupX = 0.0;
			newCupX = 0.0;
			cupY = 0.0;
			newCupY = 0.0;
			///// candle /////
			candleRotZ = 0.0;
			candleX = 0.0;
			newCandleX = 0.0;
			candleY = 0.0;
			newCandleY = 0.0;
			centerCandleY = 0.0;
			centerCandleYNew = 0.0;
			centerCandleRotZ = 0.0;
			lowerCenterCandleY = 0.0;
			lowerCenterCandleYNew = 0.0;
			lowerCenterCandleRotY = 0.0;
			///// chandelier /////
			chandelierRotY = 0.0;
			chandelierTransY = 0.0;
			chandelierTransYNew = 0.0;
		}
		break;
	case 'd':
		//top view
		if (frontView && !topView) {
			camera.moveY(2.0);
			camera.rotateX(-45);
			topView = true;
			frontView = false;
			sideView = false;
		}
		break;
	case 's':
		//side view
		if (frontView && !sideView) {
			camera.moveX(-3.0);
			camera.rotateY(42);
			topView = false;
			frontView = false;
			sideView = true;
		}
		break;
	case 'a':
		//front view
		if (!frontView) {
			camera.reset();
			topView = false;
			frontView = true;
			sideView = false;
		}
		break;
	case 'f':
		//camera animation
		cameraAnimationSwitch = cameraAnimationSwitch ? false : true;
		if (cameraAnimationSwitch == false) {
			camera.reset();
			counter = 3;
		}
		break;
	case 'i':
		//global reset
		temp = 0.0;
		///// stand /////
		standAnimationSwitch = false;
		standTransX = 0.0;
		standTransY = 0.0;
		standTransZ = 0.0;
		standTransXNew = 0.0;
		standTransYNew = 0.0;
		standTransZNew = 0.0;
		standRotX = 0.0;
		standRotY = 0.0;
		standRotZ = 0.0;
		///// teapot /////
		teapotAnimationSwitch = false;
		t = 0.0;
		teapotTransX = 0.0;
		teapotTransY = 0.0;
		teapotTransZ = 0.0;
		teapotTransXNew = 0.0;
		teapotTransYNew = 0.0;
		teapotTransZNew = 0.0;
		teapotRotX = 0.0;
		teapotRotY = 0.0;
		teapotRotZ = 0.0;
		///// featherdust /////
		featherdustAnimationSwitch = false;
		featherdustT = 0.0;
		featherdustTNew = 0.0;
		featherdustTransX = 0.0;
		featherdustTransY = 0.0;
		featherdustTransZ = 0.0;
		featherdustTransXNew = 0.0;
		featherdustTransYNew = 0.0;
		featherdustTransZNew = 0.0;
		featherdustRotX = 0.0;
		featherdustRotY = 0.0;
		featherdustRotZ = 0.0;
		///// cup /////
		cupAnimationSwitch = false;
		cupRotZ = 0.0;
		cupX = 0.0;
		newCupX = 0.0;
		cupY = 0.0;
		newCupY = 0.0;
		///// candle /////
		candleAnimationSwitch = false;
		candleRotZ = 0.0;
		candleX = 0.0;
		newCandleX = 0.0;
		candleY = 0.0;
		newCandleY = 0.0;
		centerCandleY = 0.0;
		centerCandleYNew = 0.0;
		centerCandleRotZ = 0.0;
		lowerCenterCandleY = 0.0;
		lowerCenterCandleYNew = 0.0;
		lowerCenterCandleRotY = 0.0;
		///// candle2 /////
		candleAnimationSwitch2 = false;
		candleT2 = 0.0;
		candleTransX2 = 0.0;
		candleTransZ2 = 0.0;
		candleScale2 = 1.0;
		candleScale2New = 1.0;
		candleTransX2New = 0.0;
		candleTransZ2New = 0.0;
		candleTransX2New2 = 0.0;
		candleTransZ2New2 = 0.0;
		///// chandelier /////
		chandelierAnimationSwitch = false;
		chandelierRotY = 0.0;
		chandelierTransY = 0.0;
		chandelierTransYNew = 0.0;
		///// chandelier2 /////
		chandelierAnimationSwitch2 = false;
		chandelierT2 = 0.0;
		chandelierTransX2 = 0.0;
		chandelierTransY2 = 0.0;
		chandelierScale2 = 1.0;
		chandelierScale2New = 1.0;
		///// global /////
		globalAnimationSwitch = false;
		topView = false;
		frontView = true;
		sideView = false;
		///// camera /////
		cameraAnimationSwitch = false;
		camera.reset();
		counter = 3;
		break;
	case 'o':
		//chandelier animation2
		if (!globalAnimationSwitch && !chandelierAnimationSwitch) {
			chandelierAnimationSwitch2 = chandelierAnimationSwitch2 ? false : true;
			if (chandelierAnimationSwitch2 == false) {
				chandelierT2 = 0.0;
				chandelierTransX2 = 0.0;
				chandelierTransY2 = 0.0;
				chandelierScale2 = 1.0;
				chandelierScale2New = 1.0;
			}
		}
		break;
	case 'p':
		//candle animation2
		if (!globalAnimationSwitch && !candleAnimationSwitch) {
			candleAnimationSwitch2 = candleAnimationSwitch2 ? false : true;
			if (candleAnimationSwitch2 == false) {
				candleT2 = 0.0;
				candleTransX2 = 0.0;
				candleTransZ2 = 0.0;
				candleScale2 = 1.0;
				candleScale2New = 1.0;
				candleTransX2New = 0.0;
				candleTransZ2New = 0.0;
				candleTransX2New2 = 0.0;
				candleTransZ2New2 = 0.0;
			}
		}
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("BeautyAndTheBeast");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(Keyboard);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}