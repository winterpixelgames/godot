/*************************************************************************/
/*  editor_log.cpp                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "editor_log.h"

#include "core/os/keyboard.h"
#include "core/version.h"
#include "editor_node.h"
#include "editor_scale.h"
#include "scene/gui/center_container.h"
#include "scene/resources/dynamic_font.h"

void EditorLog::_error_handler(void *p_self, const char *p_func, const char *p_file, int p_line, const char *p_error, const char *p_errorexp, ErrorHandlerType p_type) {
	EditorLog *self = (EditorLog *)p_self;
	if (self->current != Thread::get_caller_id()) {
		return;
	}

	String err_str;
	if (p_errorexp && p_errorexp[0]) {
		err_str = p_errorexp;
	} else {
		err_str = String(p_file) + ":" + itos(p_line) + " - " + String(p_error);
	}

	if (p_type == ERR_HANDLER_WARNING) {
		self->add_message(err_str, MSG_TYPE_WARNING);
	} else {
		self->add_message(err_str, MSG_TYPE_ERROR);
	}
}

void EditorLog::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE) {
		//button->set_icon(get_icon("Console","EditorIcons"));
		log->add_theme_font_override("normal_font", get_theme_font("output_source", "EditorFonts"));
		log->add_theme_color_override("selection_color", get_theme_color("accent_color", "Editor") * Color(1, 1, 1, 0.4));
		log->add_theme_font_override("bold_font", get_theme_font("bold", "EditorFonts"));

		type_filter_map.find(MSG_TYPE_STD)->get()->toggle_button->set_icon(get_theme_icon("Popup", "EditorIcons"));
		type_filter_map.find(MSG_TYPE_ERROR)->get()->toggle_button->set_icon(get_theme_icon("StatusError", "EditorIcons"));
		type_filter_map.find(MSG_TYPE_WARNING)->get()->toggle_button->set_icon(get_theme_icon("StatusWarning", "EditorIcons"));
		type_filter_map.find(MSG_TYPE_EDITOR)->get()->toggle_button->set_icon(get_theme_icon("Edit", "EditorIcons"));

		clear_button->set_icon(get_theme_icon("Clear", "EditorIcons"));
		copy_button->set_icon(get_theme_icon("ActionCopy", "EditorIcons"));
		collapse_button->set_icon(get_theme_icon("CombineLines", "EditorIcons"));
		show_search_button->set_icon(get_theme_icon("Search", "EditorIcons"));

	} else if (p_what == NOTIFICATION_THEME_CHANGED) {
		Ref<DynamicFont> df_output_code = get_theme_font("output_source", "EditorFonts");
		if (df_output_code.is_valid()) {
			if (log != nullptr) {
				log->add_theme_font_override("normal_font", get_theme_font("output_source", "EditorFonts"));
				log->add_theme_color_override("selection_color", get_theme_color("accent_color", "Editor") * Color(1, 1, 1, 0.4));
			}
		}
	}
}

void EditorLog::_set_collapse(bool p_collapse) {
	collapse = p_collapse;
	_rebuild_log();
}

void EditorLog::_clear_request() {
	log->clear();
	messages.clear();
	_reset_message_counts();
	tool_button->set_icon(Ref<Texture2D>());
}

void EditorLog::_copy_request() {
	String text = log->get_selected_text();

	if (text == "") {
		text = log->get_text();
	}

	if (text != "") {
		DisplayServer::get_singleton()->clipboard_set(text);
	}
}

void EditorLog::clear() {
	_clear_request();
}

void EditorLog::_process_message(const String &p_msg, MessageType p_type) {
    if (messages.size() > 0 && messages[messages.size() - 1].text == p_msg) {
        // If previous message is the same as the new one, increase previous count rather than adding another
        // instance to the messages list.
        LogMessage &previous = messages.write[messages.size() - 1];
        previous.count++;

        _add_log_line(previous, collapse);
    } else {
        // Different message to the previous one received.
        LogMessage message(p_msg, p_type);
        _add_log_line(message);
        messages.push_back(message);
    }

    type_filter_map[p_type]->set_message_count(type_filter_map[p_type]->get_message_count() + 1);
}

void EditorLog::add_message(const String &p_msg, MessageType p_type) {
    // Parse out newlines as separate messages
    int msg_start = 0;
    int msg_length = 0;
    for(int i = 0; i < p_msg.size(); i++) {
        if(p_msg[i] == '\n') {
            if(msg_length > 0) {
                _process_message(p_msg.substr(msg_start, msg_length), p_type);
                msg_length = 0;
                msg_start = i+1;
                continue;
            }
        }
        if(i == p_msg.size() -1) {
            _process_message(p_msg.substr(msg_start, msg_length), p_type);
        }
        msg_length++;
    }
}

void EditorLog::set_tool_button(Button *p_tool_button) {
	tool_button = p_tool_button;
}

void EditorLog::_undo_redo_cbk(void *p_self, const String &p_name) {
	EditorLog *self = (EditorLog *)p_self;
	self->add_message(p_name, EditorLog::MSG_TYPE_EDITOR);
}

void EditorLog::_rebuild_log() {
	log->clear();

	for (int msg_idx = 0; msg_idx < messages.size(); msg_idx++) {
		LogMessage msg = messages[msg_idx];

		if (collapse) {
			// If collapsing, only log one instance of the message.
			_add_log_line(msg);
		} else {
			// If not collapsing, log each instance on a line.
			for (int i = 0; i < msg.count; i++) {
				_add_log_line(msg);
			}
		}
	}
}

void EditorLog::_add_log_line(LogMessage &p_message, bool p_replace_previous) {
	// Only add the message to the log if it passes the filters.
	bool filter_active = type_filter_map[p_message.type]->active;
	String search_text = search_box->get_text();
	bool search_match = search_text == String() || p_message.text.findn(search_text) > -1;

	if (!filter_active || !search_match) {
		return;
	}

	if (p_replace_previous) {
		// Remove last line if replacing, as it will be replace by the next added line.
		log->remove_line(log->get_line_count() - 1);
		log->increment_line_count();
	} else {
		log->add_newline();
	}

	switch (p_message.type) {
		case MSG_TYPE_STD: {
		} break;
		case MSG_TYPE_ERROR: {
			log->push_color(get_theme_color("error_color", "Editor"));
			Ref<Texture2D> icon = get_theme_icon("Error", "EditorIcons");
			log->add_image(icon);
			log->add_text(" ");
			tool_button->set_icon(icon);
		} break;
		case MSG_TYPE_WARNING: {
			log->push_color(get_theme_color("warning_color", "Editor"));
			Ref<Texture2D> icon = get_theme_icon("Warning", "EditorIcons");
			log->add_image(icon);
			log->add_text(" ");
			tool_button->set_icon(icon);
		} break;
		case MSG_TYPE_EDITOR: {
			// Distinguish editor messages from messages printed by the project
			log->push_color(get_theme_color("font_color", "Editor") * Color(1, 1, 1, 0.6));
		} break;
	}

	// If collapsing, add the count of this message in bold at the start of the line.
	if (collapse && p_message.count > 1) {
		log->push_bold();
		log->add_text(vformat("(%s) ", itos(p_message.count)));
		log->pop();
	}

	log->add_text(p_message.text);

	// Need to use pop() to exit out of the RichTextLabels current "push" stack.
	// We only "push" in the above swicth when message type != STD, so only pop when that is the case.
	if (p_message.type != MSG_TYPE_STD) {
		log->pop();
	}
}

void EditorLog::_set_filter_active(bool p_active, int p_message_type) {
	type_filter_map[p_message_type]->active = p_active;
	_rebuild_log();
}

void EditorLog::_set_search_visible(bool p_visible) {
	search_box->set_visible(p_visible);
	if (p_visible) {
		search_box->grab_focus();
	}
}

void EditorLog::_search_changed(const String &p_text) {
	_rebuild_log();
}

void EditorLog::_reset_message_counts() {
	for (Map<int, LogFilter *>::Element *E = type_filter_map.front(); E; E = E->next()) {
		E->value()->set_message_count(0);
	}
}

void EditorLog::_bind_methods() {
	ADD_SIGNAL(MethodInfo("clear_request"));
	ADD_SIGNAL(MethodInfo("copy_request"));
}

EditorLog::EditorLog() {
	HBoxContainer *hb = this;

	VBoxContainer *vb_left = memnew(VBoxContainer);
	vb_left->set_custom_minimum_size(Size2(0, 180) * EDSCALE);
	vb_left->set_v_size_flags(SIZE_EXPAND_FILL);
	vb_left->set_h_size_flags(SIZE_EXPAND_FILL);
	hb->add_child(vb_left);

	// Log - Rich Text Label.
	log = memnew(RichTextLabel);
	log->set_scroll_follow(true);
	log->set_selection_enabled(true);
	log->set_focus_mode(FOCUS_CLICK);
	log->set_v_size_flags(SIZE_EXPAND_FILL);
	log->set_h_size_flags(SIZE_EXPAND_FILL);
	vb_left->add_child(log);

	// Search box
	search_box = memnew(LineEdit);
	search_box->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	search_box->set_placeholder(TTR("Filter messages"));
	search_box->set_right_icon(get_theme_icon("Search", "EditorIcons"));
	search_box->set_clear_button_enabled(true);
	search_box->set_visible(false);
	search_box->connect("text_changed", callable_mp(this, &EditorLog::_search_changed));
	vb_left->add_child(search_box);

	VBoxContainer *vb_right = memnew(VBoxContainer);
	hb->add_child(vb_right);

	// Tools grid
	HBoxContainer *hb_tools = memnew(HBoxContainer);
	hb_tools->set_h_size_flags(SIZE_SHRINK_CENTER);
	vb_right->add_child(hb_tools);

	// Clear.
	clear_button = memnew(Button);
	clear_button->set_flat(true);
	clear_button->set_shortcut(ED_SHORTCUT("editor/clear_output", TTR("Clear Output"), KEY_MASK_CMD | KEY_MASK_SHIFT | KEY_K));
	clear_button->connect("pressed", callable_mp(this, &EditorLog::_clear_request));
	hb_tools->add_child(clear_button);

	// Copy.
	copy_button = memnew(Button);
	copy_button->set_flat(true);
	copy_button->set_shortcut(ED_SHORTCUT("editor/copy_output", TTR("Copy Selection"), KEY_MASK_CMD | KEY_C));
	copy_button->connect("pressed", callable_mp(this, &EditorLog::_copy_request));
	hb_tools->add_child(copy_button);

	// A second hbox to make a 2x2 grid of buttons.
	HBoxContainer *hb_tools2 = memnew(HBoxContainer);
	hb_tools2->set_h_size_flags(SIZE_SHRINK_CENTER);
	vb_right->add_child(hb_tools2);

	// Collapse.
	collapse_button = memnew(Button);
	collapse_button->set_flat(true);
	collapse_button->set_tooltip(TTR("Collapse duplicate messages into one log entry. Shows number of occurences."));
	collapse_button->set_toggle_mode(true);
	collapse_button->set_pressed(true);
	collapse_button->connect("toggled", callable_mp(this, &EditorLog::_set_collapse));
	hb_tools2->add_child(collapse_button);

	// Show Search.
	show_search_button = memnew(Button);
	show_search_button->set_flat(true);
	show_search_button->set_toggle_mode(true);
	show_search_button->set_pressed(false);
	show_search_button->set_shortcut(ED_SHORTCUT("editor/open_search", TTR("Open the search box."), KEY_MASK_CMD | KEY_F));
	show_search_button->connect("toggled", callable_mp(this, &EditorLog::_set_search_visible));
	hb_tools2->add_child(show_search_button);

	// Message Type Filters.
	vb_right->add_child(memnew(HSeparator));

	LogFilter *std_filter = memnew(LogFilter(MSG_TYPE_STD));
	std_filter->initialise_button("Toggle visibility of standard output messages.", callable_mp(this, &EditorLog::_set_filter_active));
	vb_right->add_child(std_filter->toggle_button);
	type_filter_map.insert(MSG_TYPE_STD, std_filter);

	LogFilter *error_filter = memnew(LogFilter(MSG_TYPE_ERROR));
	error_filter->initialise_button("Toggle visibility of errors.", callable_mp(this, &EditorLog::_set_filter_active));
	vb_right->add_child(error_filter->toggle_button);
	type_filter_map.insert(MSG_TYPE_ERROR, error_filter);

	LogFilter *warning_filter = memnew(LogFilter(MSG_TYPE_WARNING));
	warning_filter->initialise_button("Toggle visibility of warnings.", callable_mp(this, &EditorLog::_set_filter_active));
	vb_right->add_child(warning_filter->toggle_button);
	type_filter_map.insert(MSG_TYPE_WARNING, warning_filter);

	LogFilter *editor_filter = memnew(LogFilter(MSG_TYPE_EDITOR));
	editor_filter->initialise_button("Toggle visibility of editor messages.", callable_mp(this, &EditorLog::_set_filter_active));
	vb_right->add_child(editor_filter->toggle_button);
	type_filter_map.insert(MSG_TYPE_EDITOR, editor_filter);

	add_message(VERSION_FULL_NAME " (c) 2007-2020 Juan Linietsky, Ariel Manzur & Godot Contributors.");

	eh.errfunc = _error_handler;
	eh.userdata = this;
	add_error_handler(&eh);

	current = Thread::get_caller_id();

	EditorNode::get_undo_redo()->set_commit_notify_callback(_undo_redo_cbk, this);
}

void EditorLog::deinit() {
	remove_error_handler(&eh);
}

EditorLog::~EditorLog() {
}
