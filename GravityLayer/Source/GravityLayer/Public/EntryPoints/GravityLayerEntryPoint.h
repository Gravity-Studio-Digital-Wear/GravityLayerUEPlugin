#pragma once
#include <string>
#include <Utils/Connection.h>
#include <Wearables/Wardrobe.h>

namespace GravityLayer
{
    /// <summary>
    /// The GravityLayerEntryPoint class contains all public points to deal with Gravity Layer API. It serves as an example.
    /// </summary>
    /// <remarks>
    /// Authentication is done by receiving a JWT token for a User via signing a message from Gravity Layer API. See details in documentation.
    /// </remarks>
    class GravityLayerEntryPoint
    {
    public:
        GravityLayer::Utils::Connection GLayerConnection;
        GravityLayer::Wearables::Wardrobe Wardrobe;

    private: string _apiUrl;

           string _account;

    public: GravityLayerEntryPoint(string apiUrl, string account, string metaverseId/*, Func<string, Task<string>> signMessage*/);

    };
};