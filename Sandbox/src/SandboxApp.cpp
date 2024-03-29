#include "Engine.h"



class ExampleLayer : public Engine::Layer {
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override {
		if (Engine::Input::IsKeyPressed(EG_KEY_TAB)) {
			EG_INFO("{0} poll");
		}
	}

	void OnEvent(Engine::Event& event) override {
		if (event.GetEventType() == Engine::EventType::KeyPressed) {

			Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == EG_KEY_TAB) {
				EG_INFO("{0} event", e.GetKeyCode());
			}
			EG_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};


class Sandbox : public Engine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Engine::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Engine::Application* Engine::CreateApplication() {
	return new Sandbox();
}