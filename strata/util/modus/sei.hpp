#pragma once

#include <cstdint>   // Necessary for uint32_t
#include <limits>    // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <vk/vulkan.h>
#include <vk_types.h>
#include <vk_initializers.h>

//bootstrap library
#include "VkBootstrap.h"

#include ""
#include "sfwgui/backends/sfwgui_impl_sdl2.h"
#include "sfwgui/backends/sfwgui_impl_vulkan.h"
#include <sfwgui/sfwgui.h>
#include "sfwgui/sfwgui_internal.h"

#include <thread>
#include <mutex>
#include <stdexcept>
#include <functional>
#include <vector>
#include <optional>
#include <set>
#include <map>
#include <algorithm>
#include <thread>
#include <execution>
#include <fstream>

using namespace std;


// TODO Transparent and diffusing windows
// Behaviour must be controlled in the widget definition
// Interface class , Derived classed needs to be able to provide appropiate setting references to app and save and read them to file in json format


typedef struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
} SwapchainSupportDetails;

typedef struct GraphicsPipelineSupportDetails {
    
};



typedef struct AppInitInfo {
    
    std::pair<uint, std::pair<uint, uint> >> 
    std::vector<SDL_DisplayEventID ; 
    
} AppInitInfo ;
AppInitInfo getAppInitInfo(){
    SDL_GetNumVideoDisplays() ; 
}


// Sutiable for simple selection menus
class simpleVkMenu {
    settings 
};


class swapChain {

};
class pipeline {

};
class subPipeline {

};


// Function pointer interface implementation
#include "sei_settings.hpp"

class sei
{
public:
  
    SDL_Window *window; // Primary window of application
    DisplayMode mode ; // 
    
#ifdef MUL_WINDOWS
    std::vector<secondary> windows;
#endif
    // void createWindowCustomBar(char* title , int x , int y, int w, int h ){
    //     SDL_CreateWindow(title, x,y,w,h , SDL_WINDOW)
    // }
    SfwGuiContext *GUIcontext = NULL;
    bool loopChange;
    bool SfwGuiActive;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    std::array<VkPhysicalDevice> physicalDevice = VK_NULL_HANDLE;
    std::array<>
    VkPhysicalDeviceProperties _gpuProperties;
    VkPhysicalDevice device;
    
    VkQueue graphicsQueue;
    VkQueue presentQueue;

    SwapChainSupportDetails swapChainSupport;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    std::vector<VkImageView> swapChainImageViews;

    VkExtent2D swapChainExtent;
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> pCommandBuffers;

    /

    bool show_main_menu_bar_context_menu  ; 
    std::vector<std::pair<bool, void (*)()>> mainMenuBarOptions
    virtual void init_mainMenuBarOptions(std::vector<std::pair<bool, bool (*)() > widgets){
        for( auto func : widgets) {
            this->mainMenuBar.push_back(func) ; 
        }
    }
    
    virtual void WindowBar(std::string contextText ,  ){ // Default Loads Icon and  
    #ifdef FULLSCREEN_WINDOWBAR
    
    #endif
        SfwGui::BeginMainMenuBar();
        SfwGui::Image();
        for( auto func : mainMenuBarOptions){
            if(func[1] == true ; ) {func[0]();}
        };

        SfwGui::Text(contextText) ;
        SfwGui::SameLine(SfwGui::GetWindowWidth() - 200);
        static char searchBuffer[256] = "";
        SfwGui::InputText("##Search", searchBuffer, IM_ARRAYSIZE(searchBuffer));

        if (SfwGui::Button("Search")) {
            // Perform search action
            // Implement your search logic here
        }

        SfwGui::EndMainMenuBar();
        };
    virtual void initWindow()
    {
        SDL_Init(SDL_INIT_VIDEO);
        this->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
    };
    virtual void initVulkan()
    {
        this->createInstance();
        this->setupDebugMessenger();
        this->createWindowSurface()
        this->pickPhysicalDevice();
        this->createLogicalDevice();

        this->createSwapChain();
        this->createImageViews();

        this->createRenderPass();       // TODO
        this->createGraphicsPipeline(); // TODO
        this->createFramebuffers();     // TODO
        this->createCommandPool();      // TODO
        this->createCommandBuffer();    // TODO
    };
    void initSEI()
    {

    }
    virtual void initSfwgui()
    {

        SfwGui::GetIO().ConfigFlags |= SfwGuiConfigFlags_ViewportsEnable;
        SFWGUI_CHECKVERSION();
        this->GUIcontext = SfwGui::CreateContext();
        SfwGui_ImplSDL2_InitForVulkan(this->window);
        SfwGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = this->instance;
        init_info.PhysicalDevice = this->physicalDevice;
        init_info.Device = this->device;
        init_info.QueueFamily = 0; // Adjust according to your setup
        init_info.Queue = this->graphicsQueue;
        init_info.PipelineCache = this->PipeLineCache;
        init_info.DescriptorPool = this->DescriptorPool;
        init_info.Allocator = nullptr;
        init_info.MinImageCount = 2;
        init_info.ImageCount = static_cast<uint32_t>(this->swapChainImages.size());
        init_info.CheckVkResultFn = [](VkResult result)
        {
            if (result != VK_SUCCESS)
            {
                throw std::runtime_error("SfwGui_ImplVulkan_Init failed");
            }
        };
        SfwGui_ImplVulkan_Init(&init_info, this->renderPass);
        recreateSwapChain(); // Ensure SfwGui resources are created for the initial swap chain
    };


    virtual void cleanup()
    {
        if (enableValidationLayers)
        {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        SfwGui_ImplVulkan_Shutdown();
        SfwGui_ImplSDL2_Shutdown();

        vkDestroyDevice(this->device, nullptr);
        vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
        vkDestroyInstance(this->instance, nullptr);

        SfwGui::DestroyContext(&this->GUIcontext);

        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    virtual void run()
    {
        this->initWindow();
        this->initVulkan();
        this->initImgui();
        this->main_loop();
        this->cleanup();
    }
    virtual void setAppIcon(char* path){ // Rendered 

    }
    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};
    // Vulkan instance creation

    virtual void createInstance()
    {
        // Application info (optional)
        this->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        this->appInfo.pApplicationName = APP_NAME;
        this->appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        this->appInfo.pEngineName = ENGINE_NAME;
        this->appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        this->appInfo.apiVersion = VK_API_VERSION_1_0;

        // Create instance info
        this->createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        this->createInfo.pApplicationInfo = &appInfo;

        // Enable validation layers (optional)

        // // SDL extension handling
        // auto extensions = getRequiredExtensions(); // FIXME
        // createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        // createInfo.ppEnabledExtensionNames = extensions.data();

        // Enable validation layers (optional)
        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        // Create Vulkan instance
        if (vkCreateInstance(&this->createInfo, nullptr, &this->instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Vulkan instance!");
        }
    }

    virtual VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
    {
        for (const auto &availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }
    virtual VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
    {
        for (const auto &availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }
    virtual VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }
        else
        {
            int width, height;
            SDL_GetWindowSizeInPixels(this->window, &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)};

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }
    virtual SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device)
    {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }
    virtual void createSwapChain()
    {
        this->swapChainSupport = querySwapChainSupport(this->physicalDevice);

        this->surfaceFormat = chooseSwapSurfaceFormat(this->swapChainSupport.formats);
        this->presentMode = chooseSwapPresentMode(this->swapChainSupport.presentModes);
        this->swapChainExtent = chooseSwapExtent(this->swapChainSupport.capabilities);

        uint32_t imageCount = this->swapChainSupport.capabilities.minImageCount + 1;
        if (this->swapChainSupport.capabilities.maxImageCount > 0 && imageCount > this->swapChainSupport.capabilities.maxImageCount)
        {
            imageCount = this->swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.oldSwapchain = this->SwapChain; // NULL when new
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = this->surface;
        createInfo.minImageCount = this->imageCount;
        createInfo.imageFormat = this->surfaceFormat.format;
        createInfo.imageColorSpace = this->surfaceFormat.colorSpace;
        createInfo.imageExtent = this->swapChainExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;     // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }

        createInfo.preTransform = this->swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(this->device, &createInfo, nullptr, &this->swapChain) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(this->device, this->swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(this->device, swapChain, &imageCount, swapChainImages.data());

        this->swapChainImageFormat = surfaceFormat.format;
        this->swapChainExtent = extent;

        // Create image views for each swap chain image
        swapChainImageViews.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++)
        {
            swapChainImageViews[i] = createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
        }
    }
    virtual void cleanupSwapChain()
    {
        for (auto framebuffer : this->swapChainFramebuffers)
        {
            vkDestroyFramebuffer(this->device, framebuffer, nullptr);
        }

        vkFreeCommandBuffers(this->device, this->commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        vkDestroyPipeline(this->device, this->graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(this->device, this->pipelineLayout, nullptr);
        vkDestroyRenderPass(this->device, this->renderPass, nullptr);

        for (auto imageView : this->swapChainImageViews)
        {
            vkDestroyImageView(this->device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(this->device, this->swapChain, nullptr);
    }
    virtual void recreateSwapChain()
    {
        vkDeviceWaitIdle(device);
        this->cleanupSwapChain();
        this->createSwapChain();
        this->createImageViews();
        this->createRenderPass();
        this->createGraphicsPipeline();
        this->createFramebuffers();
        this->createCommandBuffers();
    }
    virtual void createImageViews()
    {
        this->swapChainImageViews.resize(this->swapChainImages.size());
        for (size_t i = 0; i < this->swapChainImages.size(); i++)
        {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(this->device, &createInfo, nullptr, &this->swapChainImageViews[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }

    /*
    typedef enum VkShaderStageFlagBits {
        VK_SHADER_STAGE_VERTEX_BIT = 0x00000001,
        VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT = 0x00000002,
        VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT = 0x00000004,
        VK_SHADER_STAGE_GEOMETRY_BIT = 0x00000008,
        VK_SHADER_STAGE_FRAGMENT_BIT = 0x00000010,
        VK_SHADER_STAGE_COMPUTE_BIT = 0x00000020,
        VK_SHADER_STAGE_ALL_GRAPHICS = 0x0000001F,
        VK_SHADER_STAGE_ALL = 0x7FFFFFFF,
        VK_SHADER_STAGE_RAYGEN_BIT_KHR = 0x00000100,
        VK_SHADER_STAGE_ANY_HIT_BIT_KHR = 0x00000200,
        VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR = 0x00000400,
        VK_SHADER_STAGE_MISS_BIT_KHR = 0x00000800,
        VK_SHADER_STAGE_INTERSECTION_BIT_KHR = 0x00001000,
        VK_SHADER_STAGE_CALLABLE_BIT_KHR = 0x00002000,
        VK_SHADER_STAGE_TASK_BIT_EXT = 0x00000040,
        VK_SHADER_STAGE_MESH_BIT_EXT = 0x00000080,
        VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI = 0x00004000,
        VK_SHADER_STAGE_RAYGEN_BIT_NV = VK_SHADER_STAGE_RAYGEN_BIT_KHR,
        VK_SHADER_STAGE_ANY_HIT_BIT_NV = VK_SHADER_STAGE_ANY_HIT_BIT_KHR,
        VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
        VK_SHADER_STAGE_MISS_BIT_NV = VK_SHADER_STAGE_MISS_BIT_KHR,
        VK_SHADER_STAGE_INTERSECTION_BIT_NV = VK_SHADER_STAGE_INTERSECTION_BIT_KHR,
        VK_SHADER_STAGE_CALLABLE_BIT_NV = VK_SHADER_STAGE_CALLABLE_BIT_KHR,
        VK_SHADER_STAGE_TASK_BIT_NV = VK_SHADER_STAGE_TASK_BIT_EXT,
        VK_SHADER_STAGE_MESH_BIT_NV = VK_SHADER_STAGE_MESH_BIT_EXT,
        VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
    } VkShaderStageFlagBits;
    */
   // consteval , constinit , constexpr
   // 
    std::vector<char> readFileSPV(const std::string &filename)
    {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
    }
    VkShaderModule createShaderModule(const std::vector<char> &code)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());
        VkShaderModule shaderModule;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create shader module!");
        }
        return shaderModule;
    };
 
    virtual void createGraphicsPipeline(std::vector<VkShaderModule> modules )
    {
        const char* vertShaderCode = constexpr readFileSPV("shaders/vert.spv");
        const char* fragShaderCode = constexpr readFileSPV("shaders/frag.spv");

        VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
        VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

        for(auto const &i : modules){
            
        }

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        vkDestroyShaderModule(this->device, fragShaderModule, nullptr);
        vkDestroyShaderModule(this->device, vertShaderModule, nullptr);
    };
    
    std::vector<std::string> certShaders ; 
    // Allows producing of shaders
    virtual void produceGraphicsPipeline()
    {
        typedef std::vector<std::vector<char>> shaderCode;
        for (std::string i : this->certShaders)
        {
        };
        auto vertShaderCode = readFileSPV("shaders/vert.spv");
        auto fragShaderCode = readFileSPV("shaders/frag.spv");

        VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
        VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

        VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        vkDestroyShaderModule(this->device, fragShaderModule, nullptr);
        vkDestroyShaderModule(this->device, vertShaderModule, nullptr);
    };
    
    // Validation layers
    const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    // Debug messenger creation
    virtual void setupDebugMessenger()
    {
        if (!enableValidationLayers)
            return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to set up debug messenger!");
        }
    }
    // Vulkan surface creation
    virtual void createWindowSurface(VkSurfaceKHR* surface)
    {
        if (!SDL_Vulkan_CreateSurface(this->window, this->instance, &this->surface))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Vulkan surface creation failed: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to create SDL Vulkan surface");
        }
    }
    // Physical device selection
    virtual void pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, devices.data());
    
        for (const auto     &device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }
    // Logical device creation
    virtual void createLogicalDevice()
    {
        QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{}; // No specific features enabled for now

        // Logical device info
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pEnabledFeatures = &deviceFeatures;

        // Extensions
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        // Validation layers
        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        // Create logical device
        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &this->device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create logical device!");
        }

        // Get device queues
        vkGetDeviceQueue(this->device, indices.graphicsFamily.value(), 0, &this->graphicsQueue);
        vkGetDeviceQueue(this->device, indices.presentFamily.value(), 0, &this->presentQueue);
    }
    virtual void chooseMultipleLogicalDevices(){

    };
    // Queue families
    struct QueueFamilyIndices
    {

        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    // Check for queue families
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            // Check for graphics support
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
            }

            // Check for presentation support
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport)
            {
                indices.presentFamily = i;
            }

            if (indices.isComplete())
            {
                break;
            }

            i++;
        }

        return indices;
    }

    // Check device suitability
    bool isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);

        return indices.isComplete();
    };

    // Required device extensions
    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    // Check for required extensions
    bool checkDeviceExtensionSupport(VkPhysicalDevice device)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto &extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    };

    // Debug messenger creation
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    };

    // Debug messenger destruction
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    };

    // Debug callback function
    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData)
    {

        std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    };

    // Populate debug messenger create info
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
    };



     void wake(){

    };
    
    void sleep(){
        SDL_Event* ev; 
        while(SDL_PollEvent(ev)){
            if(ev->type == SDL_POLLSENTINEL)
                continue ; 
            else ;
            SDL_Delay(200) ; 
        }
        
    };

#ifdef APP_EVENT
    virtual void _quit(SDL_QuitEvent *qevent) { this->cleanup() ; }
    virtual void _app_terminating() { exit(EXIT_SUCCESS); }
    virtual void _app_lowmemory(void){};
    virtual void _app_willenterbackground() { return ; /*this->will_sleep();*/ };
    virtual void _app_didenterbackground(){this->sleep();} ;
    virtual void _app_willenterforeground(){this->will_wake() ;} ;
    virtual void _app_didenterforeground() {  return ; /*this->will_wake();*/ };
    virtual void _localechanged(){return ;} 
    virtual bool SDL_AppEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case SDL_QUIT: //           = 0x100, /**< User-requested quit */
        {
            this->_quit(event->quit) ;
            return true;
        };
            /* These application events have special meaning on iOS, see README-ios.md for details */
        case SDL_APP_TERMINATING, /**< The application is being terminated by the OS
                          Called on iOS in applicationWillTerminate()
                          Called on Android in onDestroy()
                     */
        {
        this->_APP_TERMINATING();
          return true;
        };
            case SDL_APP_LOWMEMORY: /**< The application is low on memory, free memory if possible.
                           Called on iOS in applicationDidReceiveMemoryWarning()
                           Called on Android in onLowMemory()
                      */
        {
            
            this->_app_lowmemory();
            return true;
        }
        case SDL_APP_WILLENTERBACKGROUND: /**< The application is about to enter the background
                                Called on iOS in applicationWillResignActive()
                                Called on Android in onPause()
                           */
        {
            this->_app_willenterbackground();
            return true;
        };
        case SDL_APP_DIDENTERBACKGROUND: /**< The application did enter the background and may not get CPU for some time
                                Called on iOS in applicationDidEnterBackground()
                                Called on Android in onPause()
                           */
        {
            this->_app_didenterbackground();
            return true;
        }
        case SDL_APP_WILLENTERFOREGROUND: /**< The application is about to enter the foreground
                                Called on iOS in applicationWillEnterForeground()
                                Called on Android in onResume()
                           */
        {
            this->_app_willenterforeground();
            return true;
        }
        case SDL_APP_DIDENTERFOREGROUND: /**< The application is now interactive
                                Called on iOS in applicationDidBecomeActive()
                                Called on Android in onResume()
                           */
        {
            this->_app_didenterforeground()
            return true;
        }
        case SDL_LOCALECHANGED: /**< The user's locale preferences have changed. */
        {
            this->_localechanged();
            return true;
        }
        }
    }
#endif
#ifdef DISPLAY_EVENT
    SDL_DisplayEvent _DISPLAYCONNECTED_FLAG = NULL;
    SDL_DisplayEvent _DISPLAYDISCONNECTED_FLAG = NULL;
    SDL_DisplayEvent _DISPLAYORIENTATION_FLAG = NULL;

#ifdef MUL_WINDOWS
    virtual void organiseWindows(SDL_DisplayEvent event) // TODO
    {
        std::map<int, SDL_Rect> displayMap;
        int num = SDL_GetNumVideoDisplays();
        for (int i = 0; i < num; i++)
        {
            displayMap.insert(std::pair<int, SDLRect>)
        };
        for (SDL_Window *window : this->windows)
        {
        };
    };
#endif
    bool organiseDisplayHandle(SDL_DisplayEvent event)
    {
#ifdef MUL_WINDOWS
#ifdef MUL_WINDOWS_DISPLAY_ASK
        bool show_dialog;
        SfwGui::Window
            SfwGui::Begin("Display Event", &show_dialog, SfwGuiWindowFlags_AlwaysAutoResize);
        SfwGui::Text(" Reorganize Secondary Windows? \n Enter for Yes, ESC for No");
        SfwGui::Separator();
        if (SfwGui::Button("Yes"))
        {
            organiseWindows(event);
            return true;
        };
        SfwGui::Separator();
        if (SfwGui::Button("No"))
        {
            return true;
        }
        SfwGui::End();
#endif
        organiseWindows();
#endif
        return false;
    }
    virtual void _displayconnected(SDL_DisplayEvent ev)
    {
        SDL_Log("A new display with id %d was connected", ev.display);
        if (this->organiseDisplayHandle(ev))
        {
            this->_DISPLAYCONNECTED_FLAG = NULL;
        }
    };
    virtual void _displaydisconnected(SDL_DisplayEvent ev)
    {
        SDL_Log("The display with id %d was disconnected", ev.display);
        if (this->organiseDisplayHandle(ev))
        {
            this->_DISPLAYDISCONNECTED_FLAG = NULL;
        }
    };
    virtual void _displayorientation(SDL_DisplayEvent ev)
    {
        SDL_Log("The orientation of display with id %d was changed", ev.display);
        if (this->organiseDisplayHandle(ev))
        {
            this->_DISPLAYORIENTATION_FLAG = NULL;
        }
    };
    virtual bool SDL_DisplayEvent(SDL_Event *event)
    {
        if (event->type == SDL_DISPLAYEVENT)
        {
            switch (event->display.event)
            {
            case SDL_DISPLAYEVENT_CONNECTED:
                this->_DISPLAYCONNECTED_ARG = event->display; // TODO
                this->_displayconnected(event->display);
                return 1;
            case SDL_DISPLAYEVENT_DISCONNECTED:
                this->_DISPLAYDISCONNECTED(event->display);
                this->_DISPLAYDISCONNECTED_FLAG = event->display;
                return 1;
            case SDL_DISPLAYEVENT_ORIENTATION:
                this->_DISPLAYORIENTATION(event->display);
                this->_DISPLAYORIENTATION_FLAG = event->display;
                return 1;
            }
        }
        if (this->_DISPLAYCONNECTED_ARG != NULL)
        {
            this->_displayconnected(this->_DISPLAYCONNECTED_ARG);
        };
        if (this->_DISPLAYDISCONNECTED_ARG != NULL)
        {
            this->_displaydisconnected(this->_DISPLAYDISCONNECTED_ARG);
        };
        if (this->_DISPLAYORIENTATION_ARG != NULL)
        {
            this->_displayorientation(this->_DISPLAYORIENTATION_ARG);
        };

    };
#endif
#ifdef WINDOW_EVENT
    virtual void _windowevent(SDL_WindowEvent ev){

    };
    virtual void _syswmevent(SDL_SysWMEvent ev){

    };
    SDL_WindowEvent _WINDOWEVENT_ARG = NULL;
    SDL_SysWMEvent _SYSWMEVENT_ARG = NULL;
    virtual bool SDL_WindowEvent(SDL_Event *event)
    {
        if (event->type == SDL_WINDOW_EVENT)
        {
            switch (event->type)
            {
            case:
                SDL_WINDOWEVENT
                {
                    this->_windowevent(event->window);
                    this->_WINDOWEVENT_ARG = this->window;
                    return true;
                } /**< Window state change */
            case:
                SDL_SYSWMEVENT
                {
                    this->_SYSWMEVENT_ARG = this->window;
                    this->_syswmevent(event->syswm);
                    return true;
                }
            }
        }


        if (this->_WINDOWEVENT_ARG != NULL)
        {
                        this->_windowevent(this->_WINDOWEVENT_ARG);
        };
        if (this->_SYSWMEVENT_ARG != NULL)
        {
                        this->_syswmevent(this->_SYSWMEVENT_ARG);
        }
    };
#endif
#ifdef KEY_EVENT // TODO
    std::vector<SDL_Keysym>  keys ;

    #ifdef KEY_SHORTCUTS
    #ifdef KEY_COMBOS
    bool possibleCombo ; // Set to true if pressed
    std::array<std::map<std::tuple<SDL_Keycode>, void (*action)() >, int>> combos ; 
    #ifdef PLUGINS
     std::array<std::tuple<SDL_Keycode>, int>> getKeyCombosExt(){
        
    };
    #endif
     std::array<std::tuple<SDL_Keycode>, int>> getKeyCombos(){

    }
    void assignKeyCombos(){
        getKeyCombos(){

        };
    }; 
    
    #ifdef KEY_CHORDS // Supports Ctrl+Key , Key Combo type shortcuts
    std::array<std::array<SDL_Keycode>> chordStarts ;
    std::array<std::tuple<std::array<SDL_Keycode>, std::array<SDL_keycode>>>>
    void shortcutChord(){ // 

    };
    #endif
    #endif
    #ifndef KEY_COMBOS
    #endif
    #endif


    virtual void _keydown(SDL_KeyboardEvent ev){ // Detect various shortcuts
        if(ev->repeat > 0 ){
    switch(ev->state){
            case: SDL_PRESSED {
                switch(ev->keysym.sym) {

                }
            };
            case: SDL_RELEASED {

            };
        } 
        };
        switch(ev->state){
            case: SDL_PRESSED {
                switch(ev->keysym.sym) {

                }
            };
            case: SDL_RELEASED {

            };
        } 
    };
    virtual void _keyup(SDL_KeyboardEvent ev){

    };
    virtual void _textediting(SDL_TextEditingEvent ev){

    };
    virtual void _textinput(SDL_TextInputEvent ev);
    virtual void _keymapchanged();
    virtual void _textediting_ext(SDL_TextEditingExtEvent ev);
    virtual bool SDL_KeyEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_KEYDOWN
            {              
                inline this->_keydown(event->key);
                return true;
            }
        case:
            SDL_KEYUP
            {
                inline this->_keyup(event->key);
                return true;
            }
        case:
            SDL_TEXTEDITING
            {
                inline this->_textediting(event->edit);
                return true;
            }
        case:
            SDL_TEXTINPUT
            {
                inline this->_textinput(event->text);
                return true;
            }
        case:
            SDL_KEYMAPCHANGED
            {
                inline this->KEYMAPCHANGED();
                return true;
            }
        case:
            SDL_TEXTEDITING_EXT
            {
                inline this->_textediting_ext(event->editExt);
                return true;
            }
        };
    };
#endif
#ifdef MOUSE_EVENT
    enum MouseState {

    };
    virtual void _mousemotion(SDL_MouseMotionEvent ev){
        switch(ev->){

        }
        };
    virtual void _mousebuttondown(SDL_MouseButtonEvent ev){};
    virtual void _mousebuttonup(SDL_MouseButtonEvent ev);
    virtual void _mousewheel(SDL_MouseWheelEvent ev);


    getModsExt()

        assignMods()
    {
        getMods()
    }

    bool SDL_MouseEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_MOUSEMOTION
            {
                inline this->_mousemotion(event->motion);
                return true;
            }
        case:
            SDL_MOUSEBUTTONDOWN
            {
                inline this->_mousebuttondown(event->button);
                return true;
            }
        case:
            SDL_MOUSEBUTTONUP
            {
               inline  this->_mousebuttonup(event->button);
                return true;
            }
        case:
            SDL_MOUSEWHEEL
            {
               inline  this->_mousewheel(event->wheel);
                return true;
            }
        };
    };
#endif
#ifdef JOY_STICK_EVENT
    virtual void _joyaxismotion(SDL_JoyAxisEvent ev);
    virtual void _joyballmotion(SDL_JoyBallEvent ev);
    virtual void _joyhatmotion(SDL_JoyHatEvent ev);
    virtual void _joybuttondown(SDL_JoyButtonEvent ev);
    virtual void _joybuttonup(SDL_JoyButtonEvent ev);
    virtual void _joydeviceadded(SDL_JoyDeviceEvent ev);
    virtual void _joydeviceremoved(SDL_JoyDeviceEvent ev);
    virtual void _joybatteryupdated(SDL_JoyBatteryEvent ev);
    virtual bool SDL_JoyEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_JOYAXISMOTION
            {
            inline this->_joyaxismotion(event->jaxis);
            return true;
            } /**< Joystick axis motion */
        case:
            SDL_JOYBALLMOTION
            {
            inline this->_joyballmotion(event->jball);
            return true;
            } /**< Joystick trackball motion */
        case:
            SDL_JOYHATMOTION
            {
            inline this->_joyhatmotion(event->jhat);
            return true;
            } /**< Joystick hat position change */
        case:
            SDL_JOYBUTTONDOWN
            {
            inline this->_joybuttondown(event->jbutton);
            return true;
            } /**< Joystick button pressed */
        case:
            SDL_JOYBUTTONUP
            {
            inline this->_joybuttonup(event->jbutton);
            return true;
            } /**< Joystick button released */
        case:
            SDL_JOYDEVICEADDED
            {
            inline this->_joydeviceadded(event->jdevice);
            return true;
            } /**< A new joystick has been inserted into the system */
        case:
            SDL_JOYDEVICEREMOVED
            {
            inline this->_joydeviceremoved(event->jdevice);
            return true;
            } /**< An opened joystick has been removed */
        case:
            SDL_JOYBATTERYUPDATED
            {
            inline this->_joybatteryupdated(event->jbattery);
            return true;
            } /**< Joystick battery level change */
        }
        return false;
    };
#endif
#ifdef CONTROLLER_EVENT
   virtual  void _controlleraxismotion(SDL_ContorllerAxisEvent ev);
   virtual  void _controllerbuttondown(SDL_ControllerButtonEvent ev);
   virtual  void _controllerbuttonup(SDL_ControllerButtonEvent ev);
   virtual  void _controllerdeviceadded(SDL_ControllerDeviceEvent ev);
   virtual  void _controllerdeviceremoved(SDL_ControllerDeviceEvent ev);
   virtual  void _controllerdeviceremapped(SDL_ControllerDeviceEvent ev);
   virtual  void _controllertouchpaddown(SDL_ControllerTouchpadEvent ev);
   virtual  void _controllertouchpadmotion(SDL_ControllerTouchpadEvent ev);
   virtual  void _controllertouchpadup(SDL_ControllerTouchpadEvent ev);
   virtual  void _controllersensorupdate(SDL_ControllerSensorEvent ev);
   virtual  bool SDL_ControllerEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_CONTROLLERAXISMOTION
            {
                inline this->_controlleraxismotion(event->caxis) ;
                return true;
            }
        case:
            SDL_CONTROLLERBUTTONDOWN
            {
                inline this->_controlleraxismotion(event->cbutton) ;
                return true;
            } /**< Game controller button pressed */
        case:
            SDL_CONTROLLERBUTTONUP
            {
                inline this->_controlleraxismotion(event->button) ;
                return true;
            } /**< Game controller button released */
        case:
            SDL_CONTROLLERDEVICEREMAPPED
            {
                inline this->_controlleraxismotion(event->device) ;
                return true;
            } /**< The controller mapping was updated */
        case:
            SDL_CONTROLLERTOUCHPADDOWN
            {
                inline this->_controlleraxismotion(event->ctouchpad) ;
                return true;
            } /**< Game controller touchpad was touched */
        case:
            SDL_CONTROLLERTOUCHPADMOTION
            {
               inline  this->_controlleraxismotion(event->ctouchpad) ;
                return true;
            } /**< Game controller touchpad finger was moved */
        case:
            SDL_CONTROLLERTOUCHPADUP
            {
                inline this->_controlleraxismotion(event->ctouchpad) ;
                return true;
            } /**< Game controller touchpad finger was lifted */
        case:
            SDL_CONTROLLERSENSORUPDATE
            {
                inline this->_controlleraxismotion(event->csensor) ;
                return true;
            }
        case:
            SDL_CONTROLLERDEVICEADDED
            {
                inline this->_controlleraxismotion(event->cdevice) ;
                return true;
            } /**< A new Game controller has been inserted into the system */
        case:
            SDL_CONTROLLERDEVICEREMOVED
            {
                inline this->_controlleraxismotion(event->cdevice) ;
                return true;
            } /**< An opened Game controller has been removed */
        default: 
            return false 

        }
    };
#ifdef TOUCH_EVENT
    virtual void _fingerdown(SDL_TouchFingerEvent ev);
    virtual void _fingerup(SDL_TouchFingerEvent ev);
    virtual void _fingermotion(SDL_TouchFingerEvent ev);
    virtual bool SDL_TouchEvent(SDL_Event *event)
    {
            switch (event->type)
            {
            case:
                SDL_FINGERDOWN
                {
                    inline this->_fingerdown(event->tfinger);
                    return true;
                }
            case:
                SDL_FINGERUP
                {
                    inline this->_fingerup(event->tfinger);
                    return true;
                }
            case:
                SDL_FINGERMOTION
                {
                   inline  this->_fingermotion(event->tfinger);
                    return true;
                }
            default:
                return false ;
            };
       
    };
   
#endif
#ifdef GESTURE_EVENT
    virtual void _dollargesture(SDL_DollarGesture ev){};
    virtual void _dollarrecord(SDL_DollarGesture ev){};
    virtual void _multigesture(SDL_MultiGestureEvent ev){};
    SDL_DollarGesture _DOLLARGESTURE_ARG = NULL;
    SDL_DollarGesture _DOLLARRECORD_ARG = NULL;
    SDL_MultiGestureEvent _MULTIGESTURE_ARG = NULL;
    bool SDL_GestureEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case SDL_MULTIGESTURE {
                inline this->_multigesture(event->mgesture); return true;
        };
        case:
        SDL_DOLLARGESTURE
            {
               inline  this->_dollargesture(event->dgesture);

                return true;
            };
        case:
            SDL_DOLLARRECORD
            {
                inline this->_dollargesture(event->dgesture);
                return true;
            };
        }
        if (this->_DOLLARGESTURE_ARG != NULL)
        {
            this->_DOLLARGESTURE(this->_DOLLARGESTURE_ARG);
        };
        if (this->_DOLLARRECORD_ARG != NULL)
        {
            this->_DOLLARRECORD(this->_DOLLARRECORD_ARG);
        };
        if (this->_MULTIGESTURE_ARG != NULL)
        {
            this->_MULTIGESTURE(this->_MULTIGESTURE_ARG);
        };
    };
#endif
#ifdef CLIPBOARD_EVENT
    virtual bool (*ClipBoardEvent)(SDL_Event *);
    virtual void (*_CLIPBOARDUPDATE)();

    virtual void _clipboardupdate(){return };
    virtual bool SDL_ClipBoardEvent(SDL_Event *event)
    {
        if (event->type == SDL_CLIPBOARDUPDATE)
        {
            this->_clipboardupdate();
            return true;
        };
        return false;
    };
    virtual void assignClipBoardEvent()
    {
        this->ClipBoardEvent = this->SDL_ClipBoardEvent;
        this->_CLIPBOARDUPDATE = this->_clipboardupdate;
    };
#endif
#ifdef DROP_EVENT
    virtual void _dropfile(SDL_DropEvent ev){};
    virtual void _droptext(SDL_DropEvent ev){};
    virtual void _dropbegin(SDL_DropEvent ev){};
    virtual void _dropcomplete(SDL_DropEvent ev){};
    virtual bool SDL_DropEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_DROPFILE
            {
                inline this->_dropfile(event->drop);
                return true;
            }; /**< The system requests a file open */
        case:
            SDL_DROPTEXT
            {
                inline this->_droptext(event->drop);
                return true;

            }; /**< text/plain drag-and-drop event */
        case:
            SDL_DROPBEGIN
            {
                inline this->_dropbegin(event->drop);
                return true;
            }; /**< A new set of drops is beginning (NULL filename) */
        case:
            SDL_DROPCOMPLETE
            {
                inline this->_dropcomplete(event->drop);
                return true;
            };
        }
    };
    virtual void assignDropEvent()
    {
        this->DropEvent = this->SDL_DropEvent;
        _DROPFILE = _dropfile;
        _DROPTEXT = _droptext;
        _DROPBEGIN = _dropbegin;
        _DROPCOMPLETE = _dropcomplete;
    };
#endif
#ifdef AUDIO_EVENT
   
    virtual void _audiodeviceadded(SDL_AudioDeviceEvent);
    virtual void _audiodeviceremoved(SDL_AudioDeviceEvent);
    SDL_AudioDeviceEvent _AUDIODEVICEADDED_ARG = NULL;
    SDL_AudioDeviceEvent _AUDIODEVICEREMOVED_ARG = NULL;
    virtual bool SDL_AudioEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_AUDIODEVICEADDED
            {
                inline this->_audiodeviceadded(event->adevice);

            }
        case:
            SDL_AUDIODEVICEREMOVED
            {
                inline this->_audiodeviceremoved(event->adevice);
            }
        }
    };
  
#endif
#ifdef SENSOR_EVENT
    virtual bool (*SensorEvent)(SDL_Event *);
    virtual void (*_SENSORUPDATE)(SDL_SensorEvent);
    virtual void _sensorupdate(SDL_SensorEvent ev){};

    virtual bool SDL_SensorEvent(SDL_Event *event)
    {
       
        if (event->type == SDL_SENSORUPDATE)
        {
            inline this->_sensorupdate(event->sensor);
            return true;
        }
    };
#ifdef RENDER_EVENT
    virtual void _render_targets_reset() {}
    virtual void _render_device_reset(){};
    virtual bool SDL_RenderEvent(SDL_Event *event)
    {
        #ifndef FP_RENDER_EVENT
        switch (event->type)
        {
        case:
            SDL_RENDER_TARGETS_RESET
            {
                inline this->_render_targets_reset();
                return true;

            } /**< The render targets have been reset and their contents need to be updated */
        case:
            SDL_RENDER_DEVICE_RESET
            {
                inline this->_render_device_reset();
                return true;
            };
        }
        #endif
    };
#endif
#ifdef POLL_SENTINEL_EVENT
    virtual void _pollsentinel(){     return;   };
    virtual bool SDL_PollSentinelEvent()
    {
        if (event->type == SDL_POLLSENTINEL)
        {
            this->_pollsentinelevent();
            return true;
        }
    };
#endif
#ifdef EVENT_LOOP
typedef struct event{

}event ;
virtual bool processEvent(event ev) {

};
std::vector<event> events ;
virtual void event_loop(event event){
    #ifdef THREAD_EVENT
    bool quit_event_thread 
    while(quit_event_thread){
    #endif
    for( event i : events){
        #ifdef EVENT_ASYNC
        std::async(std::launch::async, &this->processEvent, i);
        #endif
        #ifndef EVENT_ASYNC
        this->processEvent(i) ;
        #endif
    };
    #ifdef THREAD_EVENT
    };
    #endif
}
#endif

#ifdef RESAQ_LOOP

#ifdef THREAD_RESAQ

bool  quit_resaq_thread = false ;
#endif

virtual inline void load(){ // Function that loads any assets supplied to it to be consumed by another process
    
};
virtual void resaq_loop(){
#ifdef THREAD_RESAQ
    while (!this->quit_resaq_thread){
#endif
#ifdef THREAD_RESAQ
    };
#endif
};
#endif

#ifdef RENDER_LOOP
#ifdef THREAD_RENDER
bool quit_render_loop = false ;
#endif
virtual void render_loop(){         
    #ifdef THREAD_RENDER
    while(!this->quit_render_thread)
    #endif
    {

        SfwGui::
    if (io.ConfigFlags & SfwGuiConfigFlags_ViewportsEnable)
    {
        SfwGui::UpdatePlatformWindows();
        SfwGui::RenderPlatformWindowsDefault();
    }
    }
    
}
#endif

#ifdef GAME_LOOP
#ifdef GAME_LOOP_PRIORITY
enum GameLoopPriority
{
#ifdef CONTROL_MOUSE_KEYBOARD
    GAMECONTROLMODE_MOUSE_KEYBAORD = 0,
#endif
#ifdef CONTROL_JOYSTICK //
    GAMECONTROLMODE_JOYSTICK = 1,
#endif
#ifdef CONTROL_CONTROLLER
    GAMECONTROLMODE_CONTROLLER = 2,
#endif
#ifdef CONTROL_TOUCH
    GAMECONTROLMODE_TOUCH = 3
#endif
};
#endif
bool quit_game_loop = false ; 


virtual void game_loop()  // In this loop all entity updates are handled
{
 #ifdef THREAD_GAME
    while(!this->quit_game_loop){
 #endif
   
 #ifdef THREAD_GAME
    };
#endif
};
#endif

titleBar(){

}
virtual void main_loop() // In this loop all events are handled input or otherwise
{

    // Custom 
#ifdef THREAD_GAME
std::thread game(
#ifdef FP_GAME_LOOP
    fp_game_loop,
#endif
#ifndef FP_GAME_LOOP
    game_loop,    
#endif
    void ) ;
#endif
#ifdef THREAD_EVENT
std::thread render(
    render_loop,
    void );
#endif
#ifdef THREAD_RESAQ
std::thread render(
    render_loop,
    void );
#endif
#ifdef THREAD_RENDER
std::thread render(
    render_loop,
    void );
#endif
SDL_Event event;
    bool quit = false;
    bool gui_priority = true; 
    bool gui_active = true ;
    while (SDL_PollEvent(&event) != 0) 
    {
     
        if(gui_active){
            if(SfwGui_ImplSDL2_ProcessEvent(&event)){
                continue ;
            };
        }
        if(event < SDL_DISPLAYEVENT ){
        #ifdef APP_EVENT
            inline this->AppEvent(&event);
        #endif
        }
        else(event < SDL_WINDOWEVENT){
        #ifdef DISPLAY_EVENT
        inline this->DisplayEvent(&event);
        #endif
        }
        else(event < SDL_KEYDOWN){
        #ifdef WINDOW_EVENT
        inline this->WindowEvent(&event);
        #endif
        }
        else (event < SDL_MOUSEMOTION) {
        #ifdef KEY_EVENT
        inline this->KeyEvent(&event);
        #endif
        }
        else (event < SDL_JOYAXISMOTION ){
        #ifdef MOUSE_EVENT
        inline this->MouseEvent(&event);
        #endif
        } 
        else (event < SDL_CONTROLLERAXISMOTION){
        #ifdef JOY_STICK_EVENT
        inline this->JoyEvent(&event);
        #endif
        }
        else (event < SDL_FINGERDOWN){
        #ifdef CONTROLLER_EVENT
        inline this->ControllerEvent(&event);
        #endif
        }
        else (event < SDL_DOLLARGESTURE){
        #ifdef TOUCH_EVENT
        inline this->TouchEvent(&event);
        #endif
        }
        else (event < SDL_CLIPBOARDUPDATE){
        #ifdef GESTURE_EVENT
        inline this->GestureEvent(&event);
        #endif
        }
        else (event < SDL_DROPFILE){
        #ifdef CLIPBOARD_EVENT
        inline this->ClipboardEvent(&event);
        #endif
        }
        else (event < SDL_AUDIODEVICEADDED){
        #ifdef DROP_EVENT
        inline this->DropEvent(&event);
        #endif
        }
        else (event < SDL_SENSORUPDATE){
        #ifdef AUDIO_EVENT
        inline this->AudioEvent(&event);
        #endif
        }
        else (event < SDL_RENDER_TARGETS_RESET) {
        #ifdef SENSOR_EVENT
        inline this->SensorEvent(&event);
        #endif
        }
        if(event < SDL_POLLSENTINEL){
        #ifdef RENDER_EVENT
        inline this->RenderEvent(&event);
        #endif
        }
        if(event < SDL_USEREVENT){
        #ifdef POLL_SENTINEL_EVENT
        inline this->PollSentinelEvent(&event);
        #endif
        }
#ifndef THREAD_GAME
        inline this->game_loop(&event);
#endif
#ifndef THREAD_RESAQ
        inline this->resaq_loop(&event);
#endif
#ifndef THREAD_EVENT
        inline this->event_loop(&event);
#endif
#ifndef THREAD_RENDER
        inline this->render_loop(&event);
#endif
        if (event.type == SDL_QUIT)
        {
            quit = true;
            continue;
        }
        if (this->SDL_AppEvent(&event))
        {
            continue;
        }
    };
}

    sei(){

    }

}