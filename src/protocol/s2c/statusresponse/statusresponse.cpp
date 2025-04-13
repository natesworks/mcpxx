#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "statusresponse.h"

using ordered_json = nlohmann::ordered_json;

StatusResponse::StatusResponse(CallingInstance &ci) : Packet(ci), ci(ci) {}

StatusResponse::~StatusResponse() {}

void StatusResponse::read()
{
    ordered_json data = ordered_json::parse(ci.stream.readString());
    version = data["version"]["name"];
    protocolVersion = data["version"]["protocol"];
    maxPlayers = data["players"]["max"];
    onlinePlayers = data["players"]["online"];

    for (auto& element : data["players"]["sample"])
    {
        std::map<std::string, std::string> player = {{"name", element["name"]}, {"id", element["id"]}};
        players.push_back(player);
    }

    description = data["description"]["text"];

    if (data.contains("favicon"))
    {
        favicon = data["favicon"];
    }
    else
    {
        favicon = "";
    }

    enforcesSecureChat = data["enforcesSecureChat"];
}

void StatusResponse::write()
{
    ordered_json data;
    data["version"]["name"] = version;
    data["version"]["protocol"] = protocolVersion;
    data["players"]["max"] = maxPlayers;
    data["players"]["online"] = onlinePlayers;

    data["players"]["sample"] = ordered_json::array();

    for (const auto& player : players)
    {
        ordered_json playerJson;
        playerJson["name"] = player.at("name");
        playerJson["id"] = player.at("id");
        data["players"]["sample"].push_back(playerJson);
    }

    data["description"]["text"] = description;

    if (!favicon.empty())
    {
        data["favicon"] = favicon;
    }

    data["enforcesSecureChat"] = enforcesSecureChat;

    Logger::debug(data.dump());

    ci.stream.writeString(data.dump());
    ci.stream.writePacketHeader(ci.packetID);
}

uint16_t StatusResponse::getPacketID()
{
    return 0x0;
}