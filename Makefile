# Makefile for both application and kernel module

.PHONY: all build clean docker-build app-build module-build help docker-shell docker-clean doc

# Docker image name
DOCKER_IMAGE := raspberrypi5-app-builder:latest

# Build directories
APP_BUILD_DIR := application/build
MODULE_BUILD_DIR := kernel_module/build

# Color codes
GREEN := \033[0;32m
NC := \033[0m # No Color

default: all

help:
	@echo -e "${GREEN}Available targets:${NC}"
	@echo "  all          - Build both application and kernel module"
	@echo "  app-build    - Build only the application"
	@echo "  module-build - Build only the kernel module"
	@echo "  clean        - Clean all build directories"
	@echo "  docker-shell - Open a shell inside the Docker container"
	@echo "  docker-clean - Clean the Docker environment"
	@echo "  help         - Display this help message"

all: app-build module-build doc

app-build:
	@echo -e "${GREEN}Building application...${NC}"
	docker run --rm -v ${PWD}:/workspace ${DOCKER_IMAGE} \
		bash -c "set -e && \
		source /opt/poky/environment-setup-cortexa76-poky-linux && \
		cd /workspace/application && \
		mkdir -p build && \
		cd build && \
		cmake .. && \
		make"
	@echo -e "${GREEN}Application build completed.${NC}"

module-build:
	@echo -e "${GREEN}Building kernel module...${NC}"
	docker run --rm -v ${PWD}:/workspace ${DOCKER_IMAGE} \
		bash -c "set -e && \
		source /opt/poky/environment-setup-cortexa76-poky-linux && \
		cd /workspace/kernel_module && \
		make "
	@echo -e "${GREEN}Kernel module build completed.${NC}"

docker-shell:
	@echo -e "${GREEN}Opening a shell inside the Docker container...${NC}"
	docker run --rm -it -v ${PWD}:/workspace ${DOCKER_IMAGE} bash

docker-clean:
	@echo -e "${GREEN}Cleaning Docker environment...${NC}"
	docker system prune -f
	@echo -e "${GREEN}Docker environment cleaned.${NC}"

clean:
	@echo -e "${GREEN}Cleaning build directories...${NC}"
	rm -rf ${APP_BUILD_DIR}/
	rm -rf ${MODULE_BUILD_DIR}/
	rm -rf doc/  # Remove the doc directory
	@echo -e "${GREEN}Clean completed.${NC}"

doc:
	@echo -e "${GREEN}Generating documentation...${NC}"
	docker run --rm -v ${PWD}:/workspace ${DOCKER_IMAGE} \
		bash -c "set -e && \
		cd /workspace && \
		doxygen"
	@echo -e "${GREEN}Documentation generated in ./doc.${NC}"