all:
	g++ -I Game/include -L Game/lib -o main *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
	.\main.exe