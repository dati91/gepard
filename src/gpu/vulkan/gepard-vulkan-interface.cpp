/* Copyright (C) 2016, Gepard Graphics
 * Copyright (C) 2016, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef USE_VULKAN

#include "gepard-vulkan-interface.h"

#include <dlfcn.h>

namespace gepard {

namespace vulkan {

GepardVulkanInterface::GepardVulkanInterface(const char *libraryName)
{
    _vulkanLibrary = dlopen(libraryName, RTLD_LAZY);
}

GepardVulkanInterface::~GepardVulkanInterface()
{
    dlclose(_vulkanLibrary);
}

void GepardVulkanInterface::loadGlobalFunctions()
{
#define GD_VK_LOAD_FUNCTION(fun)\
    fun = (PFN_##fun) vkGetInstanceProcAddr (0, #fun); \
    ASSERT(fun && "Couldn't load " #fun "!");

    if (!_vulkanLibrary) {
            GD_CRASH("Loading the Vulkan library was unsuccessfuly!\n");
            return;
    }

    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(_vulkanLibrary, "vkGetInstanceProcAddr");
    ASSERT(vkGetInstanceProcAddr && "Couldn't load the vkGetInstanceProcAddr function!");

    GD_VK_LOAD_FUNCTION (vkCreateInstance);

#undef GD_VK_LOAD_FUNCTION
}

void GepardVulkanInterface::loadInstanceFunctions(VkInstance instance)
{
#define GD_VK_LOAD_FUNCTION(fun)\
    fun = (PFN_##fun) vkGetInstanceProcAddr (instance, #fun); \
    ASSERT(fun && "Couldn't load " #fun "!");

    GD_VK_LOAD_FUNCTION(vkDestroyInstance);
    GD_VK_LOAD_FUNCTION(vkEnumeratePhysicalDevices);
    GD_VK_LOAD_FUNCTION(vkGetPhysicalDeviceProperties);
    GD_VK_LOAD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties);
    GD_VK_LOAD_FUNCTION(vkCreateDevice);
    GD_VK_LOAD_FUNCTION(vkGetDeviceProcAddr);

#undef GD_VK_LOAD_FUNCTION
}

void GepardVulkanInterface::loadDeviceFunctions(VkDevice device)
{
#define GD_VK_LOAD_FUNCTION(fun)\
    fun = (PFN_##fun) vkGetDeviceProcAddr (device, #fun); \
    ASSERT(fun && "Couldn't load " #fun "!");

    GD_VK_LOAD_FUNCTION(vkDestroyDevice);
    GD_VK_LOAD_FUNCTION(vkGetDeviceQueue);

#undef GD_VK_LOAD_FUNCTION
}



} // namespace vulkan

} // namespace gepard

#endif // USE_VULKAN
