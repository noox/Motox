
LIBS = -lGL -lglut

all: motox

motox: *.cpp *.h
	g++ *.cpp ${LIBS} -o motox

clean:
	rm motox

