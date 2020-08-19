#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <dirent.h>
#include <unistd.h>
#include <future>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <random>
#include <set>
#include <tuple>
#include <time.h>

#include <vips/vips8>

#include "PolygonFitting/PolygonFitting.h"

using namespace vips;
using namespace std;

void RunBestFitPolygon( string interiorName, string boundingName, string outputName, float decimateValue, float angleOffset, float resize );
