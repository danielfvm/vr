build: 
	g++ test.cpp -lGL -lGLU -lGLEW -lglut -lm -o Test

clean: 
	rm Test
