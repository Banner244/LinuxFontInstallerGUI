#pragma once

#include <gtkmm.h>
#include <adwaita.h>
#include <iostream>
#include <memory>

#include "../View/TestWindow.h"
#include "../View/MyWindow.h"
#include "../Controller/MyWindowController.h"
#include "gtkmm/application.h"

class GuiHelper{
	private:
		static std::shared_ptr<Gtk::Application> app; // Zentrale Gtk::Application-Instanz
													  
		// Initialisiert die Gtk::Application
		static void initialize(); 

	public:
		// Zeigt das Hauptfenster
		static int showMainWindow();

		// Beispiel für neues Fenster
		static void showDifferentWindow();

};








/*	private:
	public:
		static int startMainWindow(){
			// Adwaita init
			adw_init();
			auto app = Gtk::Application::create("org.gtkmm.examples.base");
			app->hold();

			auto mainWindow = std::make_shared<MyWindow>();
			auto controller = std::make_unique<MyWindowController>(mainWindow);

			mainWindow->show();
			app->add_window(*mainWindow);
			return app->run();
		}*/
