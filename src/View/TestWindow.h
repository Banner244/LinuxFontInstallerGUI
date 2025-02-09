#pragma once

#include <cstdlib>
#include <gtkmm.h>
#include <adwaita.h>
#include <iostream>
#include "../Controller/IMyWindow.h"
#include "gtkmm/listbox.h"

class TestWindow : public Gtk::Window {
	private:
	public:
		TestWindow(): addButton("Button"){
			set_child(addButton);

			std::cout << "TestWindow" << std::endl;
		}


	protected:
		Gtk::Button addButton;
};
