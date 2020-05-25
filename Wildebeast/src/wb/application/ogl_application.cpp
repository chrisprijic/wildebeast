#include "wbpch.h"

#include "wb/application/application.h"
#ifdef WB_OGL
#include "wb/events/event_router.h"

#include <GL/glew.h>

namespace wb {
    Application::Application() {
        platform = Platform::Create();
        platform->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
        platform->Init();

        window = platform->NewWindow();

        graphicsContext = DeviceContext::Create(WB_DEVICECONTEXT_OPENGL, window);
        graphicsContext->Init();
        //graphicsContext->SetVSync(true);

		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

		f32 points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
		};

		u32 vbo = 0;
		glGenBuffers(1, &vbo);
		WB_ASSERT(vbo != 0, "VAO cannot be 0")(vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(f32), points, GL_STATIC_DRAW);

		vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		const char* vertex_shader =
			"#version 400\n"
			"in vec3 vp;"
			"uniform mat4 mvp;"
			"void main () {"
			"  gl_Position = mvp * vec4 (vp, 1.0);"
			"}";

		const char* fragment_shader =
			"#version 400\n"
			"out vec4 frag_colour;"
			"void main () {"
			"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
			"}";

		u32 vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, NULL);
		glCompileShader(vs);
		int params = -1;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
		if (GL_TRUE != params) {
			printf("ERROR: GL shader index %i did not compile\n", vs);
		}
		u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, NULL);
		glCompileShader(fs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
		if (GL_TRUE != params) {
			printf("ERROR: GL shader index %i did not compile\n", fs);
		}
		shader_programme = glCreateProgram();
		glAttachShader(shader_programme, fs);
		glAttachShader(shader_programme, vs);
		glLinkProgram(shader_programme);
		glGetProgramiv(shader_programme, GL_LINK_STATUS, &params);
		if (GL_TRUE != params) {
			printf(
				"ERROR: could not link shader program w/ GL index %u\n",
				shader_programme
			);
		}
		GLint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error before rendering: " << err << std::endl;
		}
		//--------------------------------------------

		glUseProgram(shader_programme);
		mvp_loc = glGetUniformLocation(shader_programme, "mvp");
		mvp = fmat4{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		t = 0;
    }


    Application::~Application() {}

    void Application::OnEvent(Event& e) {}

    void Application::onEvent(Event& e) {
        switch (e.Type) {
            case WB_EVENT_QUIT: {
                closeWindow();
            } break;
            default: {
                OnEvent(e);
            }
        }
    }

    void Application::closeWindow() {
        isRunning = false;
    }

    void Application::Run() {
		while (isRunning) {
			t++;
			platform->OnUpdate();

			glClearDepthf(1.0f);
			glClear(GL_DEPTH_BUFFER_BIT);
			f32 rgb[3] = { 1.0f, 0.0f, 0.0f };
			glClearBufferfv(GL_COLOR, 0, rgb);

			mvp.m41 = cos(t / 1000.0);
			mvp.m42 = sin(t / 1000.0);

			//--------------------------------------------
			glUseProgram(shader_programme);
			glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glPtr(mvp * ndc));
			glBindVertexArray(vao);
			// draw points 0-3 from the currently bound VAO with current in-use shader
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//--------------------------------------------
			std::cout << '.';
            graphicsContext->SwapBuffers();
        }
    }
}
#endif