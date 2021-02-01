#include "BestFitPolygon.h"

void test1( Polygon &R )
{
  R.addVertex(66.7695,104.821);
  R.addVertex(71.8299,114.839);
  R.addVertex(71.3801,123.594);
  R.addVertex(70.6173,126.715);
  R.addVertex(31.1714,123.369);
  R.addVertex(37.788,97.1706);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
}

void test2( Polygon &R )
{
  R.addVertex(40,40);
  R.addVertex(80,80);
  R.addVertex(40,60);
  R.addVertex(0,80);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,0);
}

void BestFitPolygon( string interiorName, string boundingName, string outputName, float decimateValue, float angleOffset, float maxAngle, float resize )
{
  Polygon P, P2, R;

/*
  concavePolygonFromAlphaImage( P2, "1.png", 1 );
  
  decimate(P2,.01);

  removeExtrasP( P2, .01 );

  decimate(P2,.02);

  removeExtrasP( P2, .01 );

  P2.center();

  convexPolygonFromVertices( P2.vertices, P );
*/


  polygonFromAlphaImage( P, interiorName, 1 );

  decimate(P,decimateValue);

  P.makeClockwise();
  P.center();



//  test2(R);

  concavePolygonFromAlphaImage( R, boundingName, 1 );

  decimate(R,decimateValue);

//  R.makeClockwise();




  float scale, rotation;

  Vertex offset;



//  std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();

  findBestFit( P, R, scale, rotation, offset, angleOffset, maxAngle );

//  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
//  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 <<std::endl;

  cout << "scale: " << scale << endl;
  cout << "rotation: " << rotation << endl;
  cout << "offset: " << offset << endl;

  drawImage( P, R, scale, rotation, offset, outputName , resize );

//  drawImage( interiorName, R, scale, rotation, offset, outputName, resize );
}

void RunBestFitPolygon( string interiorName, string boundingName, string outputName, float decimateValue, float angleOffset, float maxAngle, float resize )
{
  BestFitPolygon( interiorName, boundingName, outputName, decimateValue, angleOffset, maxAngle, resize );
}
