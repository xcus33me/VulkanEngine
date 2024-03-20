#pragma once

#include "vue_device.hpp"

// std
#include <string>
#include <vector>

namespace vue {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class VuePipeline {
        public:
            VuePipeline(
                VueDevice& device, 
                const std::string& vertFilepath, 
                const std::string& fragFilepath,
                const PipelineConfigInfo& configInfo);
            ~VuePipeline();

            VuePipeline(const VuePipeline&) = delete;
            void operator=(const VuePipeline&) = delete;

            static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height); 
    
        private:
            static std::vector<char> readFile(const std::string& filepath);

            void createGraphicsPipeline(
                const std::string vertFilepath, 
                const std::string fragFilepath,
                const PipelineConfigInfo& configInfo);

            void createShaderModule(std::vector<char>& code, VkShaderModule* shaderModule);

            VueDevice& vueDevice;
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;
    };
}