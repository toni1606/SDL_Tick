# SDL_Tick
This project is a clone of Tick Tack Toe implemented in C using the SDL Media Library. It was built as a side project with the main purpose of learning more about SDL. In it's current state it has a few bugs which are known.

## Building
To be able to build the app you must have `SDL2` and `make` installed. In Linux you can run the following command tu build and run the app.

```bash
make run
```

## Switching from GUI to CLI
If you wish to switch from GUI mode to CLI mode you can add the following line to the top of `src/main.c`, then recompile.
```c
#define CLI_APP 0
```
