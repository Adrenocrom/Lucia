#ifndef FEEDFORWARD_H
#define FEEDFORWARD_H

#pragma once

#include "lucia.h"

#define OUTUNIT 		0
#define HIDDENUNIT 	1

class FeedForward {
  private:
  	int m_iNumHiddenLayer;
  	int m_iNumLayer;
  	int m_iNumNeuronsPerLayer;

	  float m_fLearningRate;
	  float m_fAlpha;

	  vector<vector<vector<float> > > m_pppMatrix;
	  vector<vector<vector<float> > > m_pppDelta;
	  vector<vector<float> > m_ppfDelt;
  	vector<vector<float> > m_ppfHidden;

  	std::vector<float>  m_vInput;
    std::vector<float>  m_vOutput;

    std::vector<int>	  m_vPerLayer;

    vector<vector<float> > m_vvIn;
    vector<vector<float> > m_vvOut;

public:
	FeedForward(int iNumInputNeurons,
              int iNumOutPutNeurons,
              const string str_hiddenLayer);

	~FeedForward();

	void setInputAndOutput(vector<vector<float> > vvIn, vector<vector<float> > vvOut);

	std::vector<float> calcOutput(std::vector<float> input);
	
  void learnNetwork(vector<float>& vInput,
							      vector<float>& vOutput,
							      float fLearningRate = 0.1,
							      float fAlpha = 0.0f);

  void runTraining(vector<vector<float> >& pIn, 
                   vector<vector<float> >& pOut, 
                   int iNumSteps = 100000, 
                   float fLearningRate = 0.1, 
                   float fAlpha = 0.0f, 
                   int iNumExamples = -1);

  bool isCorrect(vector<float> vIn, vector<float> vOut);

	void loadWeights(const std::string filename);
	void saveWeights(const std::string filename);
	void createHiddenFromString(const string str_hiddenLayer);

	void setAllWeights(float fWeight);
	void setWeight(int l, int i, int j, float w);
	float getWeight(int l, int i, int j) {return m_pppMatrix[l][i][j];}
	int getNumLayer() {return m_iNumLayer;}
	vector<int> getLayer() {return m_vPerLayer;}

  vector<float> makeClean(vector<float> vIn);
  void printv(vector<float> vIn);
};

#endif
