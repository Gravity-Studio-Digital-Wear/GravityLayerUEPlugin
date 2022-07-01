#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include <string>
using namespace::std;

namespace GravityLayer::Utils
{
    static class Downloader
    {
    public:
        static UTexture2D DownloadImage(string mediaUrl);
    
        static char[] DownloadAvatar(string url);
       
    };
};
