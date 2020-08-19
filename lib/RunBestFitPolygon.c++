#include "BestFitPolygon.h"
#include <tclap/CmdLine.h>

using namespace TCLAP;

int main( int argc, char **argv )
{
  try
  {
    CmdLine cmd("Computes best fit polygon.", ' ', "2.0");

    ValueArg<float> resizeArg( "r", "resize", "Resize output value", false, 1.0, "float", cmd);

    ValueArg<float> angleOffsetArg( "a", "angleOffset", "Angel offset value", false, 360.0, "float", cmd);

    ValueArg<float> decimateValueArg( "d", "decimate", "Decimate value", false, 0.0, "float", cmd);

    ValueArg<string> outputArg( "o", "output", "Output name", true, "out", "string", cmd);

    ValueArg<string> boundingNameArg( "b", "bounding", "Bounding shape", true, "in", "string", cmd);

    ValueArg<string> interiorNameArg( "i", "interior", "Interior shape", true, "in", "string", cmd);

    cmd.parse( argc, argv );

    string interiorName               = interiorNameArg.getValue();
    string boundingName               = boundingNameArg.getValue();
    string outputName                 = outputArg.getValue();
    float decimateValue               = decimateValueArg.getValue();
    float angleOffset                 = angleOffsetArg.getValue();
    float resize                      = resizeArg.getValue();

    if( VIPS_INIT( argv[0] ) ) return( -1 );

    RunBestFitPolygon( interiorName, boundingName, outputName, decimateValue, angleOffset, resize );
  }
  catch (ArgException &e)  // catch any exceptions
  {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
  return 0;
}