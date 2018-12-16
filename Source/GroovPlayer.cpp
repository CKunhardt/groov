/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "GroovAudioProcessor.h"
#include "GroovRenderer.h"
#include "GroovRenderWindow.h"
#include "GroovPlayer.h"

//==============================================================================
GroovPlayer::GroovPlayer(GroovAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	renderer.reset(new GroovRenderer());
	renderWindow.reset(new GroovRenderWindow("Groov Projection", renderer.get()));

	addAndMakeVisible(bpmLabel);
	bpmLabel.setJustificationType(Justification::topLeft);
	bpmLabel.setFont(Font(14.0f));

	// SLIDERS -----------------------
	addAndMakeVisible(sizeSlider);
	sizeSlider.setRange(1.0, 3.0, 0.01);
	sizeSlider.addListener(this);

	addAndMakeVisible(zoomLabel);
	zoomLabel.attachToComponent(&sizeSlider, true);

	addAndMakeVisible(spinSpeedSlider);
	spinSpeedSlider.setRange(0.0, 0.5, 0.001);
	spinSpeedSlider.addListener(this);
	spinSpeedSlider.setSkewFactor(0.5f);

	addAndMakeVisible(spinSpeedLabel);
	spinSpeedLabel.attachToComponent(&spinSpeedSlider, true);

	addAndMakeVisible(wiggleSlider);
	wiggleSlider.setRange(0.0, 10.0, 0.001);
	wiggleSlider.addListener(this);

	addAndMakeVisible(wiggleLabel);
	wiggleLabel.attachToComponent(&wiggleSlider, true);

	addAndMakeVisible(colorSatSlider);
	colorSatSlider.setRange(0.0, 1.0, 0.001);
	colorSatSlider.addListener(this);

	addAndMakeVisible(colorSatLabel);
	colorSatLabel.attachToComponent(&colorSatSlider, true);

	addAndMakeVisible(colorValSlider);
	colorValSlider.setRange(0.0, 1.0, 0.001);
	colorValSlider.addListener(this);

	addAndMakeVisible(colorValLabel);
	colorValLabel.attachToComponent(&colorValSlider, true);

	addAndMakeVisible(bgHueSlider);
	bgHueSlider.setRange(0.0, 360.0, 1.0);
	bgHueSlider.addListener(this);

	addAndMakeVisible(bgHueLabel);
	bgHueLabel.attachToComponent(&bgHueSlider, true);

	addAndMakeVisible(bgSatSlider);
	bgSatSlider.setRange(0.0, 1.0, 0.001);
	bgSatSlider.addListener(this);

	addAndMakeVisible(bgSatLabel);
	bgSatLabel.attachToComponent(&bgSatSlider, true);

	addAndMakeVisible(bgValSlider);
	bgValSlider.setRange(0.0, 1.0, 0.001);
	bgValSlider.addListener(this);

	addAndMakeVisible(bgValLabel);
	bgValLabel.attachToComponent(&bgValSlider, true);

	addAndMakeVisible(bgSpeedSlider);
	bgSpeedSlider.setRange(0, 250, 1);
	bgSpeedSlider.addListener(this);

	addAndMakeVisible(bgSpeedLabel);
	bgSpeedLabel.attachToComponent(&bgSpeedSlider, true);

	// TOGGLE BUTTONS -----------------------

	// this button toggles the feature that bounces the cubes
	addAndMakeVisible(enableScaleBounce);
	enableScaleBounce.onClick = [this] {renderer->doScaleBounce = enableScaleBounce.getToggleState(); };

	// This button toggles the feature that 'freezes' the animation by setting a bool in GroovRenderer to true
	addAndMakeVisible(freeze);
	freeze.onClick = [this] { renderer->frozen = freeze.getToggleState(); };

	// Cube controls
	spinSpeedSlider.setValue(0.01);
	sizeSlider.setValue(2.5);
	wiggleSlider.setValue(4.0);
	colorSatSlider.setValue(0.5);
	colorValSlider.setValue(1.0);

	// Background controls
	bgHueSlider.setValue(180.0);
	bgSatSlider.setValue(0.75);
	bgValSlider.setValue(1.0);
	bgSpeedSlider.setValue(125);

	startTimer(100);

    setSize (PLAYER_WIDTH, PLAYER_HEIGHT);
}

GroovPlayer::~GroovPlayer()
{
	renderer.reset();
	renderWindow.reset();
}

void GroovPlayer::sliderValueChanged(Slider*)
{
	renderer->scale = (float)sizeSlider.getValue();
	renderer->rotationSpeed = (float)spinSpeedSlider.getValue();
	renderer->wiggleSpeed = (float)wiggleSlider.getValue();
	renderer->colorSat = (float)colorSatSlider.getValue();
	renderer->colorVal = (float)colorValSlider.getValue();
	renderer->bgHue = (float)bgHueSlider.getValue();
	renderer->bgSat = (float)bgSatSlider.getValue();
	renderer->bgVal = (float)bgValSlider.getValue();
	renderer->bgSpeed = (int)bgSpeedSlider.getValue();
}

//==============================================================================
void GroovPlayer::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    /*g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);*/
}

void GroovPlayer::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	auto area = getLocalBounds().reduced(4);

	auto top = area.removeFromTop(PLAYER_HEIGHT - PARAM_HEIGHT);

	auto controls = top.removeFromRight(area.getWidth() / 2);
	freeze.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	enableScaleBounce.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	bgSatSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	bgValSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	bgHueSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	bgSpeedSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	colorSatSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	colorValSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	wiggleSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	spinSpeedSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));
	sizeSlider.setBounds(controls.removeFromBottom(PARAM_HEIGHT));

	top.removeFromRight(70);

	bpmLabel.setBounds(top);
}

void GroovPlayer::timerCallback()
{
	double bpm = processor.bpm;
	bpmLabel.setText(std::to_string(bpm), dontSendNotification);
	renderer->bpm = bpm;
}
