GLAD_HEADER_DIR=~/software/glad/include
GLFW_HEADER_DIR=~/software/glfw/include
GLFW_LINK_DIR=~/software/glfw/lib
GLM_HEADER_DIR=~/software/glm-0.9.9-a2
CFLAGS= -I $(GLFW_HEADER_DIR) -I $(GLAD_HEADER_DIR) -I $(GLM_HEADER_DIR) -D DEBUG 
LFLAGS= -L $(GLFW_LINK_DIR) -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lpthread  -lrt -lm  -ldl
BUILD_DIR=build
CC=g++
SRCS=tools.cpp errorTools.cpp circle.cpp cylinder.cpp square.cpp stb.cpp toolsGL.cpp shapes.cpp sphere.cpp camera.cpp shader.cpp  scene.cpp lighting.cpp glad.cpp
OBJS=$(SRCS:%.cpp=$(BUILD_DIR)/%.o)
SRCSTEST=glad.cpp testTriangle.cpp square.cpp shapes.cpp toolsGL.cpp stb.cpp shader.cpp tools.cpp scene.cpp camera.cpp
OBJSTEST=$(SRCSTEST:%.cpp=$(BUILD_DIR)/%.o)
all:	visuals

clean:
	find $(BUILD_DIR) -type f -name '*.o' -exec rm {} \;
	rm -f vis
test:		$(OBJSTEST)
	$(CC) $^ $(LFLAGS)   -o test

visuals:	$(OBJS)
	$(CC) $^ $(LFLAGS)   -o vis

$(BUILD_DIR)/%.o: 	%.cpp
	$(CC) -c $(CFLAGS)  $< -o $@
