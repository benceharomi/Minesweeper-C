# Minesweeper C

## Requirements
Please mind that gcc and the SDL libaries are required for the execution of this program.
### Linux
gcc:
```
apt install build-essential
```
SDL libaries:
```
apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```
### Mac
Install homebrew:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```
Install SDL:
```
brew install sdl2 && sdl2_gfx
```
## Execution
Make sure you are in the root of the repository.
Compile:
```
gcc -o bin/minesweeper src/*.c `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer
```
Execute:
```
bin/./minesweeper
```
