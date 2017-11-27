//-------------------------------------------------------------------------
// Simple back-propagation neural network example
// 2017 - Bobby Anguelov
// MIT license: https://opensource.org/licenses/MIT
//-------------------------------------------------------------------------

#include "NeuralNetwork.h"
#include <assert.h>
#include <stdlib.h>
#include <ctime>
#include <random>

//-------------------------------------------------------------------------

	Network::Network(int numInputs,int numHidden, int numOutputs)
		: m_numInputs(numInputs)
		, m_numHidden(numHidden)
		, m_numOutputs(numOutputs)
	{
		assert(m_numInputs > 0 && m_numOutputs > 0 && m_numHidden > 0);
		InitializeNetwork();
		InitializeWeights();
	}

	Network::Network(int numInputs, int numHidden, int numOutputs, std::vector<double> const& weights)
		: m_numInputs(numInputs)
		, m_numHidden(numHidden)
		, m_numOutputs(numOutputs)
	{
		assert(m_numInputs > 0 && m_numOutputs > 0 && m_numHidden > 0);
		InitializeNetwork();
		LoadWeights(weights);
	}

	void Network::InitializeNetwork()
	{
		// Create storage and initialize the neurons and the outputs
		//-------------------------------------------------------------------------

		// Add bias neurons
		int32_t const totalNumInputs = m_numInputs + 1;
		int32_t const totalNumHiddens = m_numHidden + 1;

		m_inputNeurons.resize(totalNumInputs);
		m_hiddenNeurons.resize(totalNumHiddens);
		m_outputNeurons.resize(m_numOutputs);

		// Set bias values
		m_inputNeurons.back() = -1.0;
		m_hiddenNeurons.back() = -1.0;

		// Create storage and initialize and layer weights
		//-------------------------------------------------------------------------

		int32_t const numInputHiddenWeights = totalNumInputs * totalNumHiddens;
		int32_t const numHiddenOutputWeights = totalNumHiddens * m_numOutputs;
		m_weightsInputHidden.resize(numInputHiddenWeights);
		m_weightsHiddenOutput.resize(numHiddenOutputWeights);
	}

	void Network::InitializeWeights()
	{
		// Set weights to random values between [-0.5,0.5]
		for (int32_t inputIdx = 0; inputIdx <= m_numInputs; inputIdx++)
		{
			for (int32_t hiddenIdx = 0; hiddenIdx < m_numHidden; hiddenIdx++)
			{
				int32_t const weightIdx = GetInputHiddenWeightIndex(inputIdx, hiddenIdx);
				m_weightsInputHidden[weightIdx] = random(-0.5,0.5);
			}
		}

		// Set weights to random values between [-0.5,0.5]
		for (int32_t hiddenIdx = 0; hiddenIdx <= m_numHidden; hiddenIdx++)
		{
			for (int32_t outputIdx = 0; outputIdx < m_numOutputs; outputIdx++)
			{
				int32_t const weightIdx = GetHiddenOutputWeightIndex(hiddenIdx, outputIdx);
				m_weightsHiddenOutput[weightIdx] = random(-0.5,0.5);
			}
		}
	}

	void Network::LoadWeights(std::vector<double> const& weights)
	{
		int32_t const numInputHiddenWeights = m_numInputs * m_numHidden;
		int32_t const numHiddenOutputWeights = m_numHidden * m_numOutputs;
		assert(weights.size() == numInputHiddenWeights + numHiddenOutputWeights);

		int32_t weightIdx = 0;
		for (int InputHiddenIdx = 0; InputHiddenIdx < numInputHiddenWeights; InputHiddenIdx++)
		{
			m_weightsInputHidden[InputHiddenIdx] = weights[weightIdx];
			weightIdx++;
		}

		for (int HiddenOutputIdx = 0; HiddenOutputIdx < numHiddenOutputWeights; HiddenOutputIdx++)
		{
			m_weightsHiddenOutput[HiddenOutputIdx] = weights[weightIdx];
			weightIdx++;
		}
	}
	double Network::random(double a, double b)
	{
		return (rand() / (double)RAND_MAX) * (b - a) + a;
	}
