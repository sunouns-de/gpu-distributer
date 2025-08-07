#include <stdio.h>
#include <nvml.h>

int init_device(int device_num){
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
        return 1;
    }

    if (device_count < device_num){
        return -1;
    }
    return 0;
}

int main() {
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
        return 1;
    }

    for (i = 0; i < device_count; i++) {
        nvmlDevice_t device;
        char name[64];
        nvmlUtilization_t utilization;
        nvmlMemory_t memory;
        unsigned int temperature;

        result = nvmlDeviceGetHandleByIndex(i, &device);
        if (result != NVML_SUCCESS) {
            printf("Failed to get handle for device %d: %s\n", i, nvmlErrorString(result));
            continue;
        }

        nvmlDeviceGetName(device, name, sizeof(name));
        nvmlDeviceGetUtilizationRates(device, &utilization);
        nvmlDeviceGetMemoryInfo(device, &memory);
        nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature);

        printf("GPU %d: %s\n", i, name);
        printf("  GPU Utilization     : %u%%\n", utilization.gpu);
        printf("  Memory Usage        : %llu / %llu MB\n",
               memory.used / 1024 / 1024, memory.total / 1024 / 1024);
        printf("  Temperature         : %u C\n", temperature);
        printf("-----------------------------\n");
    }

    nvmlShutdown();
    return 0;
}
