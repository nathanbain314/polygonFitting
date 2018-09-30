#include "Vertex.h"

Vertex::Vertex( double _x, double _y )
{
  x = _x;
  y = _y;
}

Vertex::Vertex( const Vertex& rhs )
{
  x = rhs.x;
  y = rhs.y;
}

Vertex& Vertex::operator=( const Vertex& rhs )
{
  x = rhs.x;
  y = rhs.y;

  return *this;
}

bool Vertex::operator==( const Vertex& rhs )
{
  return (this->x == rhs.x && this->y == rhs.y);
}

bool Vertex::operator!=( const Vertex& rhs )
{
  return (this->x != rhs.x || this->y != rhs.y);
}

Vertex Vertex::offset( double _x, double _y )
{
  return Vertex( x + _x, y + _y );
}

Vertex Vertex::offset( Vertex &v )
{
  return Vertex( x + v.x, y + v.y );;
}
