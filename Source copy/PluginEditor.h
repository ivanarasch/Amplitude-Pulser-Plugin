/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AmpPulserAudioProcessorEditor  : public juce::AudioProcessorEditor,public juce::Slider::Listener
{
public:
    AmpPulserAudioProcessorEditor (AmpPulserAudioProcessor&);
    ~AmpPulserAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AmpPulserAudioProcessor& audioProcessor;
    
    
    juce::Slider mPulserFreqSlider;
    juce::Slider mPhaseOffsetSlider;
    //add Slider callback
    
    void sliderValueChanged(juce::Slider*slider)override;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpPulserAudioProcessorEditor)
};
