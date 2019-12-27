#pragma once

#include <vector>

#include "Layer.h"

namespace Combo
{
    class LayerStack
    {
        public:
            LayerStack() = default;
            ~LayerStack();

            void PushLayer(Layer* layer);
            void PushOverLay(Layer* overlay);
            void PopLayer(Layer* layer);
            void PopOverLay(Layer* overlay);

            std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
            std::vector<Layer*>::iterator end() { return m_Layers.end(); }

        private:

            std::vector<Layer*> m_Layers;
            unsigned int m_InsertLayerIndex = 0;

    };
}