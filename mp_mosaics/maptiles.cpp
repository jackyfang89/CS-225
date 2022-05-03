/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;

Point<3> convertToXYZ(LUVAPixel pixel) {
	return Point<3>(pixel.l, pixel.u, pixel.v);
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
					   vector<TileImage>& theTiles) {
	/*  procedure:
        1. build k-d tree using theTiles vector, so that 
            we can use findNearestNeighbor later
        2. create dynamically allocated MosaicCanvas with
            with same dimensions as theSource
        3. for every region in theSource, find the tileImage
            with the closeset avg color to avg color of region
        4. place found tileImage into MosaicCanvas at the same
            tile position as the sourceImage's region.
        5. return completed MosaicCanvas.

        procedure to build k-d tree from theTiles
        1. convert every TileImage into a LUVAPixel using 
            getAverageColor
        2. convert the LUVAPixels into Points
        3. build tree with this final vector of Points
        4. also need to build hashmap to get correct TileImage
            point -> tile
    */

	//convert tileImages to Points and store in hashMap and vector
	vector<Point<3>> points;
	map<Point<3>, TileImage*> map;

	for (size_t i = 0; i < theTiles.size(); ++i) {
		//get avgColor of each tile and conver to point
		Point<3> temp = convertToXYZ(theTiles[i].getAverageColor());
		points.push_back(temp);
		map.insert({temp, &theTiles[i]});
	}

	//make tree
	KDTree<3> tree(points);

	//make MosaicCanvas
	MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

	//access every region
	for (int i = 0; i < canvas->getRows(); ++i) {
		for (int j = 0; j < canvas->getColumns(); ++j) {
			Point<3> region = convertToXYZ(theSource.getRegionColor(i, j));
			Point<3> nearestPoint = tree.findNearestNeighbor(region);
			TileImage* nearestTile = (map.find(nearestPoint))->second;
			canvas->setTile(i, j, nearestTile);
		}
	}
	return canvas;
}
