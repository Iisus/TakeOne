#include <GL/gl.h>
#include "Engine.h"
#include "Log.h"

int main(void)
{
	TakeOne::Engine engine(800, 600, "TakeOne");

	while (!engine.ShouldClose())
	{
		glClearColor(0.2f, 0.8f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		engine.Update();
	}

	return 0;
}