#include "IncludesList.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

//MAKE_AUTO_HOOK_MATCH(PreviewInstaller, &System::Environment::SetEnvironmentVariable, void, System::Environment *self) {

    //PreviewInstaller(self);
//}

MAKE_AUTO_HOOK_MATCH(RefreshButton, &QuestUI::BeatSaberUI:: , void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    RefreshButton(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "Refresh", UnityEngine::Vector2(50.0f, 0.0f), UnityEngine::Vector2(20.0f, 10.0f), []() {

        Resources::FindObjectsOfTypeAll<MenuTransitionsHelper *>()[0]->RestartGame(nullptr);
    
    });

}