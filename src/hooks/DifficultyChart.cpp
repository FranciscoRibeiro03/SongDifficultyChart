#include "hooks.hpp"
#include "modloader/shared/modloader.hpp"
#include "ModConfig.hpp"

MAKE_AUTO_HOOK_MATCH(DifficultyChart, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    DifficultyChart(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *
}