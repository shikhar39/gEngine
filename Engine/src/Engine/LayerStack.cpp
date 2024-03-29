#include "egpch.h"
#include "LayerStack.h"

Engine::LayerStack::LayerStack()
{
	m_LayerInsert = m_Layers.begin();
}

Engine::LayerStack::~LayerStack()
{
	for (Layer* layer: m_Layers)
		delete layer;
}

void Engine::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_LayerInsert, layer);
}

void Engine::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
}

void Engine::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		m_LayerInsert--;
	}
}

void Engine::LayerStack::PophOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
	}
}
