#include "IncludesList.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;



MAKE_AUTO_HOOK_MATCH(DifficultyChart, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller *self) {

    DifficultyChart(self);

    if (getModConfig().Enabled.GetValue() == true) {
        UnityEngine::GameObject *screen = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(45.0f, 25.0f), UnityEngine::Vector3(getModConfig().Positions),
        UnityEngine::Vector3(getModConfig().Rotations), 0.0f, true, false);
    
        QuestUI::BeatSaberUI::CreateText(screen->get_transform(), getModConfig().meme.GetValue(), UnityEngine::Vector2(20.0f, 0.0f));

    }
    else if (getModConfig().Enabled.GetValue() == false) {
        
    }
}