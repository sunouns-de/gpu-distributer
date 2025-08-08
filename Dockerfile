FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y gcc libnvidia-ml-dev && \
    apt-get clean

# Copy and build the program
COPY main.c /main.c
COPY gpu_usage.h /gpu_usage.h
COPY gpu_usage.c /gpu_usage.c
RUN gcc /gpu_usage.c -lnvidia-ml /main.c -o /gpu_usage

CMD ["/gpu_usage"]
