#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv) {
	Engine::Log::Init();
	EG_CORE_WARN("Initialised Logger!");
	int a = BIT(3);
	EG_INFO("Hello, I am App:) var a = {0}", a);

	auto app = Engine::CreateApplication();
	app->Run();
	EG_INFO("Closing the app");
	delete app;
}
#endif // EG_PLATFORM_WINDOWS
