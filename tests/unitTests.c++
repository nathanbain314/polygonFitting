#include <gtest/gtest.h>

#include "PolygonFitting.h"

// Vertex Tests

TEST( VertexTest, Constructor )
{
  Vertex v( 5.0, -2.321 );

  ASSERT_EQ( 5.0, v.x );
  ASSERT_EQ( -2.321, v.y );
}

TEST( VertexTest, CopyConstructor )
{
  Vertex p( 5.0, -2.321 );

  Vertex v( p );

  ASSERT_EQ( 5.0, v.x );
  ASSERT_EQ( -2.321, v.y );
}

TEST( VertexTest, CopyAssignmentConstructor )
{
  Vertex p( 5.0, -2.321 );

  Vertex v = p;

  ASSERT_EQ( 5.0, v.x );
  ASSERT_EQ( -2.321, v.y );
}

TEST( VertexTest, Equality )
{
  ASSERT_TRUE( Vertex( 0.0, -0.0 ) == Vertex( 0.0, 0.0 ) );
  ASSERT_TRUE( Vertex( 5.0, -2.321 ) == Vertex( 5.0, -2.321 ) );
  ASSERT_TRUE( Vertex( 5.0, 2.321 ) == Vertex( 5.0, 2.321 ) );
  ASSERT_TRUE( Vertex( -5.0, -2.321 ) == Vertex( -5.0, -2.321 ) );

  ASSERT_FALSE( Vertex( 0.0, 0.0 ) == Vertex( 1.0, 0.0 ) );
  ASSERT_FALSE( Vertex( 0.0, 0.0 ) == Vertex( 0.0, 1.0 ) );
  ASSERT_FALSE( Vertex( 5.0, -2.321 ) == Vertex( -5.0, 2.321 ) );
  ASSERT_FALSE( Vertex( -5.0, 2.321 ) == Vertex( 5.0, 2.321 ) );
}

TEST( VertexTest, Inequality )
{
  ASSERT_TRUE( Vertex( 0.0, 0.0 ) != Vertex( 1.0, 0.0 ) );
  ASSERT_TRUE( Vertex( 0.0, 0.0 ) != Vertex( 0.0, 1.0 ) );
  ASSERT_TRUE( Vertex( 5.0, -2.321 ) != Vertex( -5.0, 2.321 ) );
  ASSERT_TRUE( Vertex( -5.0, 2.321 ) != Vertex( 5.0, 2.321 ) );

  ASSERT_FALSE( Vertex( 0.0, 0.0 ) != Vertex( -0.0, 0.0 ) );
  ASSERT_FALSE( Vertex( 5.0, -2.321 ) != Vertex( 5.0, -2.321 ) );
  ASSERT_FALSE( Vertex( 5.0, 2.321 ) != Vertex( 5.0, 2.321 ) );
  ASSERT_FALSE( Vertex( -5.0, -2.321 ) != Vertex( -5.0, -2.321 ) );
}

TEST( VertexTest, OffsetValue )
{
  Vertex v( 5.0, -2.321 );

  v = v.offset( 2.3, 1.0 );

  ASSERT_NEAR( 7.3, v.x, 0.00001 );
  ASSERT_NEAR( -1.321, v.y, 0.00001 );
}

TEST( VertexTest, OffsetVertex )
{
  Vertex v( 5.0, -2.321 );

  v = v.offset( Vertex( 2.3, 1.0 ) );

  ASSERT_NEAR( 7.3, v.x, 0.00001 );
  ASSERT_NEAR( -1.321, v.y, 0.00001 );
}


// Edge Tests

TEST( EdgeTest, Constructor )
{
  Edge e( 1, 3 );

  ASSERT_EQ( 1, e.v1 );
  ASSERT_EQ( 3, e.v2 );
}

TEST( EdgeTest, CopyConstructor )
{
  Edge f( 1, 3 );

  Edge e( f );

  ASSERT_EQ( 1, e.v1 );
  ASSERT_EQ( 3, e.v2 );
}

TEST( EdgeTest, CopyAssignmentConstructor )
{
  Edge f( 1, 3 );

  Edge e = f;

  ASSERT_EQ( 1, e.v1 );
  ASSERT_EQ( 3, e.v2 );
}

TEST( EdgeTest, Equality )
{
   ASSERT_TRUE( Edge( 0, 0 ) == Edge( 0, 0 ) );
   ASSERT_TRUE( Edge( 0, 1 ) == Edge( 0, 1 ) );
   ASSERT_TRUE( Edge( 1, 3 ) == Edge( 1, 3 ) );
   ASSERT_TRUE( Edge( 234, 100 ) == Edge( 234, 100 ) );

   ASSERT_FALSE( Edge( 0, 0 ) == Edge( 0, 1 ) );
   ASSERT_FALSE( Edge( 1, 0 ) == Edge( 0, 1 ) );
   ASSERT_FALSE( Edge( 3, 1 ) == Edge( 1, 3 ) );
   ASSERT_FALSE( Edge( 233, 100 ) == Edge( 234, 100 ) );
}

TEST( EdgeTest, Inequality )
{
   ASSERT_TRUE( Edge( 0, 0 ) != Edge( 0, 1 ) );
   ASSERT_TRUE( Edge( 1, 0 ) != Edge( 0, 1 ) );
   ASSERT_TRUE( Edge( 3, 1 ) != Edge( 1, 3 ) );
   ASSERT_TRUE( Edge( 233, 100 ) != Edge( 234, 100 ) );

   ASSERT_FALSE( Edge( 0, 0 ) != Edge( 0, 0 ) );
   ASSERT_FALSE( Edge( 0, 1 ) != Edge( 0, 1 ) );
   ASSERT_FALSE( Edge( 1, 3 ) != Edge( 1, 3 ) );
   ASSERT_FALSE( Edge( 234, 100 ) != Edge( 234, 100 ) );
}


// Polygon Tests

TEST( PolygonTest, Constructor )
{
  vector< Vertex > v;
  vector< Edge > e;

  v.push_back( Vertex( 0, 0 ) );
  v.push_back( Vertex( 0, 2 ) );
  v.push_back( Vertex( 2, 3 ) );
  v.push_back( Vertex( 3, 3 ) );
  v.push_back( Vertex( 0, 3 ) );

  e.push_back( Edge( 0, 1 ) );
  e.push_back( Edge( 1, 2 ) );
  e.push_back( Edge( 2, 3 ) );
  e.push_back( Edge( 3, 4 ) );
  e.push_back( Edge( 4, 0 ) );

  Polygon P = Polygon( v, e );

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    ASSERT_TRUE( P.vertices[i] == v[i] );
  }

  for( int i = 0; i < P.edges.size(); ++i )
  {
    ASSERT_TRUE( P.edges[i] == e[i] );
  }
}

TEST( PolygonTest, CopyConstructor )
{
  vector< Vertex > v;
  vector< Edge > e;

  v.push_back( Vertex( 0, 0 ) );
  v.push_back( Vertex( 0, 2 ) );
  v.push_back( Vertex( 2, 3 ) );
  v.push_back( Vertex( 3, 3 ) );
  v.push_back( Vertex( 0, 3 ) );

  e.push_back( Edge( 0, 1 ) );
  e.push_back( Edge( 1, 2 ) );
  e.push_back( Edge( 2, 3 ) );
  e.push_back( Edge( 3, 4 ) );
  e.push_back( Edge( 4, 0 ) );

  Polygon R = Polygon( v, e );

  Polygon P( R );

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    ASSERT_TRUE( P.vertices[i] == v[i] );
  }

  for( int i = 0; i < P.edges.size(); ++i )
  {
    ASSERT_TRUE( P.edges[i] == e[i] );
  }
}

TEST( PolygonTest, CopyAssignmentConstructor )
{
  vector< Vertex > v;
  vector< Edge > e;

  v.push_back( Vertex( 0, 0 ) );
  v.push_back( Vertex( 0, 2 ) );
  v.push_back( Vertex( 2, 3 ) );
  v.push_back( Vertex( 3, 3 ) );
  v.push_back( Vertex( 0, 3 ) );

  e.push_back( Edge( 0, 1 ) );
  e.push_back( Edge( 1, 2 ) );
  e.push_back( Edge( 2, 3 ) );
  e.push_back( Edge( 3, 4 ) );
  e.push_back( Edge( 4, 0 ) );

  Polygon R = Polygon( v, e );

  Polygon P = R;

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    ASSERT_TRUE( P.vertices[i] == v[i] );
  }

  for( int i = 0; i < P.edges.size(); ++i )
  {
    ASSERT_TRUE( P.edges[i] == e[i] );
  }
}

TEST( PolygonTest, AddVertexUsingValues )
{
  vector< Vertex > v;

  v.push_back( Vertex( 0, 0 ) );
  v.push_back( Vertex( 0, 2 ) );
  v.push_back( Vertex( 2, 3 ) );
  v.push_back( Vertex( 3, 3 ) );
  v.push_back( Vertex( 0, 3 ) );

  Polygon P;

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    P.addVertex( v[i].x, v[i].y );
  }

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    ASSERT_TRUE( P.vertices[i] == v[i] );
  }
}

TEST( PolygonTest, AddVertexUsingVertex )
{
  vector< Vertex > v;

  v.push_back( Vertex( 0, 0 ) );
  v.push_back( Vertex( 0, 2 ) );
  v.push_back( Vertex( 2, 3 ) );
  v.push_back( Vertex( 3, 3 ) );
  v.push_back( Vertex( 0, 3 ) );

  Polygon P;

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    P.addVertex( v[i] );
  }

  for( int i = 0; i < P.vertices.size(); ++i )
  {
    ASSERT_TRUE( P.vertices[i] == v[i] );
  }
}

TEST( PolygonTest, AddEdgeUsingValues )
{
  vector< Edge > e;

  e.push_back( Edge( 0, 1 ) );
  e.push_back( Edge( 1, 2 ) );
  e.push_back( Edge( 2, 3 ) );
  e.push_back( Edge( 3, 4 ) );
  e.push_back( Edge( 4, 0 ) );

  Polygon P;

  for( int i = 0; i < P.edges.size(); ++i )
  {
    P.addEdge( P.edges[i].v1, P.edges[i].v2 );
  }

  for( int i = 0; i < P.edges.size(); ++i )
  {
    ASSERT_TRUE( P.edges[i] == e[i] );
  }
}

TEST( PolygonTest, AddEdgeUsingEdge )
{
  vector< Edge > e;

  e.push_back( Edge( 0, 1 ) );
  e.push_back( Edge( 1, 2 ) );
  e.push_back( Edge( 2, 3 ) );
  e.push_back( Edge( 3, 4 ) );
  e.push_back( Edge( 4, 0 ) );

  Polygon P;

  for( int i = 0; i < P.edges.size(); ++i )
  {
    P.addEdge( P.edges[i] );
  }

  for( int i = 0; i < P.edges.size(); ++i )
  {
    ASSERT_TRUE( P.edges[i] == e[i] );
  }
}

TEST( PolygonTest, PolygonScaleBy )
{
  Polygon P;

  P.addVertex( 0, 0 );
  P.addVertex( 0, 2 );
  P.addVertex( 2, 3 );
  P.addVertex( 3, 3 );
  P.addVertex( 0, 3 );

  P.scaleBy( 1 );

  ASSERT_TRUE( P.vertices[0] == Vertex( 0, 0 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 0, 2 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 2, 3 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 3, 3 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0, 3 ) );

  P.scaleBy( 2 );

  ASSERT_TRUE( P.vertices[0] == Vertex( 0, 0 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 0, 4 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 4, 6 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 6, 6 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0, 6 ) );

  P.scaleBy( 0.25 );

  ASSERT_TRUE( P.vertices[0] == Vertex( 0, 0 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 0, 1 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 1, 1.5 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 1.5, 1.5 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0, 1.5 ) );
}

TEST( PolygonTest, PolygonOffsetBy )
{
  Polygon P;

  P.addVertex( 0, 0 );
  P.addVertex( 0, 2 );
  P.addVertex( 2, 3 );
  P.addVertex( 3, 3 );
  P.addVertex( 0, 3 );

  P.offsetBy(  Vertex( 0, 0 ) );

  ASSERT_TRUE( P.vertices[0] == Vertex( 0, 0 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 0, 2 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 2, 3 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 3, 3 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0, 3 ) );

  P.offsetBy(  Vertex( -3, 2.5 ) );

  ASSERT_TRUE( P.vertices[0] == Vertex( -3, 2.5 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( -3, 4.5 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( -1, 5.5 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 0, 5.5 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( -3, 5.5 ) );

  P.offsetBy(  Vertex( 1, 2.5 ) );

  ASSERT_TRUE( P.vertices[0] == Vertex( -2, 5 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( -2, 7 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 0, 8 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 1, 8 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( -2, 8 ) );
}

TEST( PolygonTest, PolygonRotateBy )
{
  Polygon P;

  P.addVertex( 0, 0 );
  P.addVertex( 0, 2 );
  P.addVertex( 2, 3 );
  P.addVertex( 3, 3 );
  P.addVertex( 0, 3 );

  P.rotateBy(0);

  ASSERT_TRUE( P.vertices[0] == Vertex( 0, 0 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 0, 2 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 2, 3 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 3, 3 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0, 3 ) );

  P.rotateBy(90);

  ASSERT_TRUE( P.vertices[0] == Vertex( 3, 0 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 1, 0 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 0, 2 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 0, 3 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0, 0 ) );

  P.rotateBy(13);

  ASSERT_TRUE( P.vertices[0] == Vertex( 3.59796, 0.67485 ) );
  ASSERT_TRUE( P.vertices[1] == Vertex( 1.64922, 0.22495 ) );
  ASSERT_TRUE( P.vertices[2] == Vertex( 0.22495, 1.94874 ) );
  ASSERT_TRUE( P.vertices[3] == Vertex( 0.00000, 2.92311 ) );
  ASSERT_TRUE( P.vertices[4] == Vertex( 0.67485, 0.00000 ) );
}


// PolygonFitting Tests

TEST( PolygonFittingTest, createOffsetEdges )
{
  Polygon P;

  P.addVertex( 0, 0 );
  P.addVertex( 0, 1 );
  P.addVertex( 1, 1 );
  P.addVertex( 1, 0 );

  P.addEdge( 0, 1 );
  P.addEdge( 1, 2 );
  P.addEdge( 2, 3 );
  P.addEdge( 3, 0 );

  Polygon R;

  R.addVertex( 0, 0 );
  R.addVertex( 0, 2 );
  R.addVertex( 2, 3 );
  R.addVertex( 3, 3 );
  R.addVertex( 0, 3 );

  R.addEdge( 0, 1 ); 
  R.addEdge( 1, 2 ); 
  R.addEdge( 2, 3 ); 
  R.addEdge( 3, 4 ); 
  R.addEdge( 4, 0 ); 

  PolygonFitting pf( P, R );

  pf.createOffsetEdges();

  ASSERT_TRUE( pf.vertices.size() == 20 );

  ASSERT_TRUE( pf.vertices[0] == Vertex( 0, 0 ) );
  ASSERT_TRUE( pf.vertices[1] == Vertex( 0, 1 ) );
  ASSERT_TRUE( pf.vertices[2] == Vertex( 1, 1 ) );
  ASSERT_TRUE( pf.vertices[3] == Vertex( 1, 0 ) );

  ASSERT_TRUE( pf.vertices[4] == Vertex( 0, 2 ) );
  ASSERT_TRUE( pf.vertices[5] == Vertex( 0, 3 ) );
  ASSERT_TRUE( pf.vertices[6] == Vertex( 1, 3 ) );
  ASSERT_TRUE( pf.vertices[7] == Vertex( 1, 2 ) );

  ASSERT_TRUE( pf.vertices[8] == Vertex( 2, 3 ) );
  ASSERT_TRUE( pf.vertices[9] == Vertex( 2, 4 ) );
  ASSERT_TRUE( pf.vertices[10] == Vertex( 3, 4 ) );
  ASSERT_TRUE( pf.vertices[11] == Vertex( 3, 3 ) );

  ASSERT_TRUE( pf.vertices[12] == Vertex( 3, 3 ) );
  ASSERT_TRUE( pf.vertices[13] == Vertex( 3, 4 ) );
  ASSERT_TRUE( pf.vertices[14] == Vertex( 4, 4 ) );
  ASSERT_TRUE( pf.vertices[15] == Vertex( 4, 3 ) );

  ASSERT_TRUE( pf.vertices[16] == Vertex( 0, 3 ) );
  ASSERT_TRUE( pf.vertices[17] == Vertex( 0, 4 ) );
  ASSERT_TRUE( pf.vertices[18] == Vertex( 1, 4 ) );
  ASSERT_TRUE( pf.vertices[19] == Vertex( 1, 3 ) );
}

TEST( PolygonFittingTest, ccw )
{
  ASSERT_EQ( -2, ccw( Vertex( 0, 0 ), Vertex( 1, 1 ), Vertex( 3, 1 ) ) );
  ASSERT_EQ( 2, ccw( Vertex( 3, 2 ), Vertex( 1, 5 ), Vertex( 3, 1 ) ) );
  ASSERT_EQ( -2737.2, ccw( Vertex( 0.5, 1.2 ), Vertex( 13, 100 ), Vertex( 32, 31.2 ) ) );
  ASSERT_EQ( -23.1, ccw( Vertex( -20, -0 ), Vertex( -1.3, 0.2 ), Vertex( 2, -1 ) ) ) ;
}

TEST( PolygonFittingTest, minY )
{
  ASSERT_TRUE( minY( Vertex( 0, 0 ), Vertex( 2, 2 ) ) );
  ASSERT_TRUE( minY( Vertex( 0, -0 ), Vertex( -2, 2 ) ) );
  ASSERT_TRUE( minY( Vertex( 0, 0 ), Vertex( 2, 0 ) ) );
  ASSERT_TRUE( minY( Vertex( -10, 0 ), Vertex( 2, 0 ) ) );

  ASSERT_FALSE( minY( Vertex( 0, 0 ), Vertex( 2, -2 ) ) );
  ASSERT_FALSE( minY( Vertex( 0, 0 ), Vertex( -2, -2 ) ) );
  ASSERT_FALSE( minY( Vertex( 0, 0 ), Vertex( -2, 0 ) ) );
  ASSERT_FALSE( minY( Vertex( -10, 0 ), Vertex( 10, -1 ) ) );
}

TEST( PolygonFittingTest, distance )
{
  ASSERT_NEAR( 0.0, distance( Vertex( 0, 2 ), Vertex( 0, 2 ) ), 0.00001 );
  ASSERT_NEAR( 16, distance( Vertex( 0, -2 ), Vertex( 0, 2 ) ), 0.00001 );
  ASSERT_NEAR( 19734.1565, distance( Vertex( 2.34, -12.3 ), Vertex( 139, 20.23 ) ), 0.00001 );
  ASSERT_NEAR( 1155.50567, distance( Vertex( -0.2324, -23.424 ), Vertex( -24.535, 0.3434 ) ), 0.00001 );
}

TEST( PolygonFittingTest, grahamScanSort )
{
  ASSERT_TRUE( grahamScanSort( Vertex( 0, 0 ), Vertex( 1, 1 ), Vertex( 3, 1 ) ) );
  ASSERT_TRUE( grahamScanSort( Vertex( 0.5, 1.2 ), Vertex( 13, 100 ), Vertex( 32, 31.2 ) ) );
  ASSERT_TRUE( grahamScanSort( Vertex( -20, -0 ), Vertex( -1.3, 0.2 ), Vertex( 2, -1 ) ) );
  ASSERT_FALSE( grahamScanSort( Vertex( 3, 2 ), Vertex( 1, 5 ), Vertex( 3, 1 ) ) );
}

TEST( PolygonFittingTest, grahamScan )
{
  vector< Vertex > v;
  vector< Edge > e;

  v.push_back( Vertex( 0, 0 ) );
  v.push_back( Vertex( 0, 2 ) );
  v.push_back( Vertex( 2, 3 ) );
  v.push_back( Vertex( 3, 3 ) );
  v.push_back( Vertex( 3, 0 ) );

  e = grahamScan( v );

  ASSERT_TRUE( e[0] == Edge( 0, 4 ) );
  ASSERT_TRUE( e[1] == Edge( 4, 3 ) );
  ASSERT_TRUE( e[2] == Edge( 3, 2 ) );
  ASSERT_TRUE( e[3] == Edge( 2, 1 ) );
  ASSERT_TRUE( e[4] == Edge( 1, 0 ) );

  v.push_back( Vertex( 1, 1 ) );

  e = grahamScan( v );

  ASSERT_TRUE( e[0] == Edge( 0, 4 ) );
  ASSERT_TRUE( e[1] == Edge( 4, 3 ) );
  ASSERT_TRUE( e[2] == Edge( 3, 2 ) );
  ASSERT_TRUE( e[3] == Edge( 2, 1 ) );
  ASSERT_TRUE( e[4] == Edge( 1, 0 ) );

  v.push_back( Vertex( -1, 1 ) );

  e = grahamScan( v );

  ASSERT_TRUE( e[0] == Edge( 0, 4 ) );
  ASSERT_TRUE( e[1] == Edge( 4, 3 ) );
  ASSERT_TRUE( e[2] == Edge( 3, 2 ) );
  ASSERT_TRUE( e[3] == Edge( 2, 1 ) );
  ASSERT_TRUE( e[4] == Edge( 1, 6 ) );
  ASSERT_TRUE( e[5] == Edge( 6, 0 ) );

  v.push_back( Vertex( 1, -1 ) );

  e = grahamScan( v );

  ASSERT_TRUE( e[0] == Edge( 7, 4 ) );
  ASSERT_TRUE( e[1] == Edge( 4, 3 ) );
  ASSERT_TRUE( e[2] == Edge( 3, 2 ) );
  ASSERT_TRUE( e[3] == Edge( 2, 1 ) );
  ASSERT_TRUE( e[4] == Edge( 1, 6 ) );
  ASSERT_TRUE( e[5] == Edge( 6, 0 ) );
  ASSERT_TRUE( e[6] == Edge( 0, 7 ) );

  v.push_back( Vertex( 2, -1 ) );

  e = grahamScan( v );

  ASSERT_TRUE( e[0] == Edge( 7, 8 ) );
  ASSERT_TRUE( e[1] == Edge( 8, 4 ) );
  ASSERT_TRUE( e[2] == Edge( 4, 3 ) );
  ASSERT_TRUE( e[3] == Edge( 3, 2 ) );
  ASSERT_TRUE( e[4] == Edge( 2, 1 ) );
  ASSERT_TRUE( e[5] == Edge( 1, 6 ) );
  ASSERT_TRUE( e[6] == Edge( 6, 0 ) );
  ASSERT_TRUE( e[7] == Edge( 0, 7 ) );

  v.push_back( Vertex( 0, -1 ) );

  e = grahamScan( v );

  ASSERT_TRUE( e[0] == Edge( 9, 8 ) );
  ASSERT_TRUE( e[1] == Edge( 8, 4 ) );
  ASSERT_TRUE( e[2] == Edge( 4, 3 ) );
  ASSERT_TRUE( e[3] == Edge( 3, 2 ) );
  ASSERT_TRUE( e[4] == Edge( 2, 1 ) );
  ASSERT_TRUE( e[5] == Edge( 1, 6 ) );
  ASSERT_TRUE( e[6] == Edge( 6, 9 ) );
}

TEST( PolygonFittingTest, reverseEdge )
{
  Edge e1, e2;

  e1 = Edge( 1, 2 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( 2, 1 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( -1, 2 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( 1, -2 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( 1, 1 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( 0, 2 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( 1, 20323 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );

  e1 = Edge( 0, 0 );
  e2 = reverseEdge( e1 );

  ASSERT_TRUE( e1.v1 == e2.v2 && e1.v2 == e2.v1 );
}

TEST( PolygonFittingTest, intersection )
{
  pair< double, double > t;

  Vertex v1, v2, v3, v4;

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  v3 = Vertex( 1, 0 );
  v4 = Vertex( 0, 1 );

  t = intersection( v1, v2, v3, v4 );

  ASSERT_NEAR( 0.5, t.first, 0.00001 );
  ASSERT_NEAR( 0.5, t.second , 0.00001 );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 0 );
  v3 = Vertex( 0, 0 );
  v4 = Vertex( 0, 1 );

  t = intersection( v1, v2, v3, v4 );

  ASSERT_NEAR( 0.0, t.first, 0.00001 );
  ASSERT_NEAR( 0.0, t.second , 0.00001 );

  v1 = Vertex( 2, 0 );
  v2 = Vertex( 1, 0 );
  v3 = Vertex( 0, 0 );
  v4 = Vertex( 0, 1 );

  t = intersection( v1, v2, v3, v4 );

  ASSERT_NEAR( 2.0, t.first, 0.00001 );
  ASSERT_NEAR( 0.0, t.second , 0.00001 );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 0 );
  v3 = Vertex( 0, -2 );
  v4 = Vertex( 0, -1 );

  t = intersection( v1, v2, v3, v4 );

  ASSERT_NEAR( 0.0, t.first, 0.00001 );
  ASSERT_NEAR( 2.0, t.second , 0.00001 );

  v1 = Vertex( 0.234753, 1.2742 );
  v2 = Vertex( 12.524, 24.0 );
  v3 = Vertex( 2.5, 0.737 );
  v4 = Vertex( 40.240248, 3.230 );

  t = intersection( v1, v2, v3, v4 );

  ASSERT_NEAR( -0.0313423, t.first, 0.00001 );
  ASSERT_NEAR( -0.0702279, t.second , 0.00001 );

  v1 = Vertex( 439.241, -392.32 );
  v2 = Vertex( 1.323, 0.014 );
  v3 = Vertex( 0.00234, 0.03432 );
  v4 = Vertex( -0.0087834, 0.003434 );

  t = intersection( v1, v2, v3, v4 );

  ASSERT_NEAR( 1.00229, t.first, 0.00001 );
  ASSERT_NEAR( -28.46573, t.second , 0.00001 );
}

TEST( PolygonFittingTest, intersectionPoint )
{
  double t;

  Vertex v1, v2, p;

  t = 0.5;

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );

  p = intersectionPoint( t, v1, v2 );

  ASSERT_NEAR( 0.5, p.x, 0.00001 );
  ASSERT_NEAR( 0.5, p.y, 0.00001 );

  t = 0.344;

  v1 = Vertex( -2, 3 );
  v2 = Vertex( 3, 8 );

  p = intersectionPoint( t, v1, v2 );

  ASSERT_NEAR( -0.28, p.x, 0.00001 );
  ASSERT_NEAR( 4.72, p.y, 0.00001 );

  t = 2.344;

  v1 = Vertex( -2, 3 );
  v2 = Vertex( 3, 8 );

  p = intersectionPoint( t, v1, v2 );

  ASSERT_NEAR( 9.72, p.x, 0.00001 );
  ASSERT_NEAR( 14.72, p.y, 0.00001 );

  t = -5.344;

  v1 = Vertex( -2, 3 );
  v2 = Vertex( 3, 8 );

  p = intersectionPoint( t, v1, v2 );

  ASSERT_NEAR( -28.72, p.x, 0.00001 );
  ASSERT_NEAR( -23.72, p.y, 0.00001 );
}

TEST( PolygonFittingTest, computeContributingEdges )
{
  Polygon P;

  P.addVertex( 0, 0 );
  P.addVertex( 0, 1 );
  P.addVertex( 1, 1 );
  P.addVertex( 1, 0 );

  P.addEdge( 0, 1 );
  P.addEdge( 1, 2 );
  P.addEdge( 2, 3 );
  P.addEdge( 3, 0 );

  Polygon R;

  R.addVertex( 0, 0 );
  R.addVertex( 0, 2 );
  R.addVertex( 2, 3 );
  R.addVertex( 3, 3 );
  R.addVertex( 0, 3 );

  R.addEdge( 0, 1 ); 
  R.addEdge( 1, 2 ); 
  R.addEdge( 2, 3 ); 
  R.addEdge( 3, 4 ); 
  R.addEdge( 4, 0 ); 

  PolygonFitting pf;

  pf = PolygonFitting( P, R );

  pf.computeContributingEdges();

  ASSERT_TRUE( pf.contributingEdges[0] == Edge( 3, 15 ) );
  ASSERT_TRUE( pf.contributingEdges[1] == Edge( 14, 17 ) );
  ASSERT_TRUE( pf.contributingEdges[2] == Edge( 17, 1 ) );
}

TEST( PolygonFittingTest, isOnLineSegment )
{
  Vertex v1, v2, p;

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 0, 0 );

  ASSERT_TRUE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 1, 1 );

  ASSERT_TRUE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 0.5, 0.5 );

  ASSERT_TRUE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 1, 1 );

  ASSERT_TRUE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 2, 2 );

  ASSERT_FALSE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( -1, -1 );

  ASSERT_FALSE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 0, 2 );

  ASSERT_FALSE( isOnLineSegment( p, v1, v2 ) );

  v1 = Vertex( 0, 0 );
  v2 = Vertex( 1, 1 );
  p = Vertex( 0, 0.2 );

  ASSERT_FALSE( isOnLineSegment( p, v1, v2 ) );
}

TEST( PolygonFittingTest, isValidFit )
{
  Polygon P;

  P.addVertex( 0, 0 );
  P.addVertex( 0, 1 );
  P.addVertex( 1, 1 );
  P.addVertex( 1, 0 );

  P.addEdge( 0, 1 );
  P.addEdge( 1, 2 );
  P.addEdge( 2, 3 );
  P.addEdge( 3, 0 );

  Polygon R;

  R.addVertex( 0, 0 );
  R.addVertex( 0, 2 );
  R.addVertex( 2, 3 );
  R.addVertex( 3, 3 );
  R.addVertex( 3, 0 );

  R.addEdge( 0, 1 ); 
  R.addEdge( 1, 2 ); 
  R.addEdge( 2, 3 ); 
  R.addEdge( 3, 4 ); 
  R.addEdge( 4, 0 ); 

  PolygonFitting pf;

  pf = PolygonFitting( P, R );

  ASSERT_TRUE( pf.isValidFit() );

  P.addVertex( -1, -1 );

  pf = PolygonFitting( P, R );

  ASSERT_FALSE( pf.isValidFit() );

  P.offsetBy( Vertex( 1, 1 ) );

  pf = PolygonFitting( P, R );

  ASSERT_TRUE( pf.isValidFit() );

  P.scaleBy( 2 );

  pf = PolygonFitting( P, R );

  ASSERT_FALSE( pf.isValidFit() );
}

TEST( PolygonFittingTest, intersectionEdges )
{
  Vertex v1, v2, v3, v4, v5, v6, o1, o2, o3;

  double t;

  v1 = Vertex( 39.4394, 0.483 );
  v2 = Vertex( 2, 0 );
  v3 = Vertex( 0, 0 );
  v4 = Vertex( -4.23, 393 );
  v5 = Vertex( -32.2934, 4284.2384 );
  v6 = Vertex( 493.4 , -4.904 );

  o1 = Vertex( 1, 1 );
  o2 = Vertex( 1, 0 );
  o3 = Vertex( 4.23, 1.39 );

  t = intersectionEdges( v1, v2, v3, v4, v5, v6, o1, o2, o3 );

  ASSERT_NEAR( -149.8525258, t, 0.00001 );

  v1 = Vertex( 1, 1 );
  v2 = Vertex( 0, 0 );

  t = intersectionEdges( v1, v2, v3, v4, v5, v6, o1, o2, o3 );

  ASSERT_NEAR( -149.7981258, t, 0.00001 );

  o1 = Vertex( 11.73, 1.305);

  t = intersectionEdges( v1, v2, v3, v4, v5, v6, o1, o2, o3 );

  ASSERT_NEAR( -110.9192664, t, 0.00001 );

  o2 = Vertex( -5.73, 19.305);

  t = intersectionEdges( v1, v2, v3, v4, v5, v6, o1, o2, o3 );

  ASSERT_NEAR( -42.16823799, t, 0.00001 );
}

TEST( PolygonFittingTest, findBestScale )
{
  Polygon P;

  P.addVertex( 100, 0 );
  P.addVertex( 120, 0 );
  P.addVertex( 128, 8 );
  P.addVertex( 130, 16 );
  P.addVertex( 130, 22 );
  P.addVertex( 114, 126 );
  P.addVertex( 112, 132 );
  P.addVertex( 110, 136 );
  P.addVertex( 102, 144 );
  P.addVertex( 66, 174 );
  P.addVertex( 44, 174 );
  P.addVertex( 40, 170 );
  P.addVertex( 38, 166 );
  P.addVertex( 0, 86 );
  P.addVertex( 0, 76 );
  P.addVertex( 44, 26 );
  P.addVertex( 54, 16 );
  P.addVertex( 60, 12 );
  P.addVertex( 72, 8 );

  P.addEdge( 0, 1 );
  P.addEdge( 1, 2 );
  P.addEdge( 2, 3 );
  P.addEdge( 3, 4 );
  P.addEdge( 4, 5 );
  P.addEdge( 5, 6 );
  P.addEdge( 6, 7 );
  P.addEdge( 7, 8 );
  P.addEdge( 8, 9 );
  P.addEdge( 9, 10 );
  P.addEdge( 10, 11 );
  P.addEdge( 11, 12 );
  P.addEdge( 12, 13 );
  P.addEdge( 13, 14 );
  P.addEdge( 14, 15 );
  P.addEdge( 15, 16 );
  P.addEdge( 16, 17 );
  P.addEdge( 17, 18 );
  P.addEdge( 18, 0 );

  {
    Polygon R;

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

    double scale;

    Vertex offset;

    PolygonFitting pf;

    pf = PolygonFitting( P, R );

    pf.computeContributingEdges();

    ASSERT_TRUE( pf.findBestScale( scale, offset ) );
    ASSERT_NEAR( 0.1355761355, scale, 0.00001 );
    ASSERT_NEAR( 34.331498, offset.x, 0.00001 );
    ASSERT_NEAR( 100.5528189, offset.y, 0.00001 );

    P.rotateBy( 180 );

    pf = PolygonFitting( P, R );

    pf.computeContributingEdges();

    ASSERT_TRUE( pf.findBestScale( scale, offset ) );
    ASSERT_NEAR( 0.1407163316, scale, 0.00001 );
    ASSERT_NEAR( 33.3216358, offset.x, 0.00001 );
    ASSERT_NEAR( 99.18611481, offset.y, 0.00001 );

    P.rotateBy( 90 );

    pf = PolygonFitting( P, R );

    pf.computeContributingEdges();

    ASSERT_TRUE( pf.findBestScale( scale, offset ) );
    ASSERT_NEAR( 0.1916086755, scale, 0.00001 );
    ASSERT_NEAR( 36.55123944, offset.x, 0.00001 );
    ASSERT_NEAR( 100.1514615, offset.y, 0.00001 );

    P.rotateBy( 30 );

    pf = PolygonFitting( P, R );

    pf.computeContributingEdges();

    ASSERT_FALSE( pf.findBestScale( scale, offset ) );
    ASSERT_NEAR( 0.1916086755, scale, 0.00001 );
    ASSERT_NEAR( 36.55123944, offset.x, 0.00001 );
    ASSERT_NEAR( 100.1514615, offset.y, 0.00001 );

    P.rotateBy( 10 );

    pf = PolygonFitting( P, R );

    pf.computeContributingEdges();

    ASSERT_FALSE( pf.findBestScale( scale, offset ) );
    ASSERT_NEAR( 0.1916086755, scale, 0.00001 );
    ASSERT_NEAR( 36.55123944, offset.x, 0.00001 );
    ASSERT_NEAR( 100.1514615, offset.y, 0.00001 );

    P.rotateBy( 1 );

    pf = PolygonFitting( P, R );

    pf.computeContributingEdges();

    ASSERT_FALSE( pf.findBestScale( scale, offset ) );
    ASSERT_NEAR( 0.1916086755, scale, 0.00001 );
    ASSERT_NEAR( 36.55123944, offset.x, 0.00001 );
    ASSERT_NEAR( 100.1514615, offset.y, 0.00001 );
  }
}

TEST( PolygonFittingTest, findBestFit )
{
  Polygon P;

  P.addVertex( 100, 0 );
  P.addVertex( 120, 0 );
  P.addVertex( 128, 8 );
  P.addVertex( 130, 16 );
  P.addVertex( 130, 22 );
  P.addVertex( 114, 126 );
  P.addVertex( 112, 132 );
  P.addVertex( 110, 136 );
  P.addVertex( 102, 144 );
  P.addVertex( 66, 174 );
  P.addVertex( 44, 174 );
  P.addVertex( 40, 170 );
  P.addVertex( 38, 166 );
  P.addVertex( 0, 86 );
  P.addVertex( 0, 76 );
  P.addVertex( 44, 26 );
  P.addVertex( 54, 16 );
  P.addVertex( 60, 12 );
  P.addVertex( 72, 8 );

  P.addEdge( 0, 1 );
  P.addEdge( 1, 2 );
  P.addEdge( 2, 3 );
  P.addEdge( 3, 4 );
  P.addEdge( 4, 5 );
  P.addEdge( 5, 6 );
  P.addEdge( 6, 7 );
  P.addEdge( 7, 8 );
  P.addEdge( 8, 9 );
  P.addEdge( 9, 10 );
  P.addEdge( 10, 11 );
  P.addEdge( 11, 12 );
  P.addEdge( 12, 13 );
  P.addEdge( 13, 14 );
  P.addEdge( 14, 15 );
  P.addEdge( 15, 16 );
  P.addEdge( 16, 17 );
  P.addEdge( 17, 18 );
  P.addEdge( 18, 0 );

  {
    Polygon R;

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

    double scale, rotation;

    Vertex offset;

    findBestFit( P, R, scale, rotation, offset, 360 );

    ASSERT_NEAR( 0.1355761355, scale, 0.00001 );
    ASSERT_NEAR( 0, rotation, 0.00001 );
    ASSERT_NEAR( 34.331498, offset.x, 0.00001 );
    ASSERT_NEAR( 100.5528189, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 90 );

    ASSERT_NEAR( 0.1916086755, scale, 0.00001 );
    ASSERT_NEAR( 270, rotation, 0.00001 );
    ASSERT_NEAR( 36.55123944, offset.x, 0.00001 );
    ASSERT_NEAR( 100.1514615, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 30 );

    ASSERT_NEAR( 0.1970127137, scale, 0.00001 );
    ASSERT_NEAR( 60, rotation, 0.00001 );
    ASSERT_NEAR( 28.42356773, offset.x, 0.00001 );
    ASSERT_NEAR( 92.44016929, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 1 );

    ASSERT_NEAR( 0.2001350338, scale, 0.00001 );
    ASSERT_NEAR( 64, rotation, 0.00001 );
    ASSERT_NEAR( 29.15747965, offset.x, 0.00001 );
    ASSERT_NEAR( 92.87804002, offset.y, 0.00001 );
  }

  {
    Polygon R;

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

    double scale, rotation;

    Vertex offset;

    findBestFit( P, R, scale, rotation, offset, 360 );

    ASSERT_NEAR( 0.03792666436, scale, 0.00001 );
    ASSERT_NEAR( 0, rotation, 0.00001 );
    ASSERT_NEAR( 253.0447875, offset.x, 0.00001 );
    ASSERT_NEAR( 34.6154, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 90 );

    ASSERT_NEAR( 0.03899882103, scale, 0.00001 );
    ASSERT_NEAR( 270, rotation, 0.00001 );
    ASSERT_NEAR( 252.23501, offset.x, 0.00001 );
    ASSERT_NEAR( 34.6154, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 30 );

    ASSERT_NEAR( 0.03899882103, scale, 0.00001 );
    ASSERT_NEAR( 270, rotation, 0.00001 );
    ASSERT_NEAR( 252.23501, offset.x, 0.00001 );
    ASSERT_NEAR( 34.6154, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 1 );

    ASSERT_NEAR( 0.04049394624, scale, 0.00001 );
    ASSERT_NEAR( 261, rotation, 0.00001 );
    ASSERT_NEAR( 251.8643078, offset.x, 0.00001 );
    ASSERT_NEAR( 33.67141048, offset.y, 0.00001 );
  }

  {
    Polygon R;

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

    double scale, rotation;

    Vertex offset;

    findBestFit( P, R, scale, rotation, offset, 360 );

    ASSERT_NEAR( 0.0730226525, scale, 0.00001 );
    ASSERT_NEAR( 0, rotation, 0.00001 );
    ASSERT_NEAR( 790.5153901, offset.x, 0.00001 );
    ASSERT_NEAR( 933.4888362, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 90 );

    ASSERT_NEAR( 0.110734745, scale, 0.00001 );
    ASSERT_NEAR( 90, rotation, 0.00001 );
    ASSERT_NEAR( 788.3378281, offset.x, 0.00001 );
    ASSERT_NEAR( 933.4226286, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 30 );

    ASSERT_NEAR( 0.110734745, scale, 0.00001 );
    ASSERT_NEAR( 90, rotation, 0.00001 );
    ASSERT_NEAR( 788.3378281, offset.x, 0.00001 );
    ASSERT_NEAR( 933.4226286, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 1 );

    ASSERT_NEAR( 0.1123282616, scale, 0.00001 );
    ASSERT_NEAR( 107, rotation, 0.00001 );
    ASSERT_NEAR( 785.7595005, offset.x, 0.00001 );
    ASSERT_NEAR( 931.2288503, offset.y, 0.00001 );
  }

  {
    Polygon R;

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

    double scale, rotation;

    Vertex offset;

    findBestFit( P, R, scale, rotation, offset, 360 );

    ASSERT_NEAR( 0.01612903226, scale, 0.00001 );
    ASSERT_NEAR( 0, rotation, 0.00001 );
    ASSERT_NEAR( 0.9032258065, offset.x, 0.00001 );
    ASSERT_NEAR( 0, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 90 );

    ASSERT_NEAR( 0.01724137931, scale, 0.00001 );
    ASSERT_NEAR( 90, rotation, 0.00001 );
    ASSERT_NEAR( -1.33226763e-15, offset.x, 0.00001 );
    ASSERT_NEAR( -2.116920477e-15, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 30 );

    ASSERT_NEAR( 0.01908272696, scale, 0.00001 );
    ASSERT_NEAR( 120, rotation, 0.00001 );
    ASSERT_NEAR( -0.3451279076, offset.x, 0.00001 );
    ASSERT_NEAR( -0.6992105068, offset.y, 0.00001 );

    findBestFit( P, R, scale, rotation, offset, 1 );

    ASSERT_NEAR( 0.02008602563, scale, 0.00001 );
    ASSERT_NEAR( 115, rotation, 0.00001 );
    ASSERT_NEAR( -0.5432781591, offset.x, 0.00001 );
    ASSERT_NEAR( -0.7470074687, offset.y, 0.00001 );
  }
}

int main( int argc, char **argv )
{
  testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS( );
}