#pragma once
#include <strata/backend/implgl.hpp>
#include <strata/backend/modules.hpp>
#include <lib/vk/vulkan.h>
#include <lib/vk/vulkan_core.h>
class DescriptorAllocatorSets {
    
};
class vk_impl  {
    public:
    bool nv; // TAkes prioriy over ext else 
    // bool ext; // else KHRl
    int size_t curdev;
    std::vector<VkDevice> device,
  
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
void ssbo(void* buffer, size_t strcts ){
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


void ssbo(shaderModule* module){this->ssbo(module,false);};
};


void unmap_ssbo(){
vkUnmapMemory(this->device_index[index_dev],this->ssbo_mem_index[index_ssbomem]);
};

void updateUBO();
// Unuse shader module flags
// VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI
// VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI
int shaderModule(shaderModule* module, int STAGE){
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
int grModule(shaderModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_ALL_GRAPHICS);
};
int glslModule(shaderModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_ALL);
};
int vertModule(vertModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_VERTEX_BIT);};
int fragModule(fragModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_FRAGMENT_BIT);};
int geomModule(geomModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_GEOMETRY_BIT);};
int tescModule(tescModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);};
int teseModule(teseModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);};
int compModule(compModule* module){
    this->shaderModule(module,VK_SHADER_STAGE_COMPUTE_BIT);
    VkComputePipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    pipelineInfo.stage = shaderStageInfo;              // Shader stage info
    pipelineInfo.layout = pipelineLayout;              // Pipeline layout
    if()
};
int taskModule(taskModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_TASK_BIT_NV:VK_SHADER_STAGE_TASK_BIT_EXT);};
int meshModule(meshModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_MESH_BIT_NV:VK_SHADER_STAGE_MESH_BIT_EXT);};
int rgenModule(rgenModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_RAYGEN_BIT_NV: VK_SHADER_STAGE_RAYGEN_BIT_KHR);
};
int rintModule(rintModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_INTERSECTION_BIT_NV:VK_SHADER_STAGE_INTERSECTION_BIT_KHR);};
int rahitModule(rahitModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_ANY_HIT_BIT_NV:VK_SHADER_STAGE_ANY_HIT_BIT_KHR);};
int rchitModule(rchitModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV:VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR);};
int rmissModule(rmissModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_MISS_BIT_NV:VK_SHADER_STAGE_MISS_BIT_KHR);};
int rcallModule(rcallModule* module){
    this->shaderModule(module,(this->nv)?VK_SHADER_STAGE_CALLABLE_BIT_NV:VK_SHADER_STAGE_CALLABLE_BIT_KHR);};
virtual T* shader(T shader);

void descriptor_pool(){

};
virtual void descriptors(T* shader ){
    vkCreateDescriptorSetLayout(){

    };
};


};