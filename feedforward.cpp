#include "lucia.h"

feedForward::feedForward(int iNumInputNeurons, int iNumOutputNeurons, const string str_hiddenLayer) {
	m_vPerLayer.push_back(iNumInputNeurons);
	createHiddenFromString(str_hiddenLayer);
	m_vPerLayer.push_back(iNumOutputNeurons);

	m_iNumLayer = ((int)m_vPerLayer.size())-1;
	m_iNumHiddenLayer = m_iNumLayer-1;
	m_fLearningRate = 0.07f;
	m_fAlpha = 0.0f;

	for(int l = 0; l < m_iNumLayer; ++l) {
    vector<float> vHiddenT;
    vector<float> vDeltT;

    for(int i = 0; i < m_vPerLayer[l+1]+1; ++i) {
      vHiddenT.push_back(-1.0f);
      vDeltT.push_back(-1.0f);
		}

		m_ppfDelt.push_back(vDeltT);
		m_ppfHidden.push_back(vHiddenT);
	}

	for(int l = 0; l < m_iNumLayer; ++l) {
		vector<vector<float> > vMatrxT2;
		vector<vector<float> > vDeltaT2;

		for(int i = 0; i < m_vPerLayer[l+1]; ++i) {
			vector<float> vMatrxT;
			vector<float> vDeltaT;
			for(int j = 0; j < m_vPerLayer[l]+1; ++j) {
				vMatrxT.push_back((rand() %40 + 1) / 10000000.0f);
				vDeltaT.push_back(0.2f);
			}
			vMatrxT2.push_back(vMatrxT);
			vDeltaT2.push_back(vDeltaT);
		}

		m_pppMatrix.push_back(vMatrxT2);
		m_pppDelta.push_back(vDeltaT2);
	}
}

feedForward::~feedForward() { }

void feedForward::setAllWeights(float fWeight) {
	for(int l = 0; l < m_iNumLayer; ++l) {
		for(int i = 0; i < m_vPerLayer[l+1]; ++i) {
			for(int j = 0; j < m_vPerLayer[l]+1; ++j) {
				m_pppMatrix[l][i][j] = fWeight;
			}
		}
	}
}

void feedForward::setWeight(int l, int i, int j, float w) {
	m_pppMatrix[l][i][j] = w;
}

std::vector<float> feedForward::calcOutput(std::vector<float> vInput) {
	m_vInput = vInput;
	m_vInput.push_back(-1.0f);
	m_vOutput.clear();
	
	for(int l = 0; l < m_iNumLayer; ++l) {
		for(int i = 0; i < m_vPerLayer[l+1]; ++i) {
			// Netzinput der nächsten Schicht berrechnen
			float fNetInput = 0;

			for(int j = 0; j < m_vPerLayer[l]+1; ++j) {
				if(l == 0) 
				 fNetInput += m_pppMatrix[l][i][j] * m_vInput[j];
				else		
				 fNetInput += m_pppMatrix[l][i][j] * m_ppfHidden[l-1][j];
			}

			float fNetOutput = 0;

			fNetOutput = 1/(1+expf(-fNetInput));

			m_ppfHidden[l][i] = fNetOutput;
		}
	}

	// Output vector lesen
	for(int i = 0; i < m_vPerLayer[m_iNumLayer]; ++i) {
		m_vOutput.push_back(m_ppfHidden[m_iNumLayer-1][i]);
	}

	return m_vOutput;
}

void feedForward::learnNetwork(vector<float> vInput, vector<float> vOutput, float fLearningRate, float fAlpha) {
	m_fLearningRate = fLearningRate;
	m_fAlpha = fAlpha;

	calcOutput(vInput);

	for(int i = 0; i < m_vPerLayer[m_iNumLayer]; ++i)
		m_ppfDelt[m_iNumLayer-1][i] = m_ppfHidden[m_iNumLayer-1][i] * (1 - m_ppfHidden[m_iNumLayer-1][i]) * (vOutput[i] - m_ppfHidden[m_iNumLayer-1][i]);

	for(int l = m_iNumLayer-1; l >= 0; --l) {
		for(int j = 0; j < m_vPerLayer[l]+1; ++j) {
			float fSum = 0.0f;

			for(int i = 0; i < m_vPerLayer[l+1]; ++i)
				fSum += m_pppMatrix[l][i][j] * m_ppfDelt[l][i];
			
			if(l > 0) 
        m_ppfDelt[l-1][j] = m_ppfHidden[l-1][j] * (1 - m_ppfHidden[l-1][j]) * fSum;
		}
	}

	for(int l = m_iNumLayer-1; l >= 0; --l) {
		for(int j = 0; j < m_vPerLayer[l]+1; ++j) {
			for(int i = 0; i < m_vPerLayer[l+1]; ++i) {
			   if(l > 0)
					m_pppDelta[l][i][j] = m_fLearningRate*m_ppfDelt[l][i]*m_ppfHidden[l-1][j] + m_fAlpha * m_pppDelta[l][i][j];			
				else
					m_pppDelta[l][i][j] = m_fLearningRate*m_ppfDelt[l][i]*m_vInput[j] + m_fAlpha * m_pppDelta[l][i][j];

				m_pppMatrix[l][i][j] += m_pppDelta[l][i][j];
			}
		}
	}
}

void feedForward::loadWeights(const string filename) {
	FILE* pFile = nullptr;

	if((pFile = fopen(filename.c_str(), "r")) == nullptr) {
		fclose(pFile);
		pFile = nullptr;
		std::cerr<<"ERROR: Could not load "<<filename<<"."<<std::endl;
		return;
	}

	int iTemp1, iTemp2;
	char cBuffer[200];
	float fTemp;

	fscanf(pFile, "%d", &iTemp1);
	fscanf(pFile, "%d", &iTemp2);
	fscanf(pFile, "%s", cBuffer);

	for(int l = 0; l < m_iNumLayer; ++l) {
		for(int i = 0; i < m_vPerLayer[l+1]; ++i) {
			for(int j = 0; j < m_vPerLayer[l]+1; ++j) {
				fscanf(pFile, "%f", &fTemp);
				m_pppMatrix[l][i][j] = fTemp;
			}
		}
	}

	if(pFile) {
		fclose(pFile);
		pFile = nullptr;
	}
}

void feedForward::saveWeights(const string filename) {
	FILE* pFile = nullptr;

	if((pFile = fopen(filename.c_str(), "w")) == nullptr) {
		fclose(pFile);
		pFile = nullptr;
		std::cerr<<"ERROR: Could not load "<<filename<<"."<<std::endl;
		return;
	}

	fprintf(pFile, "%d %d ", m_vPerLayer[0], m_vPerLayer[m_iNumLayer]);

	fprintf(pFile, "%d", m_vPerLayer[1]);
	for(int l = 2; l < m_iNumLayer; ++l) {
		fprintf(pFile, ",%d", m_vPerLayer[m_iNumLayer-1]);
	}

	for(int l = 0; l < m_iNumLayer; ++l) {
		for(int i = 0; i < m_vPerLayer[l+1]; ++i) {
			fprintf(pFile, "\n");
			
			for(int j = 0; j < m_vPerLayer[l]+1; ++j) {

			
				fprintf(pFile, "%f ", m_pppMatrix[l][i][j]);
			}
		}
	}

	if(pFile) {
		fclose(pFile);
		pFile = nullptr;
	}
}

void feedForward::createHiddenFromString(const string str_hiddenLayer) {
	stringstream hidden(str_hiddenLayer);
	string str_hidden;
	while(getline(hidden, str_hidden, ',')) {
		int iNumHidden = 0;
		istringstream(str_hidden) >> iNumHidden;
	
		m_vPerLayer.push_back(iNumHidden);
	}
}


void feedForward::runTraining(vector<vector<float> > pIn, vector<vector<float> > pOut, int iNumSteps, float fLearningRate, float fAlpha, int iNumExamples) {
  bool bLearned = true;
  int  iStep = 0;

  if(iNumExamples < 0)
    iNumExamples = pIn.size();
                 
  printf("train core with %d examples\n", iNumExamples);

  clock_t startTime;
  clock_t endTime;
  float fTime = 0.0f;
  
  startTime = clock();

  do {
    bLearned = true;
    
    for(int a = 0; a < iNumExamples; ++a) {
                          
      if(!isCorrect(pOut[a], makeClean(calcOutput(pIn[a])))) {
         learnNetwork(pIn[a], pOut[a], fLearningRate, fAlpha);
         bLearned = false;
      }
    }
    
    iStep++;
    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b%d Step", iStep);
  } while((!bLearned)&&(iStep < iNumSteps));
  
  endTime = clock() - startTime;
  fTime = (float) endTime/((float)CLOCKS_PER_SEC);
  printf("\ntrained and %.3f s needed\n", fTime);
  saveWeights("net.txt");
}

vector<float> feedForward::makeClean(vector<float> vIn) {
  for(int i = 0; i < vIn.size(); ++i) {
    if(vIn[i] < 0.5f) 
      vIn[i] = 0.0f; 
    else 
      vIn[i] = 1.0f;
  }

  return vIn;
}

bool feedForward::isCorrect(vector<float> vIn, vector<float> vOut) {
  float fSum = 0.0f;

  for(int a = 0; a < vIn.size(); ++a)
      fSum += pow((vIn[a] - vOut[a]), 2);

  if(fSum == 0) 
    return true;

  return false;
}

void feedForward::printv(vector<float> vIn) {
  cout<<"(";
  
  for(int i = 0; i < vIn.size(); ++i)
    cout<<vIn[i];
  cout<<")"<<endl;
}

