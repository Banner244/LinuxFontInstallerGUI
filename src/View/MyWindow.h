#pragma once

#include <cstdlib>
#include <gtkmm.h>
#include <adwaita.h>

#include "../Controller/IMyWindow.h"
#include "gtkmm/listbox.h"

class MyWindow : public Gtk::Window {
	private:
		IMyWindow* myWindowListener;
		void initHeadBar();
		void initCssStyleFile();
	public:
		MyWindow();
		void addItemToList(const Glib::ustring& text);

		void setMyWindowListener(IMyWindow* myWindowListener) {
			this->myWindowListener = myWindowListener;	
		}


	protected:
		void onButtonClicked();
		void onInstallButtonClicked();
		Gtk::Button addButton;
		Gtk::Button installButton;
		Gtk::Box rootVBox;
		Gtk::Box inputHBox;
		Gtk::ListBox listBox;
};


