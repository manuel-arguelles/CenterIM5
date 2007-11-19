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

#include "BuddyListNode.h"

#include <libpurple/blist.h>

BuddyListNode::BuddyListNode(Widget& parent, PurpleBlistNode *node)
: Label(parent, 0, 0, 64, 1, "")
, node(node)
, id(-1)
{
	log = Log::Instance();
	canfocus = true;
}

BuddyListNode::~BuddyListNode()
{
}

BuddyListNode* BuddyListNode::CreateNode(Widget& parent, PurpleBlistNode *node)
{
	BuddyListNode *bnode;

	if (PURPLE_BLIST_NODE_IS_BUDDY(node)) {
		bnode = new BuddyListBuddy(parent, node);
	} else if (PURPLE_BLIST_NODE_IS_CHAT(node)) {
		bnode = new BuddyListChat(parent, node);
	} else if (PURPLE_BLIST_NODE_IS_CONTACT(node)) {
		bnode = new BuddyListContact(parent, node);
	} else if (PURPLE_BLIST_NODE_IS_GROUP(node)) {
		bnode = new BuddyListGroup(parent, node);
	}

	return bnode;
}

void BuddyListNode::Draw(void)
{
	//TODO these nodes will use colors in the future
	//the colours should be added here
	Label::Draw();
}

void BuddyListNode::GiveFocus(void)
{
	focus = true;
	Update();
	Draw();
}

void BuddyListNode::TakeFocus(void)
{
	focus = false;
	Update();
	Draw();
}

BuddyListNode* BuddyListNode::GetParent(void)
{
	//TODO here I made the assumption that parents are *always* added before children
	//(groups before its contacts/buddies, contacts before its buddies)
	PurpleBlistNode *parent;

	parent = node->parent;

	if (!parent) return NULL; //TODO emit warning?

	if (!parent->ui_data) {
		log->Write(PURPLE_DEBUG_ERROR, "child added before its parent\n");
		//TODO how to solve this?
		return NULL;
	}

	return (BuddyListNode*)parent->ui_data;
}

BuddyListBuddy::BuddyListBuddy(Widget& parent, PurpleBlistNode *node)
: BuddyListNode(parent, node)
{
	buddy = (PurpleBuddy*)node;
	node->ui_data = this;
	Update();
}

void BuddyListBuddy::Draw(void)
{
	BuddyListNode::Draw();
}

void BuddyListBuddy::Update(void)
{
	//TODO this doesn't seem optimal
	//add a Width function to Label class and
	//clean this file up
	Glib::ustring text;
	text = purple_buddy_get_alias(buddy);
	Resize(width(text), 1);
	SetText(text);
}

BuddyListChat::BuddyListChat(Widget& parent, PurpleBlistNode *node)
: BuddyListNode(parent, node)
{
	chat = (PurpleChat*)node;
	node->ui_data = this;
	Update();
}

void BuddyListChat::Draw(void)
{
	BuddyListNode::Draw();
}

void BuddyListChat::Update(void)
{
	Glib::ustring text;
	text = purple_chat_get_name(chat);
	Resize(width(text), 1);
	SetText(text);
}

BuddyListContact::BuddyListContact(Widget& parent, PurpleBlistNode *node)
: BuddyListNode(parent, node)
{
	contact = (PurpleContact*)node;
	node->ui_data = this;
	Update();
}

void BuddyListContact::Draw(void)
{
	BuddyListNode::Draw();
}

void BuddyListContact::Update(void)
{
	PurpleBlistNode *bnode;
	Glib::ustring text;

	if (contact->alias) {
		text = contact->alias;
	} else {
		for (bnode = ((PurpleBlistNode*)contact)->child; bnode != NULL; bnode = bnode->next) {
			if (PURPLE_BLIST_NODE_IS_BUDDY(bnode))
				break;
		}

		if (!bnode) {
			//TODO error message or is this too common?
			text = "New Contact";
		} else {
			text = purple_buddy_get_alias((PurpleBuddy*)bnode);
		}
	}

	Resize(width(text), 1);
	SetText(text);
}

BuddyListGroup::BuddyListGroup(Widget& parent, PurpleBlistNode *node)
: BuddyListNode(parent, node)
{
	group = (PurpleGroup*)node;
	node->ui_data = this;
	Update();
}

void BuddyListGroup::Draw(void)
{
	BuddyListNode::Draw();
}

void BuddyListGroup::Update(void)
{
	Glib::ustring text;
	text = purple_group_get_name(group);
	Resize(width(text), 1);
	SetText(text);
}
