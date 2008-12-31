/*
 * Copyright (C) 2007 by Mark Pustjens <pustjens@dds.nl>
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
 * */

#ifndef __ABSTRACTLISTBOX_H__
#define __ABSTRACTLISTBOX_H__

#include "ScrollPane.h"

class AbstractListBox
: public ScrollPane
{
	public:
		AbstractListBox(Widget& parent, int x, int y, int w, int h);
		virtual ~AbstractListBox();

		virtual void AddItem(const char *text, sigc::slot<void> function);
		virtual void AddSeparator() =0;

		virtual void AddWidget(Widget *widget);
		virtual void RemoveWidget(Widget *widget); //TODO might not be needed?

		virtual void Clear(void);

	protected:
		int maxheight, maxwidth;

	private:
		AbstractListBox(void);
		AbstractListBox(const AbstractListBox&);

		AbstractListBox& operator=(const AbstractListBox&);
};

#endif /* __ABSTRACTLISTBOX_H__ */
