#ifndef LUCIA_H
#define LUCIA_H

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p != nullptr) { delete (p); (p) = nullptr; } }
#endif

using namespace std;

#include "feedforward.h"

#endif
