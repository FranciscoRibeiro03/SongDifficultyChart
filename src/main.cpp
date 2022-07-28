#include "IncludesList.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if (firstActivation) {
        UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollView(self->get_transform());

        AddConfigValueIncrementVector3(container->get_transform(), getModConfig().Positions, 2, 1.0f);
        AddConfigValueIncrementVector3(container->get_transform(), getModConfig().Rotations, 2, 1.0f);

        QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "Refresh", UnityEngine::Vector2(60.0f, 0.0f), UnityEngine::Vector2(20.0f, 10.0f), []() {
            Resources::FindObjectsOfTypeAll<MenuTransitionsHelper *>()[0]->RestartGame(nullptr);
        });

        UnityEngine::Transform *parent = container->get_transform();
        auto layout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);    layout->GetComponent<UnityEngine::UI::LayoutElement *>()->set_preferredWidth(90.0f);
        auto layoutParent = layout->get_transform();

        auto stringSetting = AddConfigValueStringSetting(layoutParent, getModConfig().meme);

    }
}

void DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    UnityEngine::Resources::FindObjectsOfTypeAll<MenuTransitionsHelper *>()[0]->RestartGame(nullptr);
}



// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing QuestUI");

    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);

    getLogger().info("Installed QuestUI!");

    getModConfig().Init(modInfo);

    getLogger().info("Installing SongDifficultyChart");
    
    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    getLogger().info("Installed SongDifficultyChart!");
}