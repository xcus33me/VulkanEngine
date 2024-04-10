# VulkanEngine
Simple educational 3D engine based on VulkanAPI
![214](https://github.com/xcus33me/VulkanEngine/assets/103111612/e635cf82-2fb8-4031-a0b1-4faf617eb886)
___
##Building
###For windows:
- Install VulkanSDK https://www.vulkan.org/tools#download-these-essential-development-tools
- Change the path to VulkanSDK in the .env.cmake file
- In the compile.bat file, change the path to glslc.exe, which is located at C:\VulkanSDK\(version)\Bin\glslc.exe folder
- Rebuild CMakeLists.txt file

###For Linux:
- Delete .env.cmake file
- Use "./linuxBuild.sh to build the project
