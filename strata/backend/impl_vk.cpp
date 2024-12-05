#pragma once
#include "impl.hpp"
#include <vulkan.h>
class DescriptorAllocatorSets {
    
};
template<typename T>
class vk_impl : public strata_impl<T> {
    public:
    VkDevice device;

virtual T* shader(T shader);

void descriptor_pool(){

};
virtual void descriptors(T* shader ){
    vkCreateDescriptorSetLayout(){

    };
};
template <typename T>
void load_ubo(T* UBOdata){

VkDeviceSize bufferSize = sizeof(UBOData);

// Create the uniform buffer
VkBufferCreateInfo bufferInfo{};
bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
bufferInfo.size = bufferSize;
bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

VkBuffer uniformBuffer;
vkCreateBuffer(device, &bufferInfo, nullptr, &uniformBuffer);

// Allocate memory for the buffer
VkMemoryRequirements memRequirements;
vkGetBufferMemoryRequirements(device, uniformBuffer, &memRequirements);

VkMemoryAllocateInfo allocInfo{};
allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
allocInfo.allocationSize = memRequirements.size;
allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, 
                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

VkDeviceMemory uniformBufferMemory;
vkAllocateMemory(device, &allocInfo, nullptr, &uniformBufferMemory);
vkBindBufferMemory(device, uniformBuffer, uniformBufferMemory, 0);

// Map memory to CPU-accessible pointer
void* data;
vkMapMemory(device, uniformBufferMemory, 0, bufferSize, 0, &data);


// Copy the data
memcpy(data, &ubo, sizeof(UBOData));
vkUnmapMemory(device, uniformBufferMemory);
};
template<typename T>
virtual void load_ssbo( T* SSBOdata){
    
};


};