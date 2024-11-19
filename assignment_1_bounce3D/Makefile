CC      = g++
C	= cpp
H	= h

CFLAGS    = -g -std=c++11

CFLAGS    = -g -std=c++11 \
			-I C:\Programming\freeglut-3.0.0\freeglut\include \
			-I C:\Programming\GLEW\glew-2.2.0\include \
			-I C:\Programming\GLUT\freeglut-3.4.0\include

ifeq ($(OS),Windows_NT)
	LDFLAGS = -L C:\Programming\freeglut-3.0.0\freeglut\lib\x64 \
			-L C:\Programming\GLEW\glew-2.2.0\lib\Release\x64 \
			-L C:\Programming\GLUT\freeglut-3.4.0\lib \
			-lopengl32 -lglew32 -lfreeglut -lglu32
	FREEGLUT_DLL = C:\Programming\freeglut-3.0.0\freeglut\bin\x64\freeglut.dll
	GLEW_DLL = C:\Programming\GLEW\glew-2.2.0\bin\Release\x64\glew32.dll
endif

copy_dlls:
	@echo "Copying DLLs..."
	@if exist "$(FREEGLUT_DLL)" ( \
		copy /Y "$(FREEGLUT_DLL)" . \
	) else ( \
		echo "ERROR: $(FREEGLUT_DLL) not found" \
	)
	@if exist "$(GLEW_DLL)" ( \
		copy /Y "$(GLEW_DLL)" . \
	) else ( \
		echo "ERROR: $(GLEW_DLL) not found" \
	)

HFILES = Vector.${H} Utility.${H}
OFILES = Vector.o Utility.o
PROJECT = bounce

${PROJECT}.exe:	${PROJECT}.o ${OFILES} copy_dlls
	${CC} ${CFLAGS} -o ${PROJECT}.exe ${PROJECT}.o ${OFILES} ${LDFLAGS}

${PROJECT}.o: ${PROJECT}.${C} ${HFILES}
	${CC} ${CFLAGS} -c ${PROJECT}.${C}

Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} ${CFLAGS} -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} ${CFLAGS} -c Utility.${C}

# clean:
# 	rm -f core.* *.o *~ .DS_Store ${PROJECT}

clean:
	del /Q core.* *.o *~ .DS_Store $(PROJECT).exe *.dll

run: ${PROJECT}.exe
	@echo "Running $(PROJECT).exe..."
	@echo "Current directory contains:"
	@dir *.dll
	.\${PROJECT}.exe

.PHONY: clean run copy_dlls

