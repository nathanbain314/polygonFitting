#include "PolygonFitting.h"

// Initiate with polygon P to fit in polygon R
PolygonFitting::PolygonFitting( Polygon _P, Polygon _R )
{
  P = _P;
  R = _R;
}

PolygonFitting::PolygonFitting( const PolygonFitting& rhs )
{
  P = rhs.P;
  R = rhs.R;

  polygons = rhs.polygons;
  edges = rhs.edges;
  vertices = rhs.vertices;
}

PolygonFitting& PolygonFitting::operator=( const PolygonFitting& rhs )
{
  P = rhs.P;
  R = rhs.R;

  polygons = rhs.polygons;
  edges = rhs.edges;
  vertices = rhs.vertices;

  return *this;
}

// Create vertices and edges by offsetting each edge in P by each edge in R
void PolygonFitting::createOffsetEdges()
{
  for( int j = 0; j < R.vertices.size(); ++j )
  {
    Vertex offset = R.vertices[j];

    for( int i = 0; i < P.vertices.size(); ++i )
    {
      vertices.push_back( P.vertices[ i ].offset( offset ) );
    }
  }
}

double ccw( Vertex v1, Vertex v2, Vertex v3 )
{
  return (v2.x - v1.x)*(v3.y - v1.y) - (v2.y - v1.y)*(v3.x - v1.x);
}

bool minY(Vertex i, Vertex j)
{ 
  return (i.y < j.y) || (i.y == j.y && i.x < j.x);
}

double distance( Vertex v1, Vertex v2 )
{
  return (v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y);
}

bool grahamScanSort ( Vertex v1, Vertex v2, Vertex p )
{
  double angle = ccw( v1, p, v2 );

  if( angle == 0 )
  {
    return distance( v1, p ) < distance( v2, p );
  }

  return angle > 0;
}

vector< Edge > grahamScan( vector< Vertex > vertices )
{
  vector< Vertex > verticesCopy = vertices;

  int n = vertices.size();

  // Swap vertices[0] with the point with the lowest y-coordinate
  vector< Vertex >::iterator vertexIterator;

  vertexIterator = min_element( vertices.begin(), vertices.end(), minY);

  iter_swap(vertices.begin(), vertexIterator);

  // Sort points by polar angle with vertices[0]
  sort( vertices.begin()+1, vertices.end(), bind(grahamScanSort, placeholders::_1, placeholders::_2, vertices[0]));

  stack< int > convexHull;

  for( int i = 0; i < 3; ++i )
  {
    vertexIterator = find(verticesCopy.begin(),verticesCopy.end(),vertices[i]);
    convexHull.push( vertexIterator - verticesCopy.begin() );
  }

  vertexIterator = find(verticesCopy.begin(),verticesCopy.end(),vertices[0]);
  int first = vertexIterator - verticesCopy.begin();

  // Compute hull
  for( int i = 3; i < n; ++i )
  {
    int top = convexHull.top();
    convexHull.pop();

    int second = convexHull.top();

    while( second != first && ccw( verticesCopy[top], verticesCopy[second], vertices[i] ) <= 0 )
    {
      top = second;
      convexHull.pop();
      second = convexHull.top();
    }

    convexHull.push( top );

    vertexIterator = find(verticesCopy.begin(),verticesCopy.end(),vertices[i]);
    convexHull.push( vertexIterator - verticesCopy.begin() );
  }

  convexHull.push( first );

  vector< Edge > convexHullEdges;

  int p1 = convexHull.top();
  convexHull.pop();

  while(!convexHull.empty())
  {
      int p2 = convexHull.top();
      convexHull.pop();

      convexHullEdges.push_back( Edge(p1,p2) );

      p1 = p2;
  }

  return convexHullEdges;
}

Edge reverseEdge( Edge e )
{
  return Edge( e.v2, e.v1 );
}

pair< double, double > intersection( Vertex v1, Vertex v2, Vertex v3, Vertex v4 )
{
  double x[4] = {v1.x,v2.x,v3.x,v4.x};
  double y[4] = {v1.y,v2.y,v3.y,v4.y};

  double denominator = ( x[3] - x[2] ) * ( y[0] - y[1] ) - ( x[0] - x[1] ) * ( y[3] - y[2] );

  double numerator1  = ( x[0] - x[2] ) * ( y[2] - y[3] ) + ( x[3] - x[2] ) * ( y[0] - y[2] );
  double numerator2  = ( x[0] - x[2] ) * ( y[0] - y[1] ) + ( x[1] - x[0] ) * ( y[0] - y[2] );

  // Check if parallel
  if( abs(denominator) < 0.0000001 || ( numerator1 == -numerator2 && numerator1 != 0 ) )
  {
    return pair< double, double >( -1, -1 );
  }

  return pair< double, double >( numerator1/denominator, numerator2/denominator );
}

Vertex intersectionPoint( double t, Vertex v1, Vertex v2 )
{
  double x = v1.x + t * ( v2.x - v1.x );
  double y = v1.y + t * ( v2.y - v1.y );

  return Vertex( x, y );
}

double distanceToLine( Vertex p, Vertex v1, Vertex v2 )
{
  double x[3] = {p.x,v1.x,v2.x};
  double y[3] = {p.y,v1.y,v2.y};

  double xDiff = x[2] - x[1];
  double yDiff = y[2] - y[1];

  double denominator = sqrt( xDiff * xDiff + yDiff * yDiff );

  if( denominator == 0 ) return -1;

  double numerator = abs( yDiff * x[0] - xDiff * y[0] + x[2] * y[1] - y[2] * x[1] );

  return numerator / denominator;
}

bool isOnLineSegment( Vertex v1, Vertex v2, Vertex v3 )
{
  double area = ( v1.x * ( v2.y - v3.y ) + v2.x * ( v3.y - v1.y ) + v3.x * ( v1.y - v2.y ) );

  bool inBetween = v1.x >= min(v2.x,v3.x) - 0.0000001 && v1.x <= max(v2.x,v3.x) + 0.0000001 && v1.y >= min(v2.y,v3.y) - 0.0000001 && v1.y <= max(v2.y,v3.y) + 0.0000001;

  if( inBetween && abs(area) < 0.0000001 )
  {
    return true;
  }

  return false;
}

void PolygonFitting::computeContributingEdges()
{
  P.scaleBy(-1);

  vector< int > verticesUsed;

  for( int i = 0; i < R.edges.size(); ++i )
  {
    Vertex v1 = R.vertices[ R.edges[i].v1 ];
    Vertex v2 = R.vertices[ R.edges[i].v2 ];

    double smallestAngle = 1000000000;
    int bestVertex = 0;

    for( int j = 0; j < P.vertices.size(); ++j )
    {
      Vertex p = P.vertices[j].offset( v1 );

      double angle = ccw( v1, v2, p );
 
      if( angle < smallestAngle )
      {
        smallestAngle = angle;
        bestVertex = j;
      }
    }

    v1 = v1.offset( P.vertices[bestVertex] );
    v2 = v2.offset( P.vertices[bestVertex] );

    if( i > 0 )
    {
      int s = P.vertices.size();

      int s2 = contributingEdges.size();

      int prevVertex = verticesUsed[s2-1];

      Vertex v3 = vertices[contributingEdges[s2-1].v1];
      Vertex v4 = vertices[contributingEdges[s2-1].v2];

      pair< double, double > t = intersection( v3, v4, v1, v2 );
    
      if( t.first > 1+0.0000001 || t.second < -0.0000001 )
      {
        int direction = 1;

        Vertex p1 = R.vertices[ R.edges[i].v1 ].offset( P.vertices[( prevVertex - 1 + s ) % s ] );
        Vertex p2 = R.vertices[ R.edges[i].v1 ].offset( P.vertices[( prevVertex + 1 + s ) % s ] );

        if( isOnLineSegment( p1, v3, v4 ) )
        {
          direction = 1;
        }
        else if( isOnLineSegment( p2, v3, v4 ) )
        {
          direction = -1;
        }
        else if( ccw( v4, R.vertices[ R.edges[i].v1 ].offset( P.vertices[( prevVertex - 1 + s ) % s ] ), R.vertices[ R.edges[i].v1 ].offset( P.vertices[( prevVertex + 1 + s ) % s] ) ) > 0 ) //ccw( v3, v4, R.vertices[ R.edges[i].v1 ].offset( P.vertices[( prevVertex - 1 + s ) % s ] ) ) < ccw( v3, v4, R.vertices[ R.edges[i].v1 ].offset( P.vertices[( prevVertex + 1 + s ) % s] ) ) )
        {
          direction = -1;
        }

        for( int k = prevVertex; k != bestVertex; k = ( k + direction + s ) % s )
        {
          vertices.push_back( R.vertices[ R.edges[i].v1 ].offset( P.vertices[k] ) );
          vertices.push_back( R.vertices[ R.edges[i].v1 ].offset( P.vertices[( k + direction + s ) % s] ) );

          contributingEdges.push_back( Edge( vertices.size() - 2, vertices.size() - 1 ) );

          edgeOffsets.push_back( P.vertices[( k + direction + s ) % s] );
        }
      }
    }

    vertices.push_back( v1 );
    vertices.push_back( v2 );

    contributingEdges.push_back( Edge( vertices.size() - 2, vertices.size() - 1 ) );

    verticesUsed.push_back( bestVertex );

    edgeOffsets.push_back( P.vertices[bestVertex] );
  }
}

bool PolygonFitting::isValidFit()
{
  for( int i = 0; i < R.edges.size(); ++i )
  {
    Vertex v1 = R.vertices[R.edges[i].v1];
    Vertex v2 = R.vertices[R.edges[i].v2];

    for( int j = 0; j < P.edges.size(); ++j )
    {
      pair< double, double > t = intersection( v1, v2, P.vertices[P.edges[j].v1], P.vertices[P.edges[j].v2] );

      if( t.first < -0.0000001 || t.second < -0.0000001 ) continue;

      // Edges intersect
      if( t.first > 0.0000001 && t.first < 1-0.0000001 && t.second > 0.0000001 && t.second < 1-0.0000001 )
      {
        return false;
      }


      if( ( t.first < 0.0000001 && t.second < 1 - 0.0000001 ) || ( t.first < 1 - 0.0000001 && t.second < 0.0000001 ) )//&& t.second < 1 - 0.0000001 )
      {
        if( ccw( v1, P.vertices[P.edges[j].v2], v2 ) < -0.0000001 )
        {
          return false;
        }
      }
    }
  }

  Vertex p = P.vertices[0];

  int n = 0;

  for( int i = 0; i < R.edges.size(); ++i )
  {
    Vertex v1 = R.vertices[R.edges[i].v1];
    Vertex v2 = R.vertices[R.edges[i].v2];

    if( isOnLineSegment( p, v1, v2 ) ) return true;

    if( v1.y <= p.y )
    {
      if( v2.y > p.y && ccw( v1, p, v2 ) < 0 )
      {
        ++n;
      }
    }
    else
    {
      if( v2.y <= p.y && ccw( v1, p, v2 ) > 0 )
      {
        --n;
      }
    }
  }

  if( n == 0 ) return false;

  return true;
}

double intersectionEdges( Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6, Vertex o1, Vertex o2, Vertex o3 )
{
  double x[6] = {v1.x,v2.x,v3.x,v4.x,v5.x,v6.x};
  double y[6] = {v1.y,v2.y,v3.y,v4.y,v5.y,v6.y};

  double o[4];
  double a[3];
  double b[3];
  double c[3];
  double d[3];

  a[0] = x[0] - x[2];
  a[1] = x[3] - x[2];
  a[2] = x[0] - x[1];

  b[0] = y[2] - y[3];
  b[1] = y[0] - y[2];
  b[2] = y[0] - y[1];

  c[0] = x[0] - x[4];
  c[1] = x[5] - x[4];
  c[2] = x[0] - x[1];

  d[0] = y[4] - y[5];
  d[1] = y[0] - y[4];
  d[2] = y[0] - y[1];

  o[0] = o1.x - o2.x;
  o[1] = o1.y - o2.y;
  o[2] = o1.x - o3.x;
  o[3] = o1.y - o3.y;

  double denominator1 = ( a[1] * b[2] + a[2] * b[0] );
  double denominator2 = ( c[1] * d[2] + c[2] * d[0] );

  if( abs(denominator1) < 0.0000001 || abs(denominator2) < 0.0000001 ) return -1;

  double denominator3 = ( a[1] * o[1] + b[0] * o[0] ) / denominator1 - ( c[1] * o[3] + d[0] * o[2] ) / denominator2;

  if( abs(denominator3) < 0.0000001 ) return -1;

  double result = ( c[0] * d[0] + c[1] * d[1] ) / denominator2 - ( a[0] * b[0] + a[1] * b[1] ) / denominator1;

  return result / denominator3;
}

struct Cmp
{
    bool operator ()(const pair< int, double> &a, const pair< int, double> &b)
    {
      if( a.first == b.first ) return false;
        return a.second < b.second;
    }
};

bool PolygonFitting::findBestScale( double &maxScale, Vertex &bestFitOrigin )
{
  bool isNewBestScale = false;

//  vector< Vertex > edgeOffsets;
  vector< int > validEdges;
  vector< tuple< int, int, int > > connectingEdges;

  for( int i = 0; i < contributingEdges.size(); ++i )
  {
    connectingEdges.push_back( tuple< int, int, int >(i,(i+1)%contributingEdges.size(),(i+2)%contributingEdges.size()) );

    validEdges.push_back( i );
  }

  P.scaleBy( -1 );
  Polygon P2 = P;

  bool notDoneYet = true;

  set< pair< int, double >, Cmp > eraseEdges;

  while( notDoneYet && validEdges.size() > 2 )
  {
    notDoneYet = false;

    for( int l = 0; l < connectingEdges.size(); ++l, P = P2 )
    {
      int i = get<0>(connectingEdges[l]);
      int j = get<1>(connectingEdges[l]);
      int k = get<2>(connectingEdges[l]);

      int found = 0;

      for( int m = 0; m < validEdges.size(); ++m )
      {
        if( validEdges[m] == i || validEdges[m] == j || validEdges[m] == k )
        {
          ++found;
        }
      }

      if( found < 3 ) continue;

      Vertex v1 = vertices[ contributingEdges[i].v1 ];
      Vertex v2 = vertices[ contributingEdges[i].v2 ];
      Vertex v3 = vertices[ contributingEdges[j].v1 ];
      Vertex v4 = vertices[ contributingEdges[j].v2 ];
      Vertex v5 = vertices[ contributingEdges[k].v1 ];
      Vertex v6 = vertices[ contributingEdges[k].v2 ];

      double s = intersectionEdges( v3, v4, v1, v2, v5, v6, edgeOffsets[j], edgeOffsets[i], edgeOffsets[k] );

      if( s > -1.0000001 && s < -1 + 0.0000001 )
      {
        connectingEdges.erase( connectingEdges.begin() + l );

        continue;
      }

      v1 = v1.offset( s * edgeOffsets[i].x, s * edgeOffsets[i].y );
      v2 = v2.offset( s * edgeOffsets[i].x, s * edgeOffsets[i].y );
      v3 = v3.offset( s * edgeOffsets[j].x, s * edgeOffsets[j].y );
      v4 = v4.offset( s * edgeOffsets[j].x, s * edgeOffsets[j].y );

      pair< double, double > t = intersection( v1, v2, v3, v4 );

      if( t.first > 10000 || t.first < -10000 )
      {
        connectingEdges.erase( connectingEdges.begin() + l );

        continue;
      }

      Vertex p = intersectionPoint( t.first, v1, v2 );

      s += 1.0;

      P.scaleBy( s );
      P.offsetBy( p );

      if( !isValidFit() ) continue;

      if( s > maxScale )
      {
        maxScale = s;
        bestFitOrigin = p;
        isNewBestScale = true;
      }      

      eraseEdges.insert( pair< int, double >( j, s ) );

      notDoneYet = true;

      connectingEdges.erase( connectingEdges.begin() + l );
    }

    if( !eraseEdges.empty() )
    {
      while( !eraseEdges.empty() )
      {
        int ve = (*(eraseEdges.begin())).first;

        eraseEdges.erase(eraseEdges.begin());

        vector< int >::iterator intIterator;

        // Find position of v1 if it already exists
        intIterator = find(validEdges.begin(),validEdges.end(),ve);

        int i = intIterator - validEdges.begin();

        int s = contributingEdges.size();

        connectingEdges.push_back( tuple< int, int, int >(validEdges[(i-2+s)%s],validEdges[(i-1+s)%s],validEdges[(i+1)%s]) );
        connectingEdges.push_back( tuple< int, int, int >(validEdges[(i-1+s)%s],validEdges[(i+1)%s],validEdges[(i+2)%s]) );

        validEdges.erase( intIterator );

        notDoneYet = true;
      }
    }
  }

  return isNewBestScale;
}

void findBestFit( Polygon P2, Polygon R, double &scale, double &rotation, Vertex &offset, double rotationOffset )
{
  Polygon P;
  convexPolygonFromVertices( P2.vertices, P );

  R.makeClockwise();
  P.makeClockwise();

  scale = 0;

  Vertex origin = Vertex( -1000000, -1000000 );

  for( int i = 0; i < R.vertices.size(); ++i )
  {
    Vertex v1 = R.vertices[i];

    origin.x = max( -v1.x, origin.x );
    origin.y = max( -v1.y, origin.y );
  }

  R.offsetBy( origin );

  for( double r = 0; r < 360; r += rotationOffset )
  {
    Polygon PCopy = P;

    PCopy.rotateBy(r);

    PolygonFitting pf( PCopy, R );

    pf.computeContributingEdges();

    if( pf.findBestScale( scale, offset ) )
    {
      rotation = r;
    }
  }

  P.scaleBy(scale);

  offset = offset.offset( -origin.x, -origin.y );//.offset(P.computeOffset(rotation));
}

void drawImage( Polygon P, Polygon R, double scale, double rotation, Vertex offset, string outputName, double scaleUp )
{
  double width = 0;
  double height = 0;

  Vertex origin = Vertex( -1000000, -1000000 );

  for( int i = 0; i < R.vertices.size(); ++i )
  {
    Vertex v1 = R.vertices[i];

    width = max( v1.x, width );
    height = max( v1.y, height );

    origin.x = max( -v1.x, origin.x );
    origin.y = max( -v1.y, origin.y );
  }

  width += origin.x;
  height += origin.y;

  VImage image = VImage::black(width*scaleUp+4,height*scaleUp+4).invert();

  R.offsetBy( origin );
  R.scaleBy( scaleUp );
  R.offsetBy( Vertex( 2, 2) );

  vector< double > ink = {0};

  for( int i = 0; i < R.edges.size(); ++i )
  {
    Vertex v1 = R.vertices[R.edges[i].v1];
    Vertex v2 = R.vertices[R.edges[i].v2];

    image.draw_line(ink,v1.x,v1.y,v2.x,v2.y);
  }

  P.rotateBy( rotation );
  P.scaleBy( scale );
  P.offsetBy( offset );

  P.offsetBy( origin );
  P.scaleBy( scaleUp );

  P.offsetBy( Vertex( 2, 2) );

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    Vertex v1 = P.vertices[i];

    image.draw_rect(ink,v1.x,v1.y,4,4);
  }

  for( int i = 0; i < P.edges.size(); ++i )
  {
    Vertex v1 = P.vertices[P.edges[i].v1];
    Vertex v2 = P.vertices[P.edges[i].v2];

    image.draw_line(ink,v1.x,v1.y,v2.x,v2.y);
  }

  image.vipssave("out.png");
}


void drawImage( string imageName, Polygon R, double scale, double rotation, Vertex offset, string outputName, double scaleUp )
{
  double width = 0;
  double height = 0;

  Vertex origin = Vertex( -1000000, -1000000 );

  for( int i = 0; i < R.vertices.size(); ++i )
  {
    Vertex v1 = R.vertices[i];

    width = max( v1.x, width );
    height = max( v1.y, height );

    origin.x = max( -v1.x, origin.x );
    origin.y = max( -v1.y, origin.y );
  }

  VImage image = VImage::black(width*scaleUp+4,height*scaleUp+4).invert();
  image = image.bandjoin(image).bandjoin(image);

  R.offsetBy( origin );
  R.scaleBy( scaleUp );
  R.offsetBy( Vertex( 2, 2) );

  vector< double > ink = {0,0,0};

  for( int i = 0; i < R.edges.size(); ++i )
  {
    Vertex v1 = R.vertices[R.edges[i].v1];
    Vertex v2 = R.vertices[R.edges[i].v2];

    image.draw_line(ink,v1.x,v1.y,v2.x,v2.y);
  }

  VImage centerImage = VImage::vipsload((char *)imageName.c_str()).similarity( VImage::option()->set( "scale", scale*scaleUp )->set( "angle", rotation ));

  int left, top, centerImageWidth, centerImageHeight;

  left = centerImage.find_trim( &top, &centerImageWidth, &centerImageHeight );

  centerImage = centerImage.extract_area( left, top, centerImageWidth, centerImageHeight );

  int xOffset = (offset.x + origin.x)*scaleUp+2;
  int yOffset = (offset.y + origin.y)*scaleUp+2;

  centerImage = centerImage.embed(xOffset,yOffset,centerImage.width()+xOffset,centerImage.height()+yOffset);//->set( "idx", -(offset.x + origin.x) )->set( "idy", -(offset.y + origin.y)*scaleUp ));

  VImage mask = centerImage.extract_band(3);

  centerImage = centerImage.flatten();

  image = mask.ifthenelse( centerImage, image, VImage::option()->set( "blend", true ) );

  image.vipssave("out.png");
}

void polygonFromAlphaImage( Polygon &P, string imageName, double resize )
{
  VImage image = VImage::vipsload((char *)imageName.c_str()).autorot().colourspace(VIPS_INTERPRETATION_sRGB).resize(1.0/resize);

  int width = image.width();
  int height = image.height();

  if( image.bands() == 4 )
  {
    image = image.extract_band(3);

    unsigned char *data = ( unsigned char * )image.data();

    vector< Vertex > vertices;

    for( int i = 0, p = 0; i < height; ++i )
    {
      for( int j = 0; j < width; ++j, ++p )
      {
        if( data[p] != 0 )
        {
          vertices.push_back( Vertex( j*resize, i*resize ) );
        }
      }
    }

    vector< Edge > edges = grahamScan( vertices );

    Vertex origin = Vertex( -1000000, -1000000 );

    for( int i = 0; i < edges.size(); ++i )
    {
      P.vertices.push_back( vertices[edges[i].v1] );
      P.edges.push_back( Edge( i, (i+1)%edges.size() ) );

      origin.x = max( -vertices[edges[i].v1].x, origin.x );
      origin.y = max( -vertices[edges[i].v1].y, origin.y );
    }

    P.offsetBy(origin);
  }
}

void convexPolygonFromVertices( vector< Vertex > &vertices, Polygon &P )
{
  vector< Edge > edges = grahamScan( vertices );

  Vertex origin = Vertex( -1000000, -1000000 );

  for( int i = 0; i < edges.size(); ++i )
  {
    P.vertices.push_back( vertices[edges[i].v1] );
    P.edges.push_back( Edge( i, (i+1)%edges.size() ) );

    origin.x = max( -vertices[edges[i].v1].x, origin.x );
    origin.y = max( -vertices[edges[i].v1].y, origin.y );
  }

  P.offsetBy(origin);
}