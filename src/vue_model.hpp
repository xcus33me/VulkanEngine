#pragma once

#include "vue_device.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// std
#include <vector>

namespace vue {
    class VueModel {
    public:

        struct Vertex {
            glm::vec2 position;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        VueModel(VueDevice& device, const std::vector<Vertex>& vertices);
        ~VueModel();

        VueModel(const VueModel&) = delete;
        VueModel& operator=(const VueModel&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);
    
    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);

        VueDevice& vueDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}