/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AmpPulserAudioProcessor::AmpPulserAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

AmpPulserAudioProcessor::~AmpPulserAudioProcessor()
{
}

//==============================================================================
const juce::String AmpPulserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AmpPulserAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AmpPulserAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AmpPulserAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AmpPulserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AmpPulserAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AmpPulserAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AmpPulserAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AmpPulserAudioProcessor::getProgramName (int index)
{
    return {};
}

void AmpPulserAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AmpPulserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSampleRate = sampleRate;
    mCurrentAngle [0] = juce::degreesToRadians(0.0);
    mCurrentAngle [1] = juce::degreesToRadians(180.0);
    
    
    
    
    
}

void AmpPulserAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AmpPulserAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AmpPulserAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    if (mPulserFreqSliderValue == 0.0)
        return;
    
    //channel-level for loop
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample <buffer.getNumSamples(); ++sample)
        {
            //increment the LFO phase angle by the delta so it moves forward for the next repetition
            // get the sin of our current sample which would give us one sample of the LFO sample
            double lfoSample = getLfoSample(channel);
            
            
            //egt the sin of the current angle to compute one sample of the LFO signal
            
            advancedLfoPhase(channel);
            
            lfoSample =reRangeLfo(lfoSample);
            
            

            //re-range the outpu of the sin for our purpose
            
            
            //apply the LFO signal to affect the amplitude of our input signal
            
            channelData[sample]*=lfoSample;
            
            //dont forget to wrap at Pi
            

            
        }
        // ..do something to the data...
    }
    
}
double AmpPulserAudioProcessor::getLfoSample(int channel)
{
    double sample =std::sin(mCurrentAngle[channel]);
    return sample;
}


void AmpPulserAudioProcessor::advancedLfoPhase(int channel)
{
mCurrentAngle[channel] += mAngleDelta;

mCurrentAngle[channel]=std::fmod(mCurrentAngle[channel],
                                 juce::MathConstants<double>::twoPi);
}
double AmpPulserAudioProcessor::reRangeLfo(double sample)
{
    sample+=1.0;
    sample*=5.0;
    return sample;
}

//==============================================================================
bool AmpPulserAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AmpPulserAudioProcessor::createEditor()
{
    return new AmpPulserAudioProcessorEditor (*this); 
}

//==============================================================================
void AmpPulserAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AmpPulserAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmpPulserAudioProcessor();
}
