/*
  ==============================================================================

    GroovRenderWindow.h
    Created: 15 Dec 2018 2:51:03pm
    Author:  ClintonK

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class GroovRenderer;

class GroovRenderWindow : public TopLevelWindow
{
public:
	GroovRenderWindow(String name, GroovRenderer* r);
	~GroovRenderWindow();

	void paint(Graphics& g) {};
};