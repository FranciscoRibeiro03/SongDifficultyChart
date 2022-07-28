#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(Enabled, bool, "Enable Song Difficulty Chart", true);
    CONFIG_VALUE(Positions, UnityEngine::Vector3, "Change Position", UnityEngine::Vector3(0.0f, -1.0f, 3.0f));
    CONFIG_VALUE(Rotations, UnityEngine::Vector3, "Change Rotation", UnityEngine::Vector3(45.0f, 0.0f, 0.0f));

    CONFIG_VALUE(Frequency, float, "Change The Point Frequency", 1.0f);

    CONFIG_VALUE(SoftRestart, bool, "Show Changes", false);

    CONFIG_VALUE(meme, std::string, "Change Test Button Text", "Meme");

    CONFIG_INIT_FUNCTION(

        CONFIG_INIT_VALUE(Enabled);
        CONFIG_INIT_VALUE(Positions);
        CONFIG_INIT_VALUE(Rotations);

        CONFIG_INIT_VALUE(Frequency);

        CONFIG_INIT_VALUE(SoftRestart);

        CONFIG_INIT_VALUE(meme);
    )

)