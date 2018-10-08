#include "Polygon.h"
#include "progress_bar.hpp"

vector< Edge > grahamScan( vector< Vertex > vertices );

class PolygonFitting
{
public:
  Polygon P, R, bestFit;

  vector< Polygon > polygons;
  vector< Edge > edges;
  vector< Vertex > vertices;
  vector< Edge > contributingEdges, contributingEdgesCopy;  
  vector< int > contributingVertices;  

  PolygonFitting(){}

  PolygonFitting( Polygon _P, Polygon _R );

  PolygonFitting( const PolygonFitting& rhs );

  PolygonFitting& operator=( const PolygonFitting& rhs );

  void createOffsetEdges( Polygon &P, Polygon &R );

  void computeContributingEdges();

  void computeIntersections( bool removeNonCycles );

  void checkIfValidFit();

  bool findBestScale( double &maxScale, Vertex &bestFitOrigin );

  void findBestScale2( double &maxScale, Vertex &bestFitOrigin );

  void findBestScale3( double &maxScale, Vertex &bestFitOrigin );

  bool isValidFit( Vertex &c );

  void drawImageFit( double maxScale, Vertex bestFitOrigin );
};

void findBestFit( Polygon P, Polygon R, double &scale, double &rotation, Vertex &offset, double rotationOffset = 1.0 );

void drawImage( Polygon P, Polygon R, double scale, double rotation, Vertex offset, string outputName, double scaleUp );

void drawImage( string imageName, Polygon R, double scale, double rotation, Vertex offset, string outputName, double scaleUp );

void polygonFromAlphaImage( Polygon &P, string imageName, double resize = 1.0 );