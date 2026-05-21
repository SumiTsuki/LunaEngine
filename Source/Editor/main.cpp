#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // 1. 强制走 Wayland 
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "wayland");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL 初始化失败: " << SDL_GetError() << "\n";
        return -1;
    }

    // 2. 用现代属性创建窗口（明确状态）
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Niri Wayland Test");
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 640);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 480);
    SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN, true);
    
    SDL_Window* window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    if (!window) {
        std::cerr << "窗口创建失败: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    // =======================================================
    // 💡 核心补刀：创建 SDL3 渲染器（Renderer）
    // 这一步会让 SDL3 在后台借助 OpenGL/Mesa 与 Wayland 建立真实的画面通道
    // =======================================================
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "渲染器创建失败: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    std::cout << "🎉 窗口与渲染器全部就绪！开始向 Niri 提交画面帧...\n";

    bool running = true;
    SDL_Event event;

    // 3. 游戏主循环：必须进行画面刷新
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // 🎨 【极为重要】往画布上涂上颜色（例如亮蓝色：红0, 绿120, 蓝255）
        SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
        
        // 清空当前画布
        SDL_RenderClear(renderer);
        
        // 🚀 【向 Niri 震网提交】把这一帧画面狠狠地甩给 Wayland 合成器
        // 这一步一执行，Niri 就会收到图像信号，立刻把窗口展开！
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // 锁 60 帧左右
    }

    // 4. 干净的逆序销毁
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
