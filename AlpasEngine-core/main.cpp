#include <time.h>

#include "src\utils\timer.h"

#include "src/graphics\batchrenderer2d.h"
#include "src/graphics\renderable2d.h"
#include "src/graphics\renderer2d.h"
#include "src\graphics\shader.h"
#include "src/graphics\simple2drenderer.h"
#include "src/graphics\sprite.h"
#include "src\graphics\texture.h"
#include "src/graphics\window.h"

#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src/graphics\layers\group.h"
#include "src/graphics\layers\tilelayer.h"

#include "src/maths\maths.h"

int main() 
{
	using namespace alpas;
	using namespace graphics;
	using namespace maths;
	
	Window window("Test", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;

	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	//TODO: there seems to be something wrong with the red and blue color from the textures.
	Texture* textures[] = 
	{
		new Texture("r.png"),
		new Texture("g.png"),
		new Texture("b.png")
	};

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}
	
	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		
		window.update();
		frames++;

		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	
	delete[] textures;

	return 0;
}
