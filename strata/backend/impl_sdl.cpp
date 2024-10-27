template <sren_c rc>
class sdl_env_c :  senv_c {
    rc 
    std::vector<uint> displays  ;

    std::vector<SDL_Window*> windows ; 
    void addWindow(char title , int x, int y, int w , int h ){
        this->window = SDL_CreateWindow()
    };
    void getNumDisplays();
    void add

};