//========================================================================
//
// BuiltinFont.h
//
// Copyright 2001-2003 Glyph & Cog, LLC
//
//========================================================================

#ifndef BUILTINFONT_H
#define BUILTINFONT_H

#include <aconf.h>

#include "gtypes.h"

struct BuiltinFont;
class BuiltinFontWidths;

//------------------------------------------------------------------------

struct BuiltinFont {
  const char *name;
  const char **defaultBaseEnc;
  short missingWidth;
  short ascent;
  short descent;
  short bbox[4];
  BuiltinFontWidths *widths;
};

//------------------------------------------------------------------------

struct BuiltinFontWidth {
  const char *name;
  Gushort width;
  BuiltinFontWidth *next;
};

class BuiltinFontWidths {
public:

  BuiltinFontWidths(BuiltinFontWidth *widths, int sizeA);
  ~BuiltinFontWidths();
  GBool getWidth(const char *name, Gushort *width);

private:

  int hash(const char *name);

  BuiltinFontWidth **tab;
  int size;
};

#endif
