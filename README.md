# ppengine

A mostly-complete 3D remake of Atari's Pole Position coin-op, using game logic reverse engineered from the arcade ROMs

## How to build

As a rough guide, you'll need:
- Ideally Linux - this hasn't been tested on Windows or Mac;
- GCC 4.0 or above;
- Make, to execute the Makefile;
- Various SDL2 development libraries (the packages are called libsdl-*-dev on my Ubuntu installation);
- The Open Scene Graph development libraries (the package is called libopenscenegraph-dev on my Ubuntu installation);
- The Gorilla 2 sound library (see https://code.google.com/archive/p/gorilla-audio/) - you might need to compile this separately.

Before running 'make' to execute the Makefile, set the GORILLA_AUDIO environment variable to the directly in which you've installed Gorilla Audio. For example:

`export GORILLA_AUDIO=~/gorilla`

Now, run the Makefile from within the top-level directory of the repository (the one containing the 'src' directory):

`make`

In theory, the compiler should run for a short while, after which it'll output an executable called 'client', which you can then execute to play the game (see 'How to play') below.

If the compile fails and you're struggling to understand why, drop me an email at jonathan@opalise.co.uk.

## How to play

Once you've run the 'client' executable, the game window will pop up. The initial grey square is the unimplemented title screen, but if you leave things to run for a moment, the demo mode will start running.

Press '1' to start a game. Arrow keys will steer, brake and accelerate. Space toggles between low and high gear.

