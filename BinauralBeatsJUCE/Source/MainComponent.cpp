#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class MainContentComponent : public AudioAppComponent,
	public Slider::Listener
{
public:
	MainContentComponent()
		: currentSampleRate(0.0),
		currentAngleL(0.0),
		angleDeltaL(0.0),
		currentAngleR(0.0),
		angleDeltaR(0.0),

		currentFrequencyL(440.0),
		targetFrequencyL(currentFrequencyL),

		currentFrequencyR(441.0),
		targetFrequencyR(currentFrequencyR),

		currentLevel(0.125),
		targetLevel(currentLevel)

	{
		addAndMakeVisible(frequencySliderL);
		frequencySliderL.setRange(50.0, 5000.0);
		frequencySliderL.setSkewFactorFromMidPoint(500.0);
		frequencySliderL.setValue(currentFrequencyL, dontSendNotification);
		frequencySliderL.addListener(this);

		addAndMakeVisible(frequencySliderR);
		frequencySliderR.setRange(50.0, 5000.0);
		frequencySliderR.setSkewFactorFromMidPoint(500.0);
		frequencySliderR.setValue(currentFrequencyR, dontSendNotification);
		frequencySliderR.addListener(this);

		addAndMakeVisible(levelSlider);
		levelSlider.setRange(0.0, 0.25);
		levelSlider.setValue(currentLevel, dontSendNotification);
		levelSlider.addListener(this);

		setSize(600, 100);
		setAudioChannels(0, 2); // no inputs, one output
	}

	~MainContentComponent()
	{
		shutdownAudio();
	}

	void resized() override
	{
		frequencySliderL.setBounds(10, 10, getWidth() - 20, 20);
		frequencySliderR.setBounds(10, 40, getWidth() - 20, 20);
		levelSlider.setBounds(10, 70, getWidth() - 20, 20);
	}

	void sliderValueChanged(Slider* slider) override
	{
		if (slider == &frequencySliderL)
			targetFrequencyL = frequencySliderL.getValue();

		if (slider == &frequencySliderR)
			targetFrequencyR = frequencySliderR.getValue();

		if (slider == &levelSlider)
			targetLevel = levelSlider.getValue();
	}

	void updateAngleDeltaL()
	{
		const double cyclesPerSample = frequencySliderL.getValue() / currentSampleRate;
		angleDeltaL = cyclesPerSample * 2.0 * double_Pi;
	}

	void updateAngleDeltaR()
	{
		const double cyclesPerSample = frequencySliderR.getValue() / currentSampleRate;
		angleDeltaR = cyclesPerSample * 2.0 * double_Pi;
	}

	void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override
	{
		currentSampleRate = sampleRate;
		updateAngleDeltaL();
		updateAngleDeltaR();
	}

	void releaseResources() override
	{
	}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		const float level = levelSlider.getValue();

		const double localTargetFrequencyL = targetFrequencyL;
		const double localTargetFrequencyR = targetFrequencyR;
		const double localTargetLevel = targetLevel;
		double frequencyIncrementL = 0.0;
		double frequencyIncrementR = 0.0;
		double levelIncrement = 0.0;

		// To smoothly change frequency
		if (localTargetFrequencyL != currentFrequencyL)
		{
			frequencyIncrementL = (localTargetFrequencyL - currentFrequencyL) / bufferToFill.numSamples;
		}
		else
		{
			frequencyIncrementL = 0;
		}
		if (localTargetFrequencyR != currentFrequencyR)
		{
			frequencyIncrementR = (localTargetFrequencyR - currentFrequencyR) / bufferToFill.numSamples;
		}
		else
		{
			const double frequencyIncrementR = 0;
		}
		if (localTargetLevel != currentLevel)
		{
			levelIncrement = (localTargetLevel - currentLevel) / bufferToFill.numSamples;
		}
		else
		{
			levelIncrement = 0;
		}
		for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {

			float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

			if (channel == 0) {
				for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
				{
					const float currentSampleL = (float)std::sin(currentAngleL);
					currentFrequencyL += frequencyIncrementL;
					updateAngleDeltaL();
					currentAngleL += angleDeltaL;
					currentLevel += levelIncrement;
					buffer[sample] = currentSampleL * currentLevel;
				}
			}
			else {
				for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
				{
					const float currentSampleR = (float)std::sin(currentAngleR);
					currentFrequencyR += frequencyIncrementR;
					updateAngleDeltaR();
					currentAngleR += angleDeltaR;
					currentLevel += levelIncrement;
					buffer[sample] = currentSampleR * currentLevel;
				}

			}
		}
		currentFrequencyL = localTargetFrequencyL;
		currentFrequencyR = localTargetFrequencyR;
		currentLevel = localTargetLevel;

	}






private:
	Slider frequencySliderL;
	Slider frequencySliderR;
	Slider levelSlider;

	double currentSampleRate, currentAngleL, angleDeltaL, currentAngleR, angleDeltaR;// [1]
	double currentFrequencyL, targetFrequencyL; // to smoothly change frequency
	double currentFrequencyR, targetFrequencyR; // to smoothly change frequency
	double currentLevel, targetLevel; // to smoothly change level

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};

Component* createMainContentComponent() { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
