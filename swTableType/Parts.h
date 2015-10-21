#pragma once
#include "Part.h"

using System::Collections::Generic::Dictionary;

ref class Parts :
public Dictionary<string^, Part^> {
private:
	Dictionary<string^, Part^ > _innerDict;
public:
	Parts();
};

