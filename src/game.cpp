#include "game.h"

#include "window.h"
#include "../vendor/nuklear/nuklear_sdl_gl3.h"
#include "workqueue.h"
#include "modelviewer.h"

namespace Impacto {

static int const NkMaxVertexMemory = 256 * 1024;
static int const NkMaxElementMemory = 128 * 1024;

static int const GameScrWorkSize = 32000;
static int const GameFlagWorkSize = 1000;

Game::Game(GameFeatureConfig const& config) : Config(config) {
  WindowInit();

  if (Config.GameFeatures & GameFeature_Nuklear) {
    Nk = nk_sdl_init(g_SDLWindow, NkMaxVertexMemory, NkMaxElementMemory);
    struct nk_font_atlas* atlas;
    nk_sdl_font_stash_begin(&atlas);
    // no fonts => default font used, but we still have do the setup
    nk_sdl_font_stash_end();
  }

  if (Config.GameFeatures & GameFeature_Scene3D) {
    SceneInit();
    Scene3D = new Scene;
  }

  if (Config.GameFeatures & GameFeature_ModelViewer) {
    ModelViewerComponent = new ModelViewer(this);
  }

  if (Config.GameFeatures & GameFeature_Sc3VirtualMachine) {
    VmComponent = new Vm::Vm(this);
    ScrWork = (uint32_t*)calloc(GameScrWorkSize, sizeof(uint32_t));
    FlagWork = (uint8_t*)calloc(GameFlagWorkSize, sizeof(uint8_t));
  }
}

void Game::Init() {
  if (Config.GameFeatures & GameFeature_Scene3D) {
    Scene3D->Init();
  }
  if (Config.GameFeatures & GameFeature_ModelViewer) {
    ModelViewerComponent->Init();
  }

  if (Config.GameFeatures & GameFeature_Sc3VirtualMachine) {
    VmComponent->Init(4, 0);
  }
}

Game* Game::CreateModelViewer() {
  GameFeatureConfig config;
  config.LayerCount = 1;
  config.GameFeatures =
      GameFeature_Nuklear | GameFeature_Scene3D | GameFeature_ModelViewer;
  config.Scene3D_BackgroundCount = 1;
  config.Scene3D_CharacterCount = 1;

  Game* result = new Game(config);
  result->Init();
  return result;
}

Game* Game::CreateVmTest() {
  GameFeatureConfig config;
  config.LayerCount = 1;
  config.GameFeatures = GameFeature_Sc3VirtualMachine;

  Game* result = new Game(config);
  result->Init();
  return result;
}

Game::~Game() {
  if (Config.GameFeatures & GameFeature_ModelViewer) {
    delete ModelViewerComponent;
  }

  if (Config.GameFeatures & GameFeature_Sc3VirtualMachine) {
    if (ScrWork) free(ScrWork);
    if (FlagWork) free(FlagWork);
    delete VmComponent;
  }

  if (Config.GameFeatures & GameFeature_Scene3D) {
    if (Scene3D) {
      delete Scene3D;
    }
  }

  if (Config.GameFeatures & GameFeature_Nuklear) {
    nk_sdl_shutdown();
  }
  WindowShutdown();
}

void Game::Update(float dt) {
  SDL_Event e;
  if (Config.GameFeatures & GameFeature_Nuklear) {
    nk_input_begin(Nk);
  }
  while (SDL_PollEvent(&e)) {
    WindowAdjustEventCoordinates(&e);

    if (e.type == SDL_QUIT) {
      ShouldQuit = true;
    }

    if (Config.GameFeatures & GameFeature_Nuklear) {
      nk_sdl_handle_event(&e);
    }
    WorkQueueHandleEvent(&e);
  }
  if (Config.GameFeatures & GameFeature_Nuklear) {
    nk_input_end(Nk);
  }

  if (Config.GameFeatures & GameFeature_ModelViewer) {
    ModelViewerComponent->Update(dt);
  }

  if (Config.GameFeatures & GameFeature_Sc3VirtualMachine) {
    VmComponent->Update();
  }

  if (Config.GameFeatures & GameFeature_Scene3D) {
    Scene3D->Update(dt);
  }
}

void Game::Render() {
  WindowUpdate();

  Rect viewport = WindowGetViewport();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (Config.GameFeatures & GameFeature_Scene3D) {
    Scene3D->Render();
  }

  for (uint32_t layer = 0; layer < Config.LayerCount; layer++) {
    // TODO
  }

  if (Config.GameFeatures & GameFeature_Nuklear) {
    if (g_GLDebug) {
      // Nuklear spams these
      glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                               NULL, GL_FALSE);
    }
    nk_sdl_render(NK_ANTI_ALIASING_OFF, viewport.Width, viewport.Height);
    if (g_GLDebug) {
      glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                               NULL, GL_TRUE);
    }
  }

  WindowDraw();
}

void Game::SetFlag(uint32_t flagId, uint32_t value) {
  uint32_t flagIndex = flagId >> 3;
  int flagValue = 1 << (flagId - 8 * (flagId >> 3));
  FlagWork[flagIndex] |= flagValue;
  if (!value) {
    FlagWork[flagIndex] ^= flagValue;
  }
}

bool Game::GetFlag(uint32_t flagId) {
  return ((uint8_t)(1 << (flagId - 8 * (flagId >> 3))) &
          *((uint8_t*)FlagWork + (flagId >> 3))) != 0;
}

}  // namespace Impacto