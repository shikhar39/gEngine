#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv) {
	printf("Welcome to the new game engine\n");
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#endif // EG_PLATFORM_WINDOWS
