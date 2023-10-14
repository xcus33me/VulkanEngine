#include "lve_pipeline.hpp"

#include <fstream>
#include <exception>
#include <iostream>

#ifndef ENGINE_DIR
#define ENGINE_DIR "../"
#endif

namespace lve {

    LvePipeline::LvePipeline(
        LveDevice& device, 
        const std::string& vertFilepath, 
        const std::string& fragFilepath,
        const PipelineConfigInfo& configInfo)
         : lveDevice{device} {
            createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
        }

    std::vector<char> LvePipeline::readFile(const std::string& filepath) {
        std::string enginePath = ENGINE_DIR + filepath;
        std::ifstream file{enginePath, std::ios::ate | std::ios::binary};
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filepath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }

    void LvePipeline::createGraphicsPipeline(
                const std::string vertFilepath, 
                const std::string fragFilepath,
                const PipelineConfigInfo& configInfo) {
        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << "\n";
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << "\n";
    }

    void LvePipeline::createShaderModule(std::vector<char>& code, VkShaderModule* shaderModule) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        if (vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module");
        }
    }

    PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }
}