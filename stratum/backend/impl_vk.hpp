#ifndef IMPL_VK_HPP
#define IMPL_VK_HPP
#include <strata/backend/implgl.hpp>
#include <strata/modules.hpp>
#ifdef IMPL_ANDROID
#include <android/../vk/vulkan.hpp>
#include <android/../vk/vulkan_core.hpp>
#elif
#include <lib/vk/vulkan.h>
#include <lib/vk/vulkan_core.h>

#endif

#define GET_VK_FORMAT(image_form) 


class DescriptorAllocatorSets {
    
};
class Descriptor {

};
class vk_impl : public gl_impl  {
    public:
    bool nv = 0 ; // Takes prioriy ext; // else KHRl
    int size_t curdev;
    VkInstance instance ;
    std::vector<VkPhysicalDevice> physdev;
    VkPhysicalDevice pdevice;
    VkDevice dev;


void instance_set_up(app_info info) {
    // Step 1: Fill out application info
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = info.name;
    appInfo.applicationVersion = info.ver;
    appInfo.pEngineName = info.engname;
    appInfo.engineVersion = info.engver;
    appInfo.apiVersion = VK_API_VERSION_1_2;
    // Step 2: Specify required extensions
    const char** glfwExtensions = vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, nullptr);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // For debugging

    // Step 3: Specify validation layers (if debugging)
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    // Check if validation layers are supported
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            throw std::runtime_error("Validation layer not available!");
        }
    }

    // Step 4: Create the instance
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    this->inst= instance;
};
void set_up_dev(){
     // Enumerate physical devices
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }
    this->physdev.resize(deviceCount);
    vkEnumeratePhysicalDevices(this->instance, &deviceCount, this->physdev.data());

    this->pdevice = this->physdev[0]; // Select the first device

    // Query queue family properties
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(this->pdevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(this->pdevice, &queueFamilyCount, queueFamilies.data());

    // Find a queue family that supports graphics
    graphicsQueueFamilyIndex = -1;
    for (int i = 0; i < queueFamilies.size(); i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphicsQueueFamilyIndex = i;
            break;
        };
    };

    if (graphicsQueueFamilyIndex == -1) {
        throw std::runtime_error("Failed to find a graphics queue family!");
    };

    // Create the logical device
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeaturesEnabled{};
    deviceFeaturesEnabled.geometryShader = VK_TRUE;
    

    std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.pEnabledFeatures = &deviceFeaturesEnabled;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (vkCreateDevice(this->pdevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device!");
    }

    // Retrieve the graphics queue
    vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &graphicsQueue);

};

// VK_BUFFER_USAGE_TRANSFER_SRC_BIT
// VK_BUFFER_USAGE_TRANSFER_DST_BIT
// VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT
// VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT
// VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT
// VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
// VK_BUFFER_USAGE_INDEX_BUFFER_BIT
// VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
// VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT
// VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT
// VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR
// VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR
// VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT
// VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT
// VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT
// VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR
// VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR
// VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR



constexpr VkFormat get_format(image_formats fm){
    switch(fm){
image_formats::rgba32f         :{return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;}; 
image_formats::rgba16f         :{return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;};
image_formats::rg32f           :{return VkFormat::VK_FORMAT_R32G32_SFLOAT;};
image_formats::rg16f           :{return VkFormat::VK_FORMAT_R16G16_SFLOAT;};
image_formats::r11f_g11f_b10f  :{return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;};
image_formats::r32f            :{return VkFormat::VK_FORMAT_R32_SFLOAT;};
image_formats::r16f            :{return VkFormat::VK_FORMAT_R16_SFLOAT;};
image_formats::rgba16          :{return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;};
image_formats::rgb10_a2        :{return VkFormat::VK_FORMAT_A2R10G10B10_SNORM_PACK32;};
image_formats::rgba8           :{return VkFormat::VK_FORMAT_R8G8B8A8_SRGB;};
image_formats::rg16            :{return VkFormat::VK_FORMAT_R16G16_SNORM;};
image_formats::rg8             :{return VkFormat::VK_FORMAT_R8G8_SNORM;};
image_formats::r16             :{return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;};
image_formats::r8              :{return VkFormat::VK_FORMAT_R8_SNORM;};
image_formats::rgba16_snorm    :{return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;};
image_formats::rgba8_snorm     :{return VkFormat::VK_FORMAT_R8G8B8A8_SNORM;};
image_formats::rg16_snorm      :{return VkFormat::VK_FORMAT_R16G16_SNORM;};
image_formats::rg8_snorm       :{return VkFormat::VK_FORMAT_R8G8_SNORM;};
image_formats::r16_snorm       :{return VkFormat::VK_FORMAT_R16_SNORM;};
image_formats::r8_snorm        :{return VkFormat::VK_FORMAT_R8_SNORM;};
image_formats::rgba32          :{return VkFormat::VK_FORMAT_R32G32B32A32_SINT;};
image_formats::rgba16          :{return VkFormat::VK_FORMAT_R16G16B16A16_SINT;};
image_formats::rgba8           :{return VkFormat::VK_FORMAT_R8G8B8A8_SINT;};
image_formats::rg32            :{return VkFormat::VK_FORMAT_R32G32_SINT;};
image_formats::rg16            :{return VkFormat::VK_FORMAT_R16G16_SINT;};
image_formats::rg8             :{return VkFormat::VK_FORMAT_R8G8_SINT;};
image_formats::r32i            :{return VkFormat::VK_FORMAT_R32_SINT;};
image_formats::r16i            :{return VkFormat::VK_FORMAT_R16_SINT;};
image_formats::r8i             :{return VkFormat::VK_FORMAT_R8_SINT;};
image_formats::rgba32          :{return VkFormat::VK_FORMAT_R32G32B32A32_UINT;};
image_formats::rgba16          :{return VkFormat::VK_FORMAT_R16G16B16A16_UINT;};
image_formats::rgb10_a2ui      :{return VkFormat::VK_FORMAT_A2R10G10B10_UINT_PACK32;};
image_formats::rgba8           :{return VkFormat::VK_FORMAT_R8G8B8A8_UINT;};
image_formats::rg32            :{return VkFormat::VK_FORMAT_R32G32B32_UINT;};
image_formats::rg16            :{return VkFormat::VK_FORMAT_R16G16B16_UINT;};
image_formats::rg8             :{return VkFormat::VK_FORMAT_R8G8B8_UINT;};
image_formats::r32             :{return VkFormat::VK_FORMAT_R32_UINT;};
image_formats::r16             :{return VkFormat::VK_FORMAT_R16_UINT;};
image_formats::r8              :{return VkFormat::VK_FORMAT_R8_UINT;};
    };
};

constexpr VkPrimitiveTopology(TopologyPrimitive TP){
    switch(TP){
case TopologyPrimitive::POINT_LIST : {return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;}
case TopologyPrimitive::LINE_LIST : {return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;}
case TopologyPrimitive::LINE_STRIP : {return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;}
case TopologyPrimitive::TRIANGLE_LIST : {return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;}
case TopologyPrimitive::TRIANGLE_STRIP : {return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;}
case TopologyPrimitive::TRIANGLE_FAN : {return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;}
case TopologyPrimitive::LINE_LIST_WITH_ADJACENCY : {return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;}
case TopologyPrimitive::LINE_STRIP_WITH_ADJACENCY : {return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;}
case TopologyPrimitive::TRIANGLE_LIST_WITH_ADJACENCY : {return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;}
case TopologyPrimitive::TRIANGLE_STRIP_WITH_ADJACENCY : {return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;}
case TopologyPrimitive::PATCH_LIST : {return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;}
};
}
constexpr VkSurfaceTransformFlagBitsKHR get_transform(transform::image s){
    switch(s){
case none:  {return VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;};
case rotate90:  {return VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR;};
case rotate180:  {return VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR;};
case roate270:  {return VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR;};
case mirror:  {return VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR;};
case mirror_rotate90:  {return VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR;};
case mirror_rotate180:  {return VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR;};
case mirror_roate270:  {return VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR;};};};

VkResult create_image2d( image im){
VkImageCreateInfo imageCreateInfo{};
imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
imageCreateInfo.imageType = (im.dim);
imageCreateInfo.format = get_vk_format(s); // Use the format
imageCreateInfo.extent.width = {im.w,im.h, im.depth };
imageCreateInfo.mipLevels = im.miplevels;
imageCreateInfo.arrayLayers = i.arrlayers;
imageCreateInfo.samples = im.sample;
imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
imageCreateInfo.usage = im.usage;                                                                   

imageCreateInfo.sharingMode = im.sharing==true?VK_SHARING_MODE_CONCURRENT:VK_SHARING_MODE_EXCLUSIVE;  // Exclusive access (one queue family)
imageCreateInfo.queueFamilyIndexCount = 0;
imageCreateInfo.pQueueFamilyIndices = nullptr;
imageCreateInfo.preTransform = VK_TRANSFORM_IDENTITY_BIT_KHR;  
imageCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;  // Opaque alpha
imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;  // Initial layout

VkImage image;
VkResult result = vkCreateImage(device, &imageCreateInfo, nullptr, &image);
if (result != VK_SUCCESS) {
    std::cerr << "Failed to create image!" << std::endl;
}
};
void create_image2d_cube_map(image_formats s ,size_t x, size_t y)


void ubo(void* buffer, size_t bufsize){
const VkDeviceSize bufferSize = bufsize;
VkBufferCreateInfo bufferInfo{};
bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
bufferInfo.size = bufferSize;
bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

VkBuffer unibuffer;

if (vkCreateBuffer(this->device[device_index], &bufferInfo, nullptr, &unibuffer) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create SSBO buffer!");
};
// Allocate memory for the buffer
VkMemoryRequirements memRequirements;
vkGetBufferMemoryRequirements(this->device[device_index], unibuffer, &memRequirements);

VkMemoryAllocateInfo allocInfo{};
allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
allocInfo.allocationSize = memRequirements.size;
allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits,
                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                           VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

VkDeviceMemory ssboMemory;
if (vkAllocateMemory(this->device[device_index], &allocInfo, nullptr, &ssboMemory) != VK_SUCCESS) {
    throw std::runtime_error("Failed to allocate SSBO memory!");
}

// Bind the memory to the buffer
vkBindBufferMemory(this->device[device_index], unibuffer, ssboMemory, 0);


};
int ssbo(void* buffer, size_t strcts ){
// Buffer size
const VkDeviceSize bufferSize = sizeof(strcts); 

// Create the buffer
VkBufferCreateInfo bufferInfo{};
bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
bufferInfo.size = bufferSize;
bufferInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
bufferInfo.sharingMode = concurrent?VK_SHARING_MODE_CONCURRENT:VK_SHARING_MODE_EXCLUSIVE;

VkBuffer ssboBuffer;
if (vkCreateBuffer(this->device[device_index], &bufferInfo, nullptr, &ssboBuffer) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create SSBO buffer!");
};
// Allocate memory for the buffer
VkMemoryRequirements memRequirements;
vkGetBufferMemoryRequirements(this->device[device_index], ssboBuffer, &memRequirements);

VkMemoryAllocateInfo allocInfo{};
allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
allocInfo.allocationSize = memRequirements.size;
allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits,
                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                           VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

VkDeviceMemory ssboMemory;
if (vkAllocateMemory(this->device[device_index], &allocInfo, nullptr, &ssboMemory) != VK_SUCCESS) {
    throw std::runtime_error("Failed to allocate SSBO memory!");
}

// Bind the memory to the buffer
vkBindBufferMemory(this->device[device_index], ssboBuffer, ssboMemory, 0);
vkMapMemory(device, ssboMemory, 0, bufferSize, 0, &buffer);
memcpy(buffer, data_ref, bufferSize);
};



void unmap_ssbo(){
vkUnmapMemory(this->device_index[index_dev],this->ssbo_mem_index[index_ssbomem]);
};

void updateUBO();
// Unuse shader module flags
// VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI
// VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI

constexpr VkShaderStageFlagBits getShaderType(shader_type STAGE){
    switch(STAGE){
        shader_type::all :{return VkShaderStageFlagBits::VK_SHADER_STAGE_ALL;}
        shader_type::gr :{return VkShaderStageFlagBits::VK_SHADER_STAGE_ALL_GRAPHICS;}
        shader_type::vert :{return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;}
        shader_type::frag :{return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;}
        shader_type::geom :{return VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT;}
        shader_type::tesc :{return VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;}
        shader_type::tese :{return VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;}
        shader_type::comp :{return VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;}
        shader_type::task :{return VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_EXT;}
        shader_type::mesh :{return VkShaderStageFlagBits::VK_SHADER_STAGE_MESH_BIT_EXT;}
        shader_type::rgen :{return VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_KHR;}
        shader_type::rint :{return VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_KHR;}
        shader_type::rahit :{return VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_KHR;}
        shader_type::rchit :{return VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;}
        shader_type::rmiss :{return VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_KHR;}
        shader_type::rcall :{return VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_KHR;}
    }
};

int shaderModule(shaderModule* module,VkShaderStageFlagBits STAGE){
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = module->size;
    createInfo.pCode = reinterpret_cast<const uint32_t*>(module->code);
    VkShaderModule shaderModule;
if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create shader module!");
}
    VkPipelineShaderStageCreateInfo shaderStageInfo{};
    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.stage = STAGE ;
    shaderStageInfo.module = shaderModule ;
    shaderStageInfo.pName = module->entry_point;

    if(module->unib){

    };
    if(module->shab){
        this->ssbo(module,)
    };
    return 
};
int shaderModule(shaderModule* module, shader_type STAGE){
    shaderModule(module,getShaderType(STAGE));
};


int grModule(shaderModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_ALL_GRAPHICS);
};
int glslModule(shaderModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_ALL);
};
int vertModule(vertModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT);};
int fragModule(fragModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT);};
int geomModule(geomModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT);};
int tescModule(tescModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);};
int teseModule(teseModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);};
int compModule(compModule* module){
    this->shaderModule(module,VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT);
    VkComputePipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    pipelineInfo.stage = shaderStageInfo;              // Shader stage info
    pipelineInfo.layout = pipelineLayout;              // Pipeline layout
    if()
};
int taskModule(taskModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_EXT);};
int meshModule(meshModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_MESH_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_MESH_BIT_EXT);};
int rgenModule(rgenModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_NV: VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_KHR);
};
int rintModule(rintModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_KHR);};
int rahitModule(rahitModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_KHR);};
int rchitModule(rchitModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR);};
int rmissModule(rmissModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_KHR);};
int rcallModule(rcallModule* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_KHR);};


void descriptor_pool(){

};
virtual void descriptors(T* shader ){
    vkCreateDescriptorSetLayout(){

    };
};


};