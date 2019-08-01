#include "lucia.h"

ALSet::ALSet(int num_input, int num_output) { 
  m_ff = nullptr;
  m_ff = new FeedForward(num_input, num_output, "10000");
}

ALSet::~ALSet() { 
  SAFE_DELETE(m_ff);
}

void ALSet::addTrainingspair(vector<float> input, vector<float> output) {
  m_input.push_back(input);
  m_output.push_back(output);
}
