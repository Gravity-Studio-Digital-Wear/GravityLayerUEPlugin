#pragma once

#include <vector>
#include <string>

using namespace::std;

namespace GravityLayer::Utils::APIResponse::UserResponse
{

    struct LoginResponse
    {
        string address;
        string challenge;
        string token;
    };

    struct MetadataAttributes
    {
        string name;
        string value;
    };

    struct ProductMetadata
    {
        string metaverseId;
        string modelUrl;
        string previewImage;
        vector<MetadataAttributes> attributes;
    };

    struct WardrobeData
    {
        string _id;
        string name;
        string description;
        vector<string> images;
        vector<ProductMetadata> metadata;
    };

    struct ProductData
    {

        WardrobeData product;
    };


    struct WardrobeResult
    {
        vector<ProductData> result;
    };
};
