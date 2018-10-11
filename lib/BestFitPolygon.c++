#include "BestFitPolygon.h"
#include "PolygonFitting.h"

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
  R.addVertex(259.922,35.1728);
  R.addVertex(259.164,37.8261);
  R.addVertex(255.017,41.9732);
  R.addVertex(251.338,34.6154);
  R.addVertex(259.365,34.6154);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,0);
}

void test3( Polygon &R )
{
  R.addVertex(798.913,933.215);
  R.addVertex(854.984,975.269);
  R.addVertex(855.092,976.877);
  R.addVertex(781.283,939.972);
  R.addVertex(781.625,938.488);
  R.addVertex(784.737,936.759);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
}

void test4( Polygon &R )
{
  R.addVertex( 0,0 );
  R.addVertex( 0,2 );
  R.addVertex( 2,3 );
  R.addVertex( 3,3 );
  R.addVertex( 3,0 );

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,0);
}

void imageInPolygon()
{
  Polygon P, P2, R;

  polygonFromAlphaImage( P, "1.png", 2 );
//P.scaleBy(0.0001);

{
double x0=1.5,y0=0.5,r=1.5;  // circle params
double a,da,x,y;

double minX = 1000000, minY = 1000000;

for (a=0.0;a<2.0*M_PI;)         // full circle
    {
    x=x0+(2*r*cos(a));
    y=y0+(r*sin(a));
    a+=(rand()%2)*M_PI/180.0;              // random angle step < 20,60 > degrees

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
//R.scaleBy(10000);

/*
R.addVertex(728.529,880.483);
R.addVertex(688.282,1000);
R.addVertex(599.775,1000);
R.addVertex(595.388,974.489);
R.addVertex(611.503,928.229);
R.addVertex(623.775,908.272);
R.addVertex(654.65,884.502);
R.addVertex(702.608,859.636);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,6);
  R.addEdge(6,7);
  R.addEdge(7,0);
*/
/*
R.addVertex(215.929,631.139);
R.addVertex(216.265,638.084);
R.addVertex(212.126,637.343);
R.addVertex(155.489,621.866);
R.addVertex(176.972,589.576);
R.addVertex(180.969,590.854);


  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
*/


/*
R.addVertex(271.236,796.407);
R.addVertex(302.222,824.351);
R.addVertex(287,845.183);
R.addVertex(277.346,844.538);
R.addVertex(259.76,822.688);
R.addVertex(259.76,793.213);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
*/


/*
R.addVertex(856.255,179.724);
R.addVertex(841.831,178.153);
R.addVertex(823.719,158.66);
R.addVertex(825.329,143.495);
R.addVertex(843.674,130.082);
R.addVertex(852.255,127.625);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,0);
*/


  /*
R.addVertex(735.781,555.994);
R.addVertex(733.528,589.85);
R.addVertex(731.41,592.367);
R.addVertex(681.714,583.58);
R.addVertex(695.709,510.665);
R.addVertex(706.73,513.066);
R.addVertex(733.88,544.805);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,6);
  R.addEdge(6,0);
*/

/*
  R.addVertex(857.393, 48.1399);
  R.addVertex(841.611, 66.9953);
  R.addVertex(841.427, 67.0592);
  R.addVertex(832.785, 66.5498);
  R.addVertex(818.865, 22.7141);
  R.addVertex(831.518, 0);
  R.addVertex(831.524, 0);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,6);
  R.addEdge(6,0);
*/

/*
  R.addVertex(38.1343,591.775);
  R.addVertex(0,591.775);
  R.addVertex(0,578.235);
  R.addVertex(37.6145,578.235);
*/
/*
  R.addVertex(0,0);
  R.addVertex(40,0);
  R.addVertex(40,40);
  R.addVertex(0,40);

  R.addEdge(0,1);
  R.addEdge(1,2);
  R.addEdge(2,3);
  R.addEdge(3,4);
  R.addEdge(4,5);
  R.addEdge(5,6);
  R.addEdge(6,0);
*/
//test4(R);

  double scale, rotation;

  Vertex offset;

  std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();

  findBestFit( P, R, scale, rotation, offset, 360 );

/*
R.scaleBy(0.0001);
scale *= 0.0001;
offset.x *= 0.0001;
offset.y *= 0.0001;
*/

std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000000000.0 <<std::endl;

  cout << scale << " " << rotation << " " << offset.x << " " << offset.y << endl;

  drawImage( P, R, scale, rotation, offset, "out.png", 100 );

//  drawImage( "1.png", R, scale, rotation, offset, "out.png", 100 );
}

void RunBestFitPolygon()
{
  imageInPolygon();
}