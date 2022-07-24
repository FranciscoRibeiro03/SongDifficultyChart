#include "IncludesList.hpp"

DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if(firstActivation) {
        UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollView(self->get_transform());

        AddConfigValueToggle(container->get_transform(), getModConfig().Enabled)->get_gameObject();

        // MAKE MINI PREVIEW TO SEE UPDATES
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().XPos, 0, 0.5f, -20.0f, 20.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().YPos, 0, 0.5f, -20.0f, 20.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ZPos, 0, 0.5f, -20.0f, 20.0f);

        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().XRot, 0, 1.0f, -180.0f, 180.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().YRot, 0, 1.0f, -180.0f, 180.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ZRot, 0, 1.0f, -180.0f, 180.0f);

        AddConfigValueToggle(container->get_transform(), getModConfig().EnableEnvironment)->get_gameObject();
        //QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), getModConfig().EnableEnvironment);

        // MINI PREVIEW
        float xPos = getModConfig().XPos.GetValue() / 2;
        float yPos = getModConfig().YPos.GetValue() / 2;
        float zPos = getModConfig().ZPos.GetValue() / 2;

        UnityEngine::GameObject *miniScreen = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(45.0f, 25.0f), UnityEngine::Vector3(xPos, yPos, zPos), UnityEngine::Vector3(45.0f, 0.0f, 0.0f), 0.0f, true, true, 5);
        //if (QuestUI::BeatSaberUI::)
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

    getLogger().info("Installing SongDifficultyChart hooks");
    
    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    getLogger().info("Installed all SongDifficultyChart hooks!");
}