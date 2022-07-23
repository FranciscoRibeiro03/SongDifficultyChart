#include "IncludesList.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

MAKE_AUTO_HOOK_MATCH(DifficultyChart, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller *self) {

    DifficultyChart(self);

    if (getModConfig().Enabled.GetValue() == true) {
        UnityEngine::GameObject *screen = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(45.0f, 25.0f), UnityEngine::Vector3(getModConfig().XPos.GetValue(), getModConfig().YPos.GetValue(), getModConfig().ZPos.GetValue()),
        UnityEngine::Vector3(getModConfig().XRot.GetValue(), getModConfig().YRot.GetValue(), getModConfig().ZRot.GetValue()), 0.0f, true, true, 3);
    
        QuestUI::BeatSaberUI::CreateText(screen->get_transform(), "Test", UnityEngine::Vector2(15.0f, 0.0f));

        Resources::FindObjectsOfTypeAll<MenuTransitionsHelper*>()[0]->RestartGame(nullptr);
    }
    else if (getModConfig().Enabled.GetValue() == false) {
        Resources::FindObjectsOfTypeAll<MenuTransitionsHelper*>()[0]->RestartGame(nullptr);
    }

    

}