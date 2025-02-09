#pragma once

#include <memory>
#include <gtkmm.h>
#include "IMyWindow.h"
#include "../View/MyWindow.h"
#include "../Models/FileChooser.h"

class MyWindowController : public IMyWindow {
	public:
		explicit MyWindowController(std::shared_ptr<MyWindow> myWindow);

		// Interface Methods
		void onButtonClicked() override;
		void onInstallButtonClicked() override;
		void onItemDeleteClicked(Gtk::ListBoxRow *row) override;

	private:
		std::shared_ptr<MyWindow> myWindow;
		FileChooser filechooser;
		std::string execCommand(const char* cmd); 

		void clearItems();
		void openInfoDialog(std::string info);
};
