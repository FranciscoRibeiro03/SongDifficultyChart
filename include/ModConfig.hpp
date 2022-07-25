#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(Enabled, bool, "Enable Song Difficulty Chart", true);
    CONFIG_VALUE(XPos, float, "Change X Position", 0.0f);
    CONFIG_VALUE(YPos, float, "Change Y Position", -1.0f);
    CONFIG_VALUE(ZPos, float, "Change Z Position", 3.0f);
    CONFIG_VALUE(XRot, float, "Change X Rotation", 45.0f);
    CONFIG_VALUE(YRot, float, "Change Y Rotation", 0.0f);
    CONFIG_VALUE(ZRot, float, "Change Z Rotation", 0.0f)

    CONFIG_VALUE(SoftRestart, bool, "Show Changes", false);

    CONFIG_VALUE(meme, std::string, "Change Test Button Text", "Meme");

    CONFIG_INIT_FUNCTION(

        CONFIG_INIT_VALUE(Enabled);
        CONFIG_INIT_VALUE(XPos);
        CONFIG_INIT_VALUE(YPos);
        CONFIG_INIT_VALUE(ZPos);
        CONFIG_INIT_VALUE(XRot);
        CONFIG_INIT_VALUE(YRot);
        CONFIG_INIT_VALUE(ZRot);

        CONFIG_INIT_VALUE(SoftRestart);

        CONFIG_INIT_VALUE(meme);
    )

)