#include <stdio.h>
#include <unistd.h>

#include "gpu_usage.h"

int main(int argc, char const *argv[])
{
    if(gpu_init(0)){
        fprintf(stderr, "error initializing gpu\n");
        return -1;
    }

    for (size_t i = 0; i < 120; i++)
    {
        fprintf("gpu utilization: %d", gpu_get_utilization());
        sleep(1);
    }
    
    return 0;
}
