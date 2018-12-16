/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GroovAudioProcessor.h"

//==============================================================================
/**
*/

class GroovRenderer;
class GroovRenderWindow;

class GroovPlayer  : public AudioProcessorEditor,
					 private Slider::Listener,
					 private Timer
{
public:
    GroovPlayer (GroovAudioProcessor& p);
    ~GroovPlayer();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	const int PLAYER_WIDTH = 400;
	const int PLAYER_HEIGHT = 300;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GroovAudioProcessor& processor;
	std::unique_ptr<GroovRenderer> renderer;
	std::unique_ptr<GroovRenderWindow> renderWindow;

	void timerCallback() override;

	void sliderValueChanged(Slider*) override;

	Label spinSpeedLabel{ {}, "Speed: " },
		wiggleLabel{ {}, "Wiggle: " },
		colorSatLabel{ {}, "Saturation: " },
		colorValLabel{ {}, "Brightness: " },
		bgHueLabel{ {}, "BG Hue: " },
		bgSatLabel{ {}, "BG Saturation" },
		bgValLabel{ {}, "BG Brightness" },
		bgSpeedLabel{ {}, "BG Speed" },
		zoomLabel{ {}, "Zoom: " };

	Label bpmLabel;

	Slider spinSpeedSlider,
		sizeSlider,
		wiggleSlider,
		colorSatSlider,
		colorValSlider,
		bgHueSlider,
		bgSpeedSlider,
		bgSatSlider,
		bgValSlider;

	ToggleButton enableScaleBounce{ "Enable Bouncing" },
		freeze{ "FREEZE!" };

	const int PARAM_HEIGHT = 25;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GroovPlayer)
};
