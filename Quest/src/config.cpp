#include "config.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

static ModInfo modInfo = {ID, VERSION};
extern Logger& getLogger();

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

config_t config;

void SaveConfig() {
    INFO("Saving Configuration...");
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    getConfig().config.AddMember("enabled", config.enabled, allocator);
    getConfig().config.AddMember("gravitySetting", config.gravitySetting, allocator);
    getConfig().config.AddMember("frozen", config.frozen, allocator);
    getConfig().config.AddMember("upSpeed", config.upSpeed, allocator);
    getConfig().Write();
    INFO("Saved Configuration!");
}

bool LoadConfig() {
    INFO("Loading config...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;
    if(doc.HasMember("enabled") && doc["enabled"].IsBool()) {
        config.enabled = doc["enabled"].GetBool();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("gravitySetting") && doc["gravitySetting"].IsBool()) {
        config.gravitySetting = doc["gravitySetting"].GetBool();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("frozen") && doc["frozen"].IsBool()) {
        config.frozen = doc["frozen"].GetBool();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("upSpeed") && doc["upSpeed"].GetInt()) {
        config.upSpeed = doc["upSpeed"].GetInt();
    } else {
        foundEverything = false;
    }
    return foundEverything;
}