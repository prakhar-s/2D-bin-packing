#include<vector>
#include<cstdlib>
#include"rectangle.h"

using namespace std;

class MaxRectsBinPack
{
public:
	// Instantiates a bin of size (0,0). Call Init to create a new bin.
	MaxRectsBinPack();

	MaxRectsBinPack(int width, int height, bool allowFlip = true);

	// Initializes the packer to an empty bin of width x height units
	void Init(int width, int height, bool allowFlip = true);

	// Specifies the different heuristic rules that can be used when deciding where to place a new rectangle.
	enum FreeRectChoiceHeuristic
	{
		RectBestShortSideFit, ///< -BSSF: Positions the rectangle against the short side of a free rectangle into which it fits the best.
		RectBestLongSideFit, ///< -BLSF: Positions the rectangle against the long side of a free rectangle into which it fits the best.
		RectBestAreaFit, ///< -BAF: Positions the rectangle into the smallest free rect into which it fits.
		RectBottomLeftRule, ///< -BL: Does the Tetris placement.
		RectContactPointRule ///< -CP: Choosest the placement where the rectangle touches other rects as much as possible.
	};

	/* Inserts the given list of rectangles in an offline/batch mode, possibly rotated.
	 * param rects The list of rectangles to insert. This vector will be destroyed in the process.
	 * param dst [out] This list will contain the packed rectangles. The indices will not correspond to that of rects.
	 * param method The rectangle placement rule to use when packing.
         */
	void Insert(std::vector<RectSize> &rects, std::vector<Rect> &dst, FreeRectChoiceHeuristic method);

	// Inserts a single rectangle into the bin, possibly rotated.
	Rect Insert(int width, int height, FreeRectChoiceHeuristic method);

	// Computes the ratio of used surface area to the total bin area.
	float Occupancy() const;

private:
	int binWidth;
	int binHeight;

	bool binAllowFlip;

	vector<Rect> usedRectangles;
	vector<Rect> freeRectangles;

	// Places the given rectangle into the bin.
	void PlaceRect(const Rect &node);

	// Computes the placement score for the -CP variant.
	int ContactPointScoreNode(int x, int y, int width, int height) const;

	Rect FindPositionForNewNodeBottomLeft(int width, int height, int &bestY, int &bestX) const;
	Rect FindPositionForNewNodeBestShortSideFit(int width, int height, int &bestShortSideFit, int &bestLongSideFit) const;
	Rect FindPositionForNewNodeBestLongSideFit(int width, int height, int &bestShortSideFit, int &bestLongSideFit) const;
	Rect FindPositionForNewNodeBestAreaFit(int width, int height, int &bestAreaFit, int &bestShortSideFit) const;
	Rect FindPositionForNewNodeContactPoint(int width, int height, int &contactScore) const;

	// return True if the free node was split.
	bool SplitFreeRectangle(Rect freeNode, const Rect &usedNode);

	// Goes through the free rectangle list and removes any redundant entries.
	void FixFreeList();
};
