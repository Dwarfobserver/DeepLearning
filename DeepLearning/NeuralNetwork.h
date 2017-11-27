//-------------------------------------------------------------------------
// Simple back-propagation neural network example
// 2017 - Bobby Anguelov
// MIT license: https://opensource.org/licenses/MIT
//-------------------------------------------------------------------------
// A simple neural network supporting only a single hidden layer

#pragma once
#include <stdint.h>
#include <vector>

//-------------------------------------------------------------------------

	class Network
	{		
	public:

		Network(int numInputs, int numHidden, int numOutputs);
		Network(int numInputs, int numHidden, int numOutputs, std::vector<double> const& weights);

		std::vector<double> const& GetInputHiddenWeights() const { return m_weightsInputHidden; }
		std::vector<double> const& GetHiddenOutputWeights() const { return m_weightsHiddenOutput; }

	private:

		void InitializeNetwork();
		void InitializeWeights();
		void LoadWeights(std::vector<double> const& weights);

		int32_t GetInputHiddenWeightIndex(int32_t inputIdx, int32_t hiddenIdx) const { return inputIdx * m_numHidden + hiddenIdx; }
		int32_t GetHiddenOutputWeightIndex(int32_t hiddenIdx, int32_t outputIdx) const { return hiddenIdx * m_numOutputs + outputIdx; }

	private:

		int32_t                 m_numInputs;
		int32_t                 m_numHidden;
		int32_t                 m_numOutputs;

		std::vector<double>     m_inputNeurons;
		std::vector<double>     m_hiddenNeurons;
		std::vector<double>     m_outputNeurons;

		std::vector<int32_t>    m_clampedOutputs;

		std::vector<double>     m_weightsInputHidden;
		std::vector<double>     m_weightsHiddenOutput;
	};