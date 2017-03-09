CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

all: raytracer

raytracer: point.o camera.o main.o sampler.o shape.o raytracer.o scene.o film.o camera.o
	$(CC) $(CFLAGS) -o raytracer point.o camera.o shape.o raytracer.o scene.o sampler.o film.o main.o ${INCFLAGS} ${LDFLAGS}

main.o: main.cpp Scene.h Film.h Sampler.h Sample.h LocalGeo.h Ray.h Shape.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp

sampler.o: Sampler.cpp Sampler.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp

scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp

film.o: Film.cpp Film.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Film.cpp

point.o: Point.cpp Point.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Point.cpp

camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp

shape.o: Shape.cpp Shape.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp

raytracer.o: Raytracer.cpp Raytracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Raytracer.cpp

clean:
	rm *.o raytracer *.png
