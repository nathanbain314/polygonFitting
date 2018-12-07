#include "Polygon.h"

Polygon::Polygon( vector< Vertex > &_vertices, vector< Edge > &_edges )
{
  edges = _edges;
  vertices = _vertices;
}

Polygon::Polygon( const Polygon& rhs )
{
  edges = rhs.edges;
  vertices = rhs.vertices;
}

Polygon& Polygon::operator=( const Polygon& rhs )
{
  edges = rhs.edges;
  vertices = rhs.vertices;

  return *this;
}

void Polygon::addVertex( double x, double y )
{
  vertices.push_back( Vertex(x,y) );
}

void Polygon::addVertex( Vertex v )
{
  vertices.push_back( v );
}

void Polygon::addEdge( int v1, int v2 )
{
  edges.push_back( Edge( v1, v2 ) );
}

void Polygon::addEdge( Edge e )
{
  edges.push_back( e );
}

void Polygon::switchDirection()
{
  for( int i = 0; i < vertices.size()/2; ++i )
  {
    Vertex t = vertices[i];
    vertices[i] = vertices[vertices.size() - 1 - i];
    vertices[vertices.size() - 1 - i] = t;
  }
}

void Polygon::makeClockwise()
{
  double n = 0;
  for( int i = 0; i < edges.size(); ++i )
  {
    n += ( vertices[edges[i].v2].x - vertices[edges[i].v1].x ) * ( vertices[edges[i].v2].y + vertices[edges[i].v1].y );
  }

  if( n < 0 )
  {
    switchDirection();
  }
}

void Polygon::scaleBy( double scale )
{
  for( int i = 0; i < vertices.size(); ++i )
  {
    vertices[i].x *= scale;
    vertices[i].y *= scale;
  }
}

void Polygon::offsetBy( Vertex offset )
{
  for( int i = 0; i < vertices.size(); ++i )
  {
    vertices[i] = vertices[i].offset( offset );
  }
}

void Polygon::rotateBy( double r, bool offset )
{
  double pi = 3.14159265358979;

  r *= pi / 180.0;

  Vertex origin = Vertex( -1000000, -1000000 );

  for( int i = 0; i < vertices.size(); ++i )
  {
    double x = vertices[i].x * cos( r ) - vertices[i].y * sin( r );
    double y = vertices[i].x * sin( r ) + vertices[i].y * cos( r );
    vertices[i].x = x;
    vertices[i].y = y;

    origin.x = max( -x, origin.x );
    origin.y = max( -y, origin.y );
  }
  
  if( offset ) offsetBy(Vertex(-origin.x,-origin.y));
}

Vertex Polygon::center()
{
  double maxX = -1000000000, minX = 1000000000, maxY = -1000000000, minY = 1000000000;

  for( int i = 0; i < vertices.size(); ++i )
  {
    Vertex v1 = vertices[i];

    minX = min( v1.x, minX );
    maxX = max( v1.x, maxX );
    minY = min( v1.y, minY );
    maxY = max( v1.y, maxY );
  }

  offsetBy(Vertex(-(minX+maxX)/2,-(minY+maxY)/2));

  return Vertex((minX+maxX)/2,(minY+maxY)/2);
}

Vertex Polygon::computeOffset( double r )
{
  double pi = 3.14159265358979;

  r *= pi / 180.0;

  double px = -1000000, py = -1000000, bx = -1000000, by = -1000000;

  double xRange[2] = {1000000000,-1000000000};
  double yRange[2] = {1000000000,-1000000000};

  for( int i = 0; i < vertices.size(); ++i )
  {
    double x = vertices[i].x * cos( r ) - vertices[i].y * sin( r );
    double y = vertices[i].x * sin( r ) + vertices[i].y * cos( r );

    xRange[0] = min(vertices[i].x,xRange[0]);
    xRange[1] = max(vertices[i].x,xRange[1]);

    yRange[0] = min(vertices[i].y,yRange[0]);
    yRange[1] = max(vertices[i].y,yRange[1]);

    px = max( -x, px );
    py = max( -y, py );
  }

  for( int i = 0; i < 2; ++i )
  {
    xRange[i] -= xRange[0];
    yRange[i] -= yRange[0];
  }

  for( int i = 0; i < 2; ++i )
  { 
    for( int j = 0; j < 2; ++j )
    {
      double x = xRange[j] * cos( r ) - yRange[i] * sin( r );
      double y = xRange[j] * sin( r ) + yRange[i] * cos( r );

      bx = max( -x, bx );
      by = max( -y, by );
    }
  }

  return Vertex( px - bx, py - by );
}
