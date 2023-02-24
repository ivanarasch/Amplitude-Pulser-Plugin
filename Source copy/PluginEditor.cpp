/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AmpPulserAudioProcessorEditor::AmpPulserAudioProcessorEditor (AmpPulserAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setResizable(true,true);
    setResizeLimits(200,100,1000,600);
    setSize (400, 300);
    
    mPulserFreqSlider.setRange(0.0,10.0);
    mPulserFreqSlider.setValue(PULSER_FREQ_INIT);
    addAndMakeVisible(&mPulserFreqSlider);
    mPulserFreqSlider.addListener(this);
    
    mPhaseOffsetSlider.setRange(0.0,180.0);
    mPhaseOffsetSlider.setValue(PHASE_OFFSET_INIT);
    addAndMakeVisible(&mPhaseOffsetSlider);
    mPhaseOffsetSlider.addListener(this);
    
    
    
    
    
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
}

AmpPulserAudioProcessorEditor::~AmpPulserAudioProcessorEditor()
{
    mPulserFreqSlider.removeListener(this); //this means a pointer to a class u are refering to
    mPhaseOffsetSlider.removeListener(this);
    
}

//==============================================================================
void AmpPulserAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    //assign the value of the processi's mPulserFreqSliderValue varible with the current slider value
    audioProcessor.mPulserFreqSliderValue = mPulserFreqSlider.getValue();
    audioProcessor.mPhaseOffsetSliderValue = mPhaseOffsetSlider.getValue();
    
    auto cysclesPerSample = audioProcessor.mPulserFreqSliderValue / audioProcessor.mSampleRate;
    audioProcessor.mAngleDelta = cysclesPerSample * juce::MathConstants<double>::twoPi;
    
    
    
    DBG("LFO Freq" + juce::String(audioProcessor.mPulserFreqSliderValue)+ "Angle Delta" +
        juce::String(audioProcessor.mAngleDelta));
    
}
void AmpPulserAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    
}

void AmpPulserAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    mPulserFreqSlider.setBounds(50,50,300,50);
    mPhaseOffsetSlider.setBounds(25,25,200,25);
}
