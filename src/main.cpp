#include "main.hpp"
#include "modloader/shared/modloader.hpp"
#include "ModConfig.hpp"
#include "hooks.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"

using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;

DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

void DidActivate(HMUI::ViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if(firstActivation) {
        UnityEngine::GameObject *container = QuestUI::BeatSaberUI::CreateScrollView(self->get_transform());

        AddConfigValueToggle(container->get_transform(), getModConfig().Enabled)->get_gameObject();

        // MAKE MINI PREVIEW TO SEE UPDATES
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().XPos, 0, 1.0f, -20.0f, 20.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().YPos, 0, 1.0f, -20.0f, 20.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ZPos, 0, 1.0f, -20.0f, 20.0f);

        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().XRot, 0, 1.0f, -180.0f, 180.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().YRot, 0, 1.0f, -180.0f, 180.0f);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ZRot, 0, 1.0f, -180.0f, 180.0f);
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