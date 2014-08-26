
#include <SDL2/SDL.h>
#include <iostream>

// DONT EVER USE GLOBALS!!!
SDL_Window *window;
SDL_GLContext gl_context;
bool running = true;

void createWindow(int width, int height);
void pollEvents();
void cleanup();

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Cannot Initialize SDL" << std::endl;
        exit(1);
    }

    int windowWidth = 600, windowHeight = 600;
    createWindow(windowWidth, windowHeight);

    while(running) {
        pollEvents();

        // swap render buffer
        SDL_GL_SwapWindow(window);
    }


}

void createWindow(int width, int height)
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("CS 480/680", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(!window) {
        std::cerr << "Unable to create GL Window" << std::endl;
        exit(0);
    }

    gl_context = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);
}

void pollEvents()
{
    SDL_Event event;
    char key;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                key = (char)event.key.keysym.sym;
                if(key == SDLK_ESCAPE) {
		    cleanup();
                    exit(0);
                }

                std::cout << "Key Pressed:  " << key << std::endl;
                break;

            case SDL_KEYUP:
                key = (char)event.key.keysym.sym;
                std::cout << "Key Released: " << key << std::endl;
                break;

            case SDL_QUIT:
                running = false;
                break;

            case SDL_MOUSEMOTION:
                std::cout << "Mouse Moved {" << event.motion.x << ", " << event.motion.y << "}" << std::endl;
                break;

            case SDL_MOUSEBUTTONDOWN:
                std::cout << "Mouse Clicked ";

                switch(event.button.button) {
                    case SDL_BUTTON_LEFT:
                        std::cout << "{Left}" << std::endl;
                    break;

                    case SDL_BUTTON_RIGHT:
                        std::cout << "{Right}" << std::endl;
                    break;

                    case SDL_BUTTON_MIDDLE:
                        std::cout << "{Middle}" << std::endl;
                    break;
                }

                break;
        }
    }
}

void cleanup()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
