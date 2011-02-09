/*
 * Copyright (C) 2007 by Mark Pustjens <pustjens@dds.nl>
 * Copyright (C) 2010 by CenterIM developers
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

/**
 * @file
 * InputDialog class implementation.
 *
 * @ingroup cppconsui
 */

#include "InputDialog.h"

#include "gettext.h"

InputDialog::InputDialog(const gchar *title, const gchar *defaultvalue)
: AbstractDialog(title)
{
  AddButton(_(OK_BUTTON_TEXT), InputDialog::RESPONSE_OK);

  entry = new TextEntry(AUTOSIZE, AUTOSIZE, defaultvalue);
  layout->InsertWidget(0, *entry);

  entry->GrabFocus();
}

const gchar *InputDialog::GetText() const
{
  return entry->GetText();
}

void InputDialog::EmitResponse(ResponseType response)
{
  signal_response(*this, response);
}
