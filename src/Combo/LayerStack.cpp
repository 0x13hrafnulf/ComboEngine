#include "LayerStack.h"

namespace Combo
{
    LayerStack::LayerStack()
    {

    }
    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_InsertLayerIndex, layer);
        ++m_InsertLayerIndex;
        layer->Attach();
    }
    void LayerStack::PushOverLay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->Attach();
    }
    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertLayerIndex, layer);
        if(it != m_Layers.end())
        {
            layer->Detach();
            m_Layers.erase(it);
            --m_InsertLayerIndex;
        }
    }
    void LayerStack::PopOverLay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertLayerIndex, overlay);
        if(it != m_Layers.end())
        {
            overlay->Detach();
            m_Layers.erase(it);
        }
    }
}