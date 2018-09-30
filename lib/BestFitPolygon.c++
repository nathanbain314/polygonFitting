#include "BestFitPolygon.h"
#include "PolygonFitting.h"

void imageInPolygon()
{
  Polygon P, P2, R;

  polygonFromAlphaImage( P, "1.png", 2 );

{
double x0=1.5,y0=0.5,r=1.5;  // circle params
double a,da,x,y;

double minX = 1000000, minY = 1000000;

for (a=0.0;a<2.0*M_PI;)         // full circle
    {
    x=x0+(r*cos(a));
    y=y0+(2*r*sin(a));
    a+=(rand()%120)*M_PI/180.0;              // random angle step < 20,60 > degrees

if( R.vertices.size() > 0 && x==R.vertices[R.vertices.size()-1].x && y==R.vertices[R.vertices.size()-1].y) continue;

R.addVertex(x,y);
minX = min(minX,x);
minY = min(minY,y);
    }
    for(int i = 0; i < R.vertices.size(); ++i )
    {
      R.addEdge( i, (i+1)%R.vertices.size() );
    }

    R.offsetBy(Vertex(-minX,-minY));
}


  double scale, rotation;

  Vertex offset;

  findBestFit( P, R, scale, rotation, offset, 10 );

//  cout << scale << " " << rotation << " " << offset.x << " " << offset.y << endl;

  drawImage( P, R, scale, rotation, offset, "out.png", 100 );

//  drawImage( "1.png", R, scale, rotation, offset, "out.png", 100 );
}

void RunBestFitPolygon()
{
  imageInPolygon();
}