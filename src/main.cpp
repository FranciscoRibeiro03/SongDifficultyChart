#include "IncludesList.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if(firstActivation) {
        UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollView(self->get_transform());
        //UnityEngine::GameObject *floatContainer = QuestUI::BeatSaberUI::

        AddConfigValueToggle(container->get_transform(), getModConfig().Enabled)->get_gameObject();

        // MAKE MINI PREVIEW TO SEE UPDATES
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().XPos, 0, 0.5f, -20.0f, 20.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().YPos, 0, 0.5f, -20.0f, 20.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ZPos, 0, 0.5f, -20.0f, 20.0f);

        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().XRot, 0, 1.0f, -180.0f, 180.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().YRot, 0, 1.0f, -180.0f, 180.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ZRot, 0, 1.0f, -180.0f, 180.0f);

        UnityEngine::Transform *parent = container->get_transform();
        auto layout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);    layout->GetComponent<UnityEngine::UI::LayoutElement *>()->set_preferredWidth(90.0f);
        layout->set_childControlWidth(true);
        auto layoutParent = layout->get_transform();

        auto stringSetting = AddConfigValueStringSetting(layoutParent, getModConfig().meme);

        // MINI PREVIEW

        UnityEngine::GameObject *

        UnityEngine::GameObject *miniScreen = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(45.0f, 25.0f),
        UnityEngine::Vector3(getModConfig().XPos.GetValue() / 5, getModConfig().YPos.GetValue() / 5, getModConfig().ZPos.GetValue()),
        UnityEngine::Vector3(45.0f, 0.0f, 0.0f), 0.0f, true, true, 5);
        //if (QuestUI::BeatSaberUI::)

        UnityEngine::GameObject *settingsConsole = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(25.0f, 45.0f), UnityEngine::Vector3(-2.0f, 0.0f, 0.0f), UnityEngine::Vector3(0.0f, 25.0f, 0.0f), 0.0f, true, false);
    }
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