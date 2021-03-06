/*
 * Copyright (C) 2007 by Mark Pustjens <pustjens@dds.nl>
 * Copyright (C) 2010-2013 by CenterIM developers
 *
 * This file is part of CenterIM.
 *
 * CenterIM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * CenterIM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * @file
 * Label class implementation.
 *
 * @ingroup cppconsui
 */

#include "Label.h"

namespace CppConsUI
{

Label::Label(int w, int h, const char *text_)
: Widget(w, h), text(NULL)
{
  setText(text_);
}

Label::Label(const char *text_)
: Widget(AUTOSIZE, AUTOSIZE), text(NULL)
{
  setText(text_);
}

Label::~Label()
{
  g_free(text);
}

void Label::draw()
{
  proceedUpdateArea();

  if (!area)
    return;

  int attrs = getColorPair("label", "text");
  area->attron(attrs);

  int realw = area->getmaxx();
  int realh = area->getmaxy();

  // print text
  int y = 0;
  const char *start, *end;
  start = end = text;
  int p;
  while (*end) {
    if (*end == '\n') {
      if (y >= realh)
        break;

      p = area->mvaddstring(0, y, realw * (realh - y), start, end);
      y += (p / realw) + 1;
      start = end + 1;
    }
    end++;
  }
  if (y < realh)
    area->mvaddstring(0, y, realw * (realh - y), start, end);

  area->attroff(attrs);
}

void Label::setText(const char *new_text)
{
  g_free(text);

  text = g_strdup(new_text ? new_text : "");

  // update wish height
  int h = 1;
  for (const char *cur = text; *cur; cur++)
    if (*cur == '\n')
      h++;
  setWishHeight(h);

  redraw();
}

} // namespace CppConsUI

/* vim: set tabstop=2 shiftwidth=2 textwidth=78 expandtab : */
