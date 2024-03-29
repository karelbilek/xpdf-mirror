//========================================================================
//
// SplashPath.h
//
// Copyright 2003-2013 Glyph & Cog, LLC
//
//========================================================================

#ifndef SPLASHPATH_H
#define SPLASHPATH_H

#include <aconf.h>

#include "SplashTypes.h"

//------------------------------------------------------------------------
// SplashPathPoint
//------------------------------------------------------------------------

struct SplashPathPoint {
  SplashCoord x, y;
};

//------------------------------------------------------------------------
// SplashPath.flags
//------------------------------------------------------------------------

// first point on each subpath sets this flag
#define splashPathFirst         0x01

// last point on each subpath sets this flag
#define splashPathLast          0x02

// if the subpath is closed, its first and last points must be
// identical, and must set this flag
#define splashPathClosed        0x04

// curve control points set this flag
#define splashPathCurve         0x08

//------------------------------------------------------------------------
// SplashPathHint
//------------------------------------------------------------------------

struct SplashPathHint {
  int ctrl0, ctrl1;
  int firstPt, lastPt;
  GBool projectingCap;
};

//------------------------------------------------------------------------
// SplashPath
//------------------------------------------------------------------------

class SplashPath {
public:

  // Create an empty path.
  SplashPath();

  // Copy a path.
  SplashPath *copy() { return new SplashPath(this); }

  ~SplashPath();

  // Append <path> to <this>.
  void append(SplashPath *path);

  // Start a new subpath.
  SplashError moveTo(SplashCoord x, SplashCoord y);

  // Add a line segment to the last subpath.
  SplashError lineTo(SplashCoord x, SplashCoord y);

  // Add a third-order (cubic) Bezier curve segment to the last
  // subpath.
  SplashError curveTo(SplashCoord x1, SplashCoord y1,
		      SplashCoord x2, SplashCoord y2,
		      SplashCoord x3, SplashCoord y3);

  // Close the last subpath, adding a line segment if necessary.  If
  // <force> is true, this adds a line segment even if the current
  // point is equal to the first point in the subpath.
  SplashError close(GBool force = gFalse);

  // Add a stroke adjustment hint.  The controlling segments are
  // <ctrl0> and <ctrl1> (where segments are identified by their first
  // point), and the points to be adjusted are <firstPt> .. <lastPt>.
  // <projectingCap> is true if the points are part of a projecting
  // line cap.
  void addStrokeAdjustHint(int ctrl0, int ctrl1, int firstPt, int lastPt,
			   GBool projectingCap = gFalse);

  // Add (<dx>, <dy>) to every point on this path.
  void offset(SplashCoord dx, SplashCoord dy);

  // Get the points on the path.
  int getLength() { return length; }
  void getPoint(int i, SplashCoord *x, SplashCoord *y, Guchar *f)
    { *x = pts[i].x; *y = pts[i].y; *f = flags[i]; }

  // Get the current point.
  GBool getCurPt(SplashCoord *x, SplashCoord *y);

  // Returns true if the path contains one or more zero length
  // subpaths.
  GBool containsZeroLengthSubpaths();

private:

  SplashPath(SplashPath *path);
  void grow(int nPts);
  GBool noCurrentPoint() { return curSubpath == length; }
  GBool onePointSubpath() { return curSubpath == length - 1; }
  GBool openSubpath() { return curSubpath < length - 1; }

  SplashPathPoint *pts;		// array of points
  Guchar *flags;		// array of flags
  int length, size;		// length/size of the pts and flags arrays
  int curSubpath;		// index of first point in last subpath

  SplashPathHint *hints;	// list of hints
  int hintsLength, hintsSize;

  friend class SplashXPath;
  friend class Splash;
};

#endif
