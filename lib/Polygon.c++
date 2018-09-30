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

void Polygon::rotateBy( double r )
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

  offsetBy(origin);
}
