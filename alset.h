#ifndef ALSET_H
#define ALSET_H

#pragma once

class ALSet {
  private:
    FeedForward* m_ff;
    string m_filename;

    vector<vector<float> > m_input;
    vector<vector<float> > m_output;

  public:
    ALSet(int num_input, int num_output);
    ~ALSet();

    void addTrainingspair(vector<float> input, vector<float> output);
};

#endif
