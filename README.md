
# polygonFitting


This is a tool to find the largest possible scale and best fit of a convex polygon inside of another polygon. 
# Usage
## Creating polygons
Polygons can either be created manually or by generating it from an image using the alpha channel to find the edge.
#### Manually

    // Initialize Polygon
    Polygon P;
    // Add vertices
    P.addVertex(0,0);
    P.addVertex(1,0.5);
    P.addVertex(0,1);
    // Add edges
    P.addEdge(0,1);
    P.addEdge(1,2);
    P.addEdge(2,0);
    
![Manual Polygon](http://nathanbain.com/wikiImages/RunBestFitPolygon/manualPolygon.png)
#### Convex from Image

    // Initialize Polygon
    Polygon P;
    // Create polygons
    polygonFromAlphaImage( P, "image.png" );
    // Decimate
    decimate(P,0.01);
   ![Convex Polygon](http://nathanbain.com/wikiImages/RunBestFitPolygon/convexPolygon.png)
#### Concave from Image

    // Initialize Polygon
    Polygon P;
    // Create polygons
    concavePolygonFromAlphaImage( P, "image.png" );
    // Decimate
    decimate(P,0.01);
![Concave Polygon](http://nathanbain.com/wikiImages/RunBestFitPolygon/concavePolygon.png)
  #### Decimating 
  Decimating the polygon removes unnecessary vertices while retaining the general shape of the polygon. This allows for a huge speedup while creating approximately the same output.
  ![Decimate Polygon](http://nathanbain.com/wikiImages/RunBestFitPolygon/decimatePolygon.png)
  #### Clockwise
  Polygons have to be in clockwise shape in order for the algorithm to work. Creating from an image will already do that but otherwise it can be made clockwise with `P.makeClockwise();`

#### Best fit polygon

    // Initialize variables
    float scale, rotation;
    Vertex offset;
    // Compute best fit
    findBestFit( innerPolygon, outerPolygon, scale, rotation, offset, angleOffsetInDegrees );

This can work on any type of polygon: convex, concave, and even with a hole by using counter clockwise interior edges.
![Best fit](http://nathanbain.com/wikiImages/RunBestFitPolygon/bestFit.png)
The final input to the function, marked angleOffsetInDegrees, defines the angle that the interior polygon is rotated by before computing the next best fit. The smaller the angle, the greater the fit. However, the time it takes to compute the best fit is inversely proportional to the angleOffsetInDegrees.
Below is the same polygon with offsets 360 (1 rotation), 30 (12 rotations), and 1 (360 rotations)
![Angle Offset](http://nathanbain.com/wikiImages/RunBestFitPolygon/angleOffset.png)

# RunBestFitPolygon
Building this repository creates an executable to test out the polygon fitting function. 
## options
- -i,  --interior : The interior poylgon image
- -b, --bounding : The bounding polygon image
- -o, --output : The output image name
- -d, --decimate : Decimate value. A value of 0.01 usually works the best
- -a, --angleOffset : Value to offset poylgon by multiple times while computing the best fit.
- r, --resize : Multiplier to resize the output image by.

