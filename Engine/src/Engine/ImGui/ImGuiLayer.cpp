#include "egpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Engine/Application.h"
#include <GLFW/glfw3.h>
#include "Engine/KeyCodes.h"

namespace Engine {
	ImGuiLayer::ImGuiLayer() 
		:Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = EG_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = EG_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = EG_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = EG_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = EG_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = EG_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = EG_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = EG_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = EG_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = EG_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = EG_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = EG_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = EG_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = EG_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = EG_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = EG_KEY_A;
		io.KeyMap[ImGuiKey_C] = EG_KEY_C;
		io.KeyMap[ImGuiKey_V] = EG_KEY_V;
		io.KeyMap[ImGuiKey_X] = EG_KEY_X;
		io.KeyMap[ImGuiKey_Y] = EG_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = EG_KEY_Z;
		
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate() {

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0 / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl =	io.KeysDown[EG_KEY_LEFT_CONTROL]	|| io.KeysDown[EG_KEY_RIGHT_CONTROL];
		io.KeyShift =	io.KeysDown[EG_KEY_LEFT_SHIFT]		|| io.KeysDown[EG_KEY_RIGHT_SHIFT];
		io.KeyAlt =		io.KeysDown[EG_KEY_LEFT_ALT]		|| io.KeysDown[EG_KEY_RIGHT_ALT];
		io.KeySuper =	io.KeysDown[EG_KEY_LEFT_SUPER]		|| io.KeysDown[EG_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		unsigned int c = e.GetKeyCode();
		if (c > 0 && c < 0x10000) {
			io.AddInputCharacter(c);
		}
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		return false;
	}

}