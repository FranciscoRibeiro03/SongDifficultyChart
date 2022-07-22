#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(Enabled, bool, "Enable Song Difficulty Chart", true);


    CONFIG_INIT_FUNCTION(

        CONFIG_INIT_VALUE(Enabled);
    )

)