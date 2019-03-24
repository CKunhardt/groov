/*
  ==============================================================================

    GroovRenderWindow.cpp
    Created: 15 Dec 2018 2:51:03pm
    Author:  ClintonK

  ==============================================================================
*/

#include "GroovRenderWindow.h"
#include "GroovRenderer.h"

GroovRenderWindow::GroovRenderWindow(String name, GroovRenderer* r) : TopLevelWindow(name, true)
{
	addAndMakeVisible(r);
	if (Desktop::getInstance().getDisplays().displays.size() > 1) {
		auto screen = Desktop::getInstance().getDisplays().displays[1].totalArea;
		setBounds(screen);
	}
	else {
		auto screen = Desktop::getInstance().getDisplays().getMainDisplay().totalArea;
		setBounds(screen);
	}
	setOpaque(true);
	setVisible(true);
	addToDesktop();
}

GroovRenderWindow::~GroovRenderWindow()
{
}