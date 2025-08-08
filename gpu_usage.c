#include <stdio.h>
#include <nvml.h>

#include "gpu_usage.h"

nvmlDevice_t device;

int gpu_init(int device_num){
    nvmlReturn_t result;
    unsigned int device_count, i;

    result = nvmlInit();
    if (result != NVML_SUCCESS) {
        printf("Failed to initialize NVML: %s\n", nvmlErrorString(result));
        return 1;
    }

    result = nvmlDeviceGetCount(&device_count);
    if (result != NVML_SUCCESS) {
        printf("Failed to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 2;
    }

    if (device_count < device_num){
        return 3;
    }

    result = nvmlDeviceGetHandleByIndex(i, &device);
    if (result != NVML_SUCCESS) {
        printf("Failed to get device count: %s\n", nvmlErrorString(result));
        nvmlShutdown();
        return 4;
    }
        
    char name[96];
    nvmlDeviceGetName(device, name, sizeof(name));
    printf("successfully initialized Device %s\n", name);

    return 0;
}

int gpu_get_utilization(){
    nvmlUtilization_t utilization;
    nvmlReturn_t result = nvmlDeviceGetUtilizationRates(device, &utilization);
    if(result != NVML_SUCCESS){
        return -1;
    }
    return (int) utilization.gpu;
}
