#include <GLFW/glfw3.h>
#include <algorithm>

const int width = 600;
const int height = 600;

float* pixels = new float[width*height * 3];
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}
void drawline(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
		drawPixel(i, j, red, green, blue);
	}
}
void drawline2(const int& i0, const int& j0, const int& i1, const int&j1, const float& red, const float& green, const float& blue)
{
	for (int j = j0; j <= j1; j++)
	{
		const int i = (i1 - i0)*(j - j0) / (j1 - j0) + i0;
		drawPixel(i, j, red, green, blue);
	}
}
/*void drawcircle(const int& i0, const int& j0, const int& radius, const float&red, const float& green, const float& blue)
{
for (double i = 0; i < i0 + radius; i += 0.1)
{
for (double j = 0; j < j0 + radius; j += 0.1)
{
//if ( (i0 - i) * (i0 - i) + (j0 - j) * (j0 - j) > radius*radius)
if (radius* (radius - 1) < (i - radius)*(i - radius) + (j - radius)*(j - radius)
&& radius * (radius - 1) > (i - radius)*(i - radius) + (j - radius)*(j - radius))
drawPixel(i, j, red, green, blue);
}
}
}*/
void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);
	// drawing a line
	//TODO: anti-aliasing
	int i0 = 50, i1 = 200, ix;
	int j0 = 50, j1 = 50;
	float r, g, b;
	/*
	for (int j = 0; j < 150; j++)
	{
	r = 0; g = 0; b = 0;
	drawLine(i0, j0, i1, j1+j, r, g, b);
	}*/
	for (int j = 50; j < 300; j++)
	{

		for (int i = 400; i < 600; i++)
		{
			ix = i + j*width;
			if ((i - 450)*(i - 450) + (j - 200)*(j - 200) > 50 * 49
				&& (i - 450)*(i - 450) + (j - 200)*(j - 200) < 50 * 51)
			{
				pixels[ix * 3 + 0] = 255;
				pixels[ix * 3 + 1] = 0;
				pixels[ix * 3 + 2] = 0;
			}
		}
	}
}
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//바탕화면 흰색으로 채우기
		std::fill_n(pixels, width*height * 3, 1.0f);
		//굵은선 만들기
		drawline(100, 400, 200, 500, 0.0f, 1.0f, 0.0f);
		drawline(100, 401, 199, 500, 0.0f, 1.0f, 0.0f);
		drawline(101, 400, 200, 499, 0.0f, 1.0f, 0.0f);
		//사각형 만들기
		drawline(250, 400, 350, 400, 0.0f, 1.0f, 0.0f);
		drawline2(250, 400, 250, 500, 0.0f, 1.0f, 0.0f);
		drawline(250, 500, 350, 500, 0.0f, 1.0f, 0.0f);
		drawline2(350, 400, 350, 500, 0.0f, 1.0f, 0.0f);
		//사각형 안에 채우기
		for (int i0 = 400, i1 = 500, j0 = 400, j1 = 400; j0 < 500; j0++, j1++)
		{
			drawline(i0, j0, i1, j1, 0.0f, 0.5f, 0.5f);
		}
		//삼각형 그리기
		drawline(100, 150, 200, 150, 0.0f, 1.0f, 0.0f);
		drawline(100, 150, 150, 250, 0.0f, 1.0f, 0.0f);
		drawline(150, 250, 200, 150, 0.0f, 1.0f, 0.0f);
		//오각형 그리기
		drawline(280, 150, 330, 150, 0.0f, 1.0f, 0.0f);
		drawline(330, 150, 360, 200, 0.0f, 1.0f, 0.0f);
		drawline(305, 250, 360, 200, 0.0f, 1.0f, 0.0f);
		drawline(250, 200, 305, 250, 0.0f, 1.0f, 0.0f);
		drawline(250, 200, 280, 150, 0.0f, 1.0f, 0.0f);
		//원 그리기
		drawOnPixelBuffer();


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}