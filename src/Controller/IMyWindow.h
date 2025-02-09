#pragma once

#include "gtkmm/listboxrow.h"
class IMyWindow {
	public:
		virtual void onButtonClicked() = 0;
		virtual void onInstallButtonClicked() = 0;
		virtual void onItemDeleteClicked(Gtk::ListBoxRow *row) = 0;
};
