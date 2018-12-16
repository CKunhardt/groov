/*
  ==============================================================================

   This file is part of the JUCE examples.
   Copyright (c) 2017 - ROLI Ltd.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
	This file contains a bunch of miscellaneous utilities that are
	used by the various demos.
*/

//==============================================================================

inline Colour getUIColourIfAvailable(LookAndFeel_V4::ColourScheme::UIColour uiColour, Colour fallback = Colour(0xff4d4d4d)) noexcept
{
	if (auto* v4 = dynamic_cast<LookAndFeel_V4*> (&LookAndFeel::getDefaultLookAndFeel()))
		return v4->getCurrentColourScheme().getUIColour(uiColour);

	return fallback;
}

inline InputStream* createAssetInputStream(const char* resourcePath)
{
#if JUCE_ANDROID
	ZipFile apkZip(File::getSpecialLocation(File::invokedExecutableFile));
	return apkZip.createStreamForEntry(apkZip.getIndexOfFileName("assets/" + String(resourcePath)));
#else
#if JUCE_IOS
	auto assetsDir = File::getSpecialLocation(File::currentExecutableFile)
		.getParentDirectory().getChildFile("Assets");
#elif JUCE_MAC
	auto assetsDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Groov").getChildFile("Assets");
#else
	auto assetsDir = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile("Groov").getChildFile("Assets");
#endif

	auto resourceFile = assetsDir.getChildFile(resourcePath);
	jassert(resourceFile.existsAsFile());

	return resourceFile.createInputStream();
#endif
}

inline String loadEntireAssetIntoString(const char* assetName)
{
	std::unique_ptr<InputStream> input(createAssetInputStream(assetName));

	if (input == nullptr)
		return {};

	return input->readString();
}