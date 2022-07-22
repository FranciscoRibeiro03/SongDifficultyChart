#include "hooks.hpp"
#include "modloader/shared/modloader.hpp"
#include "ModConfig.hpp"
#include "main.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "GlobalNamespace/GameplayCoreInstaller.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace QuestUI::BeatSaberUI;

MAKE_AUTO_HOOK_MATCH(DifficultyChart, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller *self) {

    DifficultyChart(self);

    if (getModConfig().Enabled.GetValue() == true) {
        UnityEngine::GameObject *screen = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(45.0f, 25.0f), UnityEngine::Vector3(0.0f, 2.0f, 2.0f),
        UnityEngine::Vector3(0, 0, 0), 0.0f, true, true, 3);
    
        QuestUI::BeatSaberUI::CreateText(screen->get_transform(), "Test");
    
    }
    else {
        
    }

    

}