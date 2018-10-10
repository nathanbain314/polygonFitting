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

  void createOffsetEdges();

  void computeContributingEdges();

  void computeIntersections( bool removeNonCycles );

  void checkIfValidFit();

  bool findBestScale( double &maxScale, Vertex &bestFitOrigin );

  bool isValidFit();

  void drawImageFit( double maxScale, Vertex bestFitOrigin );
};

void findBestFit( Polygon P, Polygon R, double &scale, double &rotation, Vertex &offset, double rotationOffset = 1.0 );

void drawImage( Polygon P, Polygon R, double scale, double rotation, Vertex offset, string outputName, double scaleUp );

void drawImage( string imageName, Polygon R, double scale, double rotation, Vertex offset, string outputName, double scaleUp );

void polygonFromAlphaImage( Polygon &P, string imageName, double resize = 1.0 );


double ccw( Vertex v1, Vertex v2, Vertex v3 );

bool minY(Vertex i, Vertex j);

double distance( Vertex v1, Vertex v2 );

bool grahamScanSort ( Vertex v1, Vertex v2, Vertex p );

vector< Edge > grahamScan( vector< Vertex > vertices );

Edge reverseEdge( Edge e );

pair< double, double > intersection( Vertex v1, Vertex v2, Vertex v3, Vertex v4 );

Vertex intersectionPoint( double t, Vertex v1, Vertex v2 );

bool isOnLineSegment( Vertex v1, Vertex v2, Vertex v3 );

double intersectionEdges( Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6, Vertex o1, Vertex o2, Vertex o3 );