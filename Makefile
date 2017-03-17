CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -g3 -O0 -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -g3 -O0 -DGL_GLEXT_PROTOTYPES
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

all: raytracer

raytracer: camera.o main.o sampler.o shape.o raytracer.o scene.o film.o camera.o transforms.o readfile.o light.o
	$(CC) $(CFLAGS) -o raytracer camera.o shape.o raytracer.o scene.o sampler.o film.o transforms.o light.o readfile.o main.o ${INCFLAGS} ${LDFLAGS}

main.o: main.cpp Scene.h Film.h Sampler.h Intersection.h Ray.h Shape.h variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp

sampler.o: Sampler.cpp Sampler.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp

scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp

film.o: Film.cpp Film.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Film.cpp

camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp

shape.o: Shape.cpp Shape.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp

raytracer.o: Raytracer.cpp Raytracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Raytracer.cpp

readfile.o: readfile.cpp readfile.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp

transforms.o: Transforms.cpp Transforms.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transforms.cpp

light.o: Light.cpp Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Light.cpp

clean:
	rm *.o raytracer *.png
