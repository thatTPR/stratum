#ifndef IMPL_VK_HPP
#define IMPL_VK_HPP
#include <strata/backend/implgl.hpp>
#include <strata/modules.hpp>
#ifdef IMPL_ANDROID
#include <android/vk/vulkan.hpp>
#include <android/vk/vulkan_core.hpp>
#elif
#include <lib/vk/vulkan.h>
#include <lib/vk/vulkan_core.h>
#endif

#define GET_VK_FORMAT(image_form) 
constexpr VkShaderStageFlagBits getShaderType(mod::shader_type STAGE){
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


constexpr VkFormat get_format(mod::image_formats fm){
    switch(fm){
mod::image_formats::rgba32f         :{return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;}; 
mod::image_formats::rgba16f         :{return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;};
mod::image_formats::rg32f           :{return VkFormat::VK_FORMAT_R32G32_SFLOAT;};
mod::image_formats::rg16f           :{return VkFormat::VK_FORMAT_R16G16_SFLOAT;};
mod::image_formats::r11f_g11f_b10f  :{return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;};
mod::image_formats::r32f            :{return VkFormat::VK_FORMAT_R32_SFLOAT;};
mod::image_formats::r16f            :{return VkFormat::VK_FORMAT_R16_SFLOAT;};
mod::image_formats::rgba16          :{return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;};
mod::image_formats::rgb10_a2        :{return VkFormat::VK_FORMAT_A2R10G10B10_SNORM_PACK32;};
mod::image_formats::rgba8           :{return VkFormat::VK_FORMAT_R8G8B8A8_SRGB;};
mod::image_formats::rg16            :{return VkFormat::VK_FORMAT_R16G16_SNORM;};
mod::image_formats::rg8             :{return VkFormat::VK_FORMAT_R8G8_SNORM;};
mod::image_formats::r16             :{return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;};
mod::image_formats::r8              :{return VkFormat::VK_FORMAT_R8_SNORM;};
mod::image_formats::rgba16_snorm    :{return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;};
mod::image_formats::rgba8_snorm     :{return VkFormat::VK_FORMAT_R8G8B8A8_SNORM;};
mod::image_formats::rg16_snorm      :{return VkFormat::VK_FORMAT_R16G16_SNORM;};
mod::image_formats::rg8_snorm       :{return VkFormat::VK_FORMAT_R8G8_SNORM;};
mod::image_formats::r16_snorm       :{return VkFormat::VK_FORMAT_R16_SNORM;};
mod::image_formats::r8_snorm        :{return VkFormat::VK_FORMAT_R8_SNORM;};
mod::image_formats::rgba32          :{return VkFormat::VK_FORMAT_R32G32B32A32_SINT;};
mod::image_formats::rgba16          :{return VkFormat::VK_FORMAT_R16G16B16A16_SINT;};
mod::image_formats::rgba8           :{return VkFormat::VK_FORMAT_R8G8B8A8_SINT;};
mod::image_formats::rg32            :{return VkFormat::VK_FORMAT_R32G32_SINT;};
mod::image_formats::rg16            :{return VkFormat::VK_FORMAT_R16G16_SINT;};
mod::image_formats::rg8             :{return VkFormat::VK_FORMAT_R8G8_SINT;};
mod::image_formats::r32i            :{return VkFormat::VK_FORMAT_R32_SINT;};
mod::image_formats::r16i            :{return VkFormat::VK_FORMAT_R16_SINT;};
mod::image_formats::r8i             :{return VkFormat::VK_FORMAT_R8_SINT;};
mod::image_formats::rgba32          :{return VkFormat::VK_FORMAT_R32G32B32A32_UINT;};
mod::image_formats::rgba16          :{return VkFormat::VK_FORMAT_R16G16B16A16_UINT;};
mod::image_formats::rgb10_a2ui      :{return VkFormat::VK_FORMAT_A2R10G10B10_UINT_PACK32;};
mod::image_formats::rgba8           :{return VkFormat::VK_FORMAT_R8G8B8A8_UINT;};
mod::image_formats::rg32            :{return VkFormat::VK_FORMAT_R32G32B32_UINT;};
mod::image_formats::rg16            :{return VkFormat::VK_FORMAT_R16G16B16_UINT;};
mod::image_formats::rg8             :{return VkFormat::VK_FORMAT_R8G8B8_UINT;};
mod::image_formats::r32             :{return VkFormat::VK_FORMAT_R32_UINT;};
mod::image_formats::r16             :{return VkFormat::VK_FORMAT_R16_UINT;};
mod::image_formats::r8              :{return VkFormat::VK_FORMAT_R8_UINT;};

mod::image_formats::rgb32f          :{return VkFormat::VK_FORMAT_R32G32B32_SFLOAT };     
mod::image_formats::rgb16f          :{return VkFormat::VK_FORMAT_R16G16B16_SFLOAT };     
mod::image_formats::rgb16           :{return VkFormat::VK_FORMAT_R16G16B16_SFLOAT };    
mod::image_formats::rgb8            :{return VkFormat::VK_FORMAT_R8G8B8_SFLOAT };   
mod::image_formats::rgb16_snorm     :{return VkFormat::VK_FORMAT_R16G16B16_SNORM };          
mod::image_formats::rgb8_snorm      :{return VkFormat::VK_FORMAT_R8G8B8_SNORM };         
mod::image_formats::rgb32i          :{return VkFormat::VK_FORMAT_R32G32B32_SINT };     
mod::image_formats::rgb16i          :{return VkFormat::VK_FORMAT_R16G16B16_SINT };     
mod::image_formats::rgb8i           :{return VkFormat::VK_FORMAT_R8G8B8_SINT };    
mod::image_formats::rgb32ui         :{return VkFormat::VK_FORMAT_R32G32B32_UINT };      
mod::image_formats::rgb16ui         :{return VkFormat::VK_FORMAT_R16G16B16_UINT };      
mod::image_formats::rgb8ui          :{return VkFormat::VK_FORMAT_R8G8B8_UINT };     

    };
};

constexpr VkPrimitiveTopology getTopology(TopologyPrimitive TP){
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
constexpr VkSurfaceTransformFlagBitsKHR get_transform(mod::transform_image s){
    switch(s){
case mod::transform_image::none:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;};
case mod::transform_image::rotate90:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR;};
case mod::transform_image::rotate180:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR;};
case mod::transform_image::roate270:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR;};
case mod::transform_image::mirror:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR;};
case mod::transform_image::mirror_rotate90:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR;};
case mod::transform_image::mirror_rotate180:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR;};
case mod::transform_image::mirror_roate270:  {return VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR;};};};


constexpr VkDescriptorType getBindingType(modules::BindingType bt){
    switch constexpr (bt){
        case mod::BindingType::SAMPLER                  : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_SAMPLER;}     
        case mod::BindingType::COMBINED_IMAGE_SAMPLER   : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;}                    
        case mod::BindingType::SAMPLED_IMAGE            : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;}           
        case mod::BindingType::STORAGE_IMAGE            : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;}           
        case mod::BindingType::UNIFORM_TEXEL_BUFFER     : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;}                  
        case mod::BindingType::STORAGE_TEXEL_BUFFER     : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;}                  
        case mod::BindingType::UNIFORM_BUFFER           : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;}            
        case mod::BindingType::STORAGE_BUFFER           : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;}            
        case mod::BindingType::UNIFORM_BUFFER_DYNAMIC   : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;}                    
        case mod::BindingType::STORAGE_BUFFER_DYNAMIC   : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;}                    
        case mod::BindingType::INPUT_ATTACHMENT         : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;}              
        case mod::BindingType::INLINE_UNIFORM_BLOCK     : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK;}                  
        case mod::BindingType::ACCELERATION_STRUCTURE   : {return VkDescriptorType::VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE;}                    
    };
}


constexpr VkImageUsageFlagBits get_image_usage(mod::image_usage iu){
switch constexpr(iu)
{
    case mod::image_usage::TRANSFER_SRC_BIT             :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT;}      
    case mod::image_usage::TRANSFER_DST_BIT             :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT;}      
    case mod::image_usage::SAMPLED_BIT                  :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_SAMPLED_BIT;} 
    case mod::image_usage::STORAGE_BIT                  :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_STORAGE_BIT;} 
    case mod::image_usage::COLOR_ATTACHMENT_BIT         :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;}          
    case mod::image_usage::DEPTH_STENCIL_ATTACHMENT_BIT :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;}                  
    case mod::image_usage::TRANSIENT_ATTACHMENT_BIT     :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;}              
    case mod::image_usage::INPUT_ATTACHMENT_BIT         :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;}          
    case mod::image_usage::VIDEO_DECODE_DST_BIT         :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR;}          
    case mod::image_usage::VIDEO_DECODE_SRC_BIT         :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR;}          
    case mod::image_usage::VIDEO_DECODE_DPB_BIT         :{return VkImageUsageFlagBits::VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;}          
}
};

constexpr VkDescriptorType getDescriptor(mod::BindingType bt){
    switch constexpr (bt){
        case mod::BindingType::SAMPLER :{return VK_DESCRIPTOR_TYPE_SAMPLER;}
        case mod::BindingType::COMBINED_IMAGE_SAMPLER :{return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;}
        case mod::BindingType::SAMPLED_IMAGE :{return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;}
        case mod::BindingType::STORAGE_IMAGE :{return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;}
        case mod::BindingType::UNIFORM_TEXEL_BUFFER :{return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;}
        case mod::BindingType::STORAGE_TEXEL_BUFFER :{return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;}
        case mod::BindingType::UNIFORM_BUFFER :{return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;}
        case mod::BindingType::STORAGE_BUFFER :{return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;}
        case mod::BindingType::UNIFORM_BUFFER_DYNAMIC :{return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;}
        case mod::BindingType::STORAGE_BUFFER_DYNAMIC :{return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;}
        case mod::BindingType::INPUT_ATTACHMENT :{return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;}
        case mod::BindingType::INLINE_UNIFORM_BLOCK :{return VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK;}
        case mod::BindingType::ACCELERATION_STRUCTURE :{return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;}
    }
}

template <>
class mod::Pipeline<VkPipeline> {
    pri::list<VkPipeline> pipelines;
};


template <typename... shadMods>
class vk_impl : public glimpl<shadMods...>  {
    public:
    using Pipelinety = VkPipeline;
    using instty = VkInstance;

    using Pipeline = mod::Pipeline<Pipelinety> ;


    using imageBuffer = VkImageBuffer ;
    bool nv = 0 ; // Takes prioriy ext; // else KHRl
    int size_t curdev;


    VkInstance instance ;
    std::vector<VkPhysicalDevice> physdev;
    VkPhysicalDevice pdevice;
    VkDevice curdev;


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


using imagety= VkImage ;
pri::list<imagety> imagePool;

pri::list<imagety>::iter create_image2d( mod::image2D& im, imageOpts opts = imageOpts()){
VkImageCreateInfo imageCreateInfo;
imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
imageCreateInfo.format = get_format(im.format);
imageCreateInfo.extent.width = im.width;
imageCreateInfo.extent.height = im.height;
if(opts.cubemap){
    imageCreateInfo.extent.depth = 6;
    imageCreateIfo.flags|=VK_IMAGE_VIEW_TYPE_CUBE ; 
}
imageCreateInfo.mipLevels = 1;
imageCreateInfo.arrayLayers = 1;
imageCreateInfo.sharingMode = im.sharing==true?VK_SHARING_MODE_CONCURRENT:VK_SHARING_MODE_EXCLUSIVE;  // Exclusive access (one queue family)
imageCreateInfo.queueFamilyIndexCount = 0;
imageCreateInfo.pQueueFamilyIndices = nullptr;
imageCreateInfo.preTransform = VK_TRANSFORM_IDENTITY_BIT_KHR;  
imageCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;  // Opaque alpha
imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;  // Initial layout
imageCreateInfo.usage = get_image_usage(opt.usage); 

VkImage image;
VkResult result = vkCreateImage(devcur, &imageCreateInfo, nullptr, &image);
if (result != VK_SUCCESS) {
    imagePool.push_back(image);
    return imagePool.rbegin() ;
    std::cerr << "Failed to create image!" << std::endl;
}
};
using memty =VkDeviceMemory ; 

void bind_image(pri::list<imagety>::iter imit,pri::list<memty>::iter memit){
    vkBindImageMemory(devcur,*imit,*memit,0) ;

    VkWriteDescriptorSet write{};
};



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

using shaderStageBits = VkShaderStageFlagBits; 
pri::list<VkShaderModule> shadMods;
template <modules::shader_type sty,typename buf,mod::BindType bt>
pri::list<VkShaderModule>::iter shaderModule(shaderModule<sty,buf,bt>* module,VkShaderStageFlagBits STAGE){
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = module->size;
    createInfo.pCode = reinterpret_cast<const uint32_t*>(module->code);
    VkShaderModule shaderModule;
if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create shader module!");
}
    shadMods.push_back(shaderModule);
    return shadMods.rbegin();
}

template <modules::shader_type sty,typename buf,mod::BindType bt>
void shaderStage(mod::shaderModule<sty,buf,bt>* module,pri::list<VkShaderModule>::iter it,size_t entryPt=0){
    VkPipelineShaderStageCreateInfo crinfo{};
    crinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    crinfo.stage = getShaderType(module->sty);
    crinfo.module = *it;
    crinfo.pName = module->entry_points[entryPt];
};
void pipelineStage(pri::list<VkShaderModule>::iter... it,pri::list<VkShaderModule>::iter... its){
    VkPipelineShaderStageCreateInfo shaderStages[]
};
template <modules::shader_type sty,typename buf,mod::BindingType bt>
bool shaderModule(mod::shaderModule<sty,buf,bt>* module, shader_type STAGE){
    shaderModule<sty,buf,bt>(module,getShaderType(STAGE));
};

template <typename buf,mod::BindType bt>
int grModule(mod::grModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::gr,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_ALL_GRAPHICS);};
template <typename buf,mod::BindType bt>
int allModule(mod::allModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::all,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_ALL);};
template <typename buf,mod::BindType bt>
int vertModule(mod::vertModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::vert,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT);};
template <typename buf,mod::BindType bt>
int fragModule(mod::fragModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::frag,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT);};
template <typename buf,mod::BindType bt>
int geomModule(mod::geomModuleM<buf,bt>* module){
    this->shaderModule<mod::shader_type::geom,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT);};
template <typename buf,mod::BindType bt>
int tescModule(tescModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::tesc,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);};
template <typename buf,mod::BindType bt>
int teseModule(teseModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::tese,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);};
template <typename buf,mod::BindType bt>
int compModule(compModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::comp,buf,bt>(module,VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT);};
template <typename buf,mod::BindType bt>
int taskModule(taskModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::task,buf,bt>(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_EXT);};
template <typename buf,mod::BindType bt>
int meshModule(meshModule<buf,bt>* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_MESH_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_MESH_BIT_EXT);};
template <typename buf,mod::BindType bt>
int rgenModule(rgenModule<buf,bt>* module){
    this->shaderModule(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_NV: VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_KHR);};
template <typename buf,mod::BindType bt>
int rintModule(rintModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::rint,buf,bt>(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_KHR);};
template <typename buf,mod::BindType bt>
int rahitModule(rahitModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::rahit,buf,bt>(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_KHR);};
template <typename buf,mod::BindType bt>
int rchitModule(rchitModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::rchit,buf,bt>(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR);};
template <typename buf,mod::BindType bt>
int rmissModule(rmissModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::rmiss,buf,bt>(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_KHR);};
template <typename buf,mod::BindType bt>
int rcallModule(rcallModule<buf,bt>* module){
    this->shaderModule<mod::shader_type::rcall,buf,bt>(module,(this->nv)?VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_NV:VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_KHR);};


void descriptors( ){
    vkCreateDescriptorSetLayout(devcur,);
};


};