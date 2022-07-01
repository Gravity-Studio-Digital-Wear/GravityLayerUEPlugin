#pragma once
#include "IFetchWearablesByMetaverseId.h"

namespace GravityLayer::Utils
{
    class Connection : public IFetchWearablesByMetaverseId
    {
    private:

        bool ConnectionEstablished;

        string _address;
        string _uuid;
        string _signature;
        string _jwt;
        string _apiUrl;
        // Func<string, Task<string>> _signMessage;

    public:
        Connection(string apiUrl, string address/*, Func<string, Task<string>> signMessage*/);

        string EstablishConnection();

        void Challenge();

        void Sign(string message);

        void AuthLogin();

        string FetchWearablesByMetaverseId(string metaverseId);

        string EstablishConnection(string testToken);

    };
};