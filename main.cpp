#include "lucia.h"


int main(int argc, char** argv) {
  feedForward n1(2, 1, "100");

  vector<vector<float> > input;
  input.push_back({0.0f, 0.0f});
  input.push_back({0.0f, 1.0f});
  input.push_back({1.0f, 0.0f});
  input.push_back({1.0f, 1.0f});

  vector<vector<float> > output;
  output.push_back({0.0f});
  output.push_back({1.0f});
  output.push_back({1.0f});
  output.push_back({0.0f});
  
  n1.runTraining(input, output, 100000);

  n1.printv(n1.makeClean(n1.calcOutput({0.0f, 1.0f})));

  return 0;
}
