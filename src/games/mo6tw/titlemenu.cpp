#include "titlemenu.h"

#include "../../renderer2d.h"
#include "../../mem.h"
#include "../../inputsystem.h"
#include "../../ui/widgets/label.h"
#include "../../profile/ui/titlemenu.h"
#include "../../profile/games/mo6tw/titlemenu.h"
#include "../../profile/scriptvars.h"
#include "../../profile/game.h"

namespace Impacto {
namespace UI {
namespace MO6TW {

using namespace Impacto::Profile::TitleMenu;
using namespace Impacto::Profile::MO6TW::TitleMenu;
using namespace Impacto::Profile::ScriptVars;

using namespace Impacto::UI::Widgets::MO6TW;

void TitleMenu::MenuButtonOnClick(Widgets::Button* target) {
  ScrWork[SW_TITLECUR1] = target->Id;
  ChoiceMade = true;
}

void TitleMenu::SecondaryButtonOnClick(Widgets::Button* target) {
  ScrWork[SW_TITLECUR2] = target->Id;
  ChoiceMade = true;
}

TitleMenu::TitleMenu() {
  MainItems = new WidgetGroup();
  ContinueItems = new WidgetGroup();
  SystemItems = new WidgetGroup();

  auto onClick =
      std::bind(&TitleMenu::MenuButtonOnClick, this, std::placeholders::_1);
  auto secondaryOnClick = std::bind(&TitleMenu::SecondaryButtonOnClick, this,
                                    std::placeholders::_1);

  Sprite nullSprite = Sprite();
  nullSprite.Bounds = RectF(0.0f, 0.0f, 0.0f, 0.0f);

  // Initial Start menu button
  InitialStart =
      new TitleButton(0, MenuEntriesSprites[0], MenuEntriesHSprites[0],
                      nullSprite, glm::vec2(MenuEntriesX, MenuEntriesFirstY));
  InitialStart->OnClickHandler = onClick;
  MainItems->Add(InitialStart, FocusDirection::Vertical);

  // Lockable Extra Story menu button
  ExtraStory = new TitleButton(
      1, MenuEntriesSprites[1], MenuEntriesHSprites[1], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (1 * MenuEntriesYPadding)));
  ExtraStory->Enabled = false;
  ExtraStory->OnClickHandler = onClick;
  ExtraStory->DisabledSprite = MenuItemLockedSprite;
  MainItems->Add(ExtraStory, FocusDirection::Vertical);

  // Continue menu button
  Continue = new TitleButton(
      2, MenuEntriesSprites[2], MenuEntriesHSprites[2], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (2 * MenuEntriesYPadding)));
  Continue->OnClickHandler = onClick;
  MainItems->Add(Continue, FocusDirection::Vertical);

  // Lockable Memories menu button
  Memories = new TitleButton(
      3, MenuEntriesSprites[3], MenuEntriesHSprites[3], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (3 * MenuEntriesYPadding)));
  Memories->Enabled = false;
  Memories->OnClickHandler = onClick;
  Memories->DisabledSprite = MenuItemLockedSprite;
  MainItems->Add(Memories, FocusDirection::Vertical);

  // Encyclopedia menu button
  Encyclopedia = new TitleButton(
      4, MenuEntriesSprites[4], MenuEntriesHSprites[4], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (4 * MenuEntriesYPadding)));
  Encyclopedia->OnClickHandler = onClick;
  MainItems->Add(Encyclopedia, FocusDirection::Vertical);

  // System menu button
  System = new TitleButton(
      5, MenuEntriesSprites[5], MenuEntriesHSprites[5], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (5 * MenuEntriesYPadding)));
  System->OnClickHandler = onClick;
  MainItems->Add(System, FocusDirection::Vertical);

  // Exit menu button
  Exit = new TitleButton(
      6, MenuEntriesSprites[6], MenuEntriesHSprites[6], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (6 * MenuEntriesYPadding)));
  Exit->OnClickHandler = onClick;
  MainItems->Add(Exit, FocusDirection::Vertical);

  // Load secondary Continue menu button
  Load = new TitleButton(
      0, MenuEntriesSprites[10], MenuEntriesHSprites[10], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (3 * MenuEntriesYPadding)));
  Load->OnClickHandler = secondaryOnClick;
  ContinueItems->Add(Load, FocusDirection::Vertical);

  // Quick Load secondary Continue menu button
  QuickLoad = new TitleButton(
      1, MenuEntriesSprites[11], MenuEntriesHSprites[11], nullSprite,
      glm::vec2(MenuEntriesX - 20.0f,
                MenuEntriesFirstY + (4 * MenuEntriesYPadding)));
  QuickLoad->OnClickHandler = secondaryOnClick;
  ContinueItems->Add(QuickLoad, FocusDirection::Vertical);

  // Option secondary System menu button
  Option = new TitleButton(
      0, MenuEntriesSprites[18], MenuEntriesHSprites[18], nullSprite,
      glm::vec2(MenuEntriesX, MenuEntriesFirstY + (6 * MenuEntriesYPadding)));
  Option->OnClickHandler = secondaryOnClick;
  SystemItems->Add(Option, FocusDirection::Vertical);

  // System Save secondary System menu button
  SystemSave = new TitleButton(
      1, MenuEntriesSprites[20], MenuEntriesHSprites[20], nullSprite,
      glm::vec2(MenuEntriesX - 20.0f,
                MenuEntriesFirstY + (7 * MenuEntriesYPadding)));
  SystemSave->OnClickHandler = secondaryOnClick;
  SystemItems->Add(SystemSave, FocusDirection::Vertical);
}

void TitleMenu::Show() {
  if (State != Shown) {
    State = Shown;
    if (UI::FocusedMenu != 0) {
      LastFocusedMenu = UI::FocusedMenu;
      LastFocusedMenu->IsFocused = false;
    }
    IsFocused = true;
    UI::FocusedMenu = this;
    if (PressToStartAnimation.State == AS_Stopped)
      PressToStartAnimation.StartIn();
  }
}
void TitleMenu::Hide() {
  if (State != Hidden) {
    State = Hidden;
    MainItems->Hide();
    if (LastFocusedMenu != 0) {
      UI::FocusedMenu = LastFocusedMenu;
      LastFocusedMenu->IsFocused = true;
    } else {
      UI::FocusedMenu = 0;
    }
    IsFocused = false;
  }
}

void TitleMenu::Update(float dt) {
  PressToStartAnimation.Update(dt);
  PrimaryFadeAnimation.Update(dt);
  SecondaryFadeAnimation.Update(dt);
  if (GetFlag(SF_TITLEMODE)) {
    Show();
  } else {
    Hide();
  }

  if (State == Shown && IsFocused) {
    ExtraStory->Enabled = GetFlag(867);
    Memories->Enabled = (GetFlag(860) || GetFlag(861) || GetFlag(862) ||
                         GetFlag(863) || GetFlag(864));

    MainItems->Opacity =
        glm::smoothstep(0.0f, 1.0f, PrimaryFadeAnimation.Progress);
    MainItems->Update(dt);
    ContinueItems->Opacity =
        glm::smoothstep(0.0f, 1.0f, SecondaryFadeAnimation.Progress);
    ContinueItems->Update(dt);
    SystemItems->Opacity =
        glm::smoothstep(0.0f, 1.0f, SecondaryFadeAnimation.Progress);
    SystemItems->Update(dt);

    switch (ScrWork[SW_TITLEDISPCT]) {
      case 0: {
        // When returning to title menu from loading a game we need to hide the
        // continue sub-menu
        if (ContinueItems->IsShown) {
          SecondaryFadeAnimation.StartOut();
          MainItems->HasFocus = true;
          Load->Move(glm::vec2(-110.0f, 0.0f));
          QuickLoad->Move(glm::vec2(-130.0f, 0.0f));
          Memories->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding));
          Encyclopedia->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding));
          System->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding));
          Exit->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding));
          ContinueItems->Hide();
        }
      } break;
      case 3: {  // Main Menu Fade In
        if (!MainItems->IsShown && ScrWork[SW_TITLECT] == 0) {
          MainItems->Show();
          MainItems->Opacity = 0.0f;
          PrimaryFadeAnimation.DurationIn = 0.3f;
          PrimaryFadeAnimation.DurationOut = 0.3f;
          PrimaryFadeAnimation.StartIn();
        }
      } break;
      case 7: {  // Secondary menu Continue Fade In
        if (!ContinueItems->IsShown && ScrWork[SW_TITLECT] == 0) {
          ContinueItems->Show();
          ContinueItems->Opacity = 0.0f;
          MainItems->HasFocus = false;

          SecondaryFadeAnimation.DurationIn = 0.512f;
          SecondaryFadeAnimation.DurationOut = 0.512f;
          SecondaryFadeAnimation.StartIn();

          Load->Move(glm::vec2(110.0f, 0.0f), 0.512f);
          QuickLoad->Move(glm::vec2(130.0f, 0.0f), 0.512f);

          Memories->Move(glm::vec2(0.0f, 2.0f * MenuEntriesYPadding), 0.512f);
          Encyclopedia->Move(glm::vec2(0.0f, 2.0f * MenuEntriesYPadding),
                             0.512f);
          System->Move(glm::vec2(0.0f, 2.0f * MenuEntriesYPadding), 0.512f);
          Exit->Move(glm::vec2(0.0f, 2.0f * MenuEntriesYPadding), 0.512f);
        } else if (ContinueItems->IsShown && ScrWork[SW_TITLECT] == 32) {
          SecondaryFadeAnimation.StartOut();

          Load->Move(glm::vec2(-110.0f, 0.0f), 0.512f);
          QuickLoad->Move(glm::vec2(-130.0f, 0.0f), 0.512f);

          Memories->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding), 0.512f);
          Encyclopedia->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding),
                             0.512f);
          System->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding), 0.512f);
          Exit->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding), 0.512f);
        } else if (ScrWork[SW_TITLECT] == 0) {
          ContinueItems->Hide();
          MainItems->HasFocus = true;
        }
      } break;
      case 11: {
        if (!SystemItems->IsShown && ScrWork[SW_TITLECT] == 0) {
          SystemItems->Show();
          SystemItems->Opacity = 0.0f;
          MainItems->HasFocus = false;

          SecondaryFadeAnimation.DurationIn = 0.512f;
          SecondaryFadeAnimation.DurationOut = 0.512f;
          SecondaryFadeAnimation.StartIn();

          Option->Move(glm::vec2(110.0f, 0.0f), 0.512f);
          SystemSave->Move(glm::vec2(130.0f, 0.0f), 0.512f);

          Exit->Move(glm::vec2(0.0f, 2.0f * MenuEntriesYPadding), 0.512f);
        } else if (SystemItems->IsShown && ScrWork[SW_TITLECT] == 32) {
          SecondaryFadeAnimation.StartOut();

          Option->Move(glm::vec2(-110.0f, 0.0f), 0.512f);
          SystemSave->Move(glm::vec2(-130.0f, 0.0f), 0.512f);

          Exit->Move(glm::vec2(0.0f, -2.0f * MenuEntriesYPadding), 0.512f);
        } else if (ScrWork[SW_TITLECT] == 0) {
          SystemItems->Hide();
          MainItems->HasFocus = true;
        }
      } break;
    }
  }
}

void TitleMenu::Render() {
  if (State != Hidden && GetFlag(SF_TITLEMODE)) {
    if (ScrWork[SW_MENUCT] != 100) {
      switch (ScrWork[SW_TITLEDISPCT]) {
        case 0:  // Initial animation
          break;
        case 1: {  // Press to start
          Renderer2D::DrawSprite(BackgroundSprite, glm::vec2(0.0f));
          Renderer2D::DrawSprite(LogoSprite, glm::vec2(LogoX, LogoY));
          Renderer2D::DrawSprite(CopyrightSprite,
                                 glm::vec2(CopyrightX, CopyrightY));
          glm::vec4 col = glm::vec4(1.0f);
          col.a = glm::smoothstep(0.0f, 1.0f, PressToStartAnimation.Progress);
          Renderer2D::DrawSprite(PressToStartSprite,
                                 glm::vec2(PressToStartX, PressToStartY), col);
        } break;
        case 2: {  // Transition between Press to start and menus
          Renderer2D::DrawSprite(MenuBackgroundSprite, glm::vec2(0.0f));
        } break;
        case 3:    // Main Menu Fade In
        case 4: {  // Main Menu
          Renderer2D::DrawSprite(MenuBackgroundSprite, glm::vec2(0.0f));
          MainItems->Render();
        } break;
        case 7:    // Secondary menu Continue Fade In
        case 8: {  // Secondary menu Continue
          Renderer2D::DrawSprite(MenuBackgroundSprite, glm::vec2(0.0f));
          ContinueItems->Render();
          MainItems->Render();
        } break;
        case 11:    // Secondary menu System Fade In
        case 12: {  // Secondary menu System
          Renderer2D::DrawSprite(MenuBackgroundSprite, glm::vec2(0.0f));
          SystemItems->Render();
          MainItems->Render();
        } break;
      }
    }

    int maskAlpha = ScrWork[SW_TITLEMASKALPHA];
    glm::vec4 col = ScrWorkGetColor(SW_TITLEMASKCOLOR);
    col.a = glm::min(maskAlpha / 255.0f, 1.0f);
    Renderer2D::DrawRect(
        RectF(0.0f, 0.0f, Profile::DesignWidth, Profile::DesignHeight), col);
  }
}

}  // namespace MO6TW
}  // namespace UI
}  // namespace Impacto