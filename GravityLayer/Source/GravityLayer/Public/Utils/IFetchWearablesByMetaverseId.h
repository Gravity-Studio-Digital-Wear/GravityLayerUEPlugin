#pragma once
#include <string>
using namespace::std;

namespace GravityLayer::Utils
{
	class IFetchWearablesByMetaverseId
	{
		virtual string FetchWearablesByMetaverseId(string metaverseId) = 0;
	};
};