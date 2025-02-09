#include "GuiHelper.h"

#include "../View/MyWindow.h"
// app has to be initialized
std::shared_ptr<Gtk::Application> GuiHelper::app = nullptr;


void GuiHelper::initialize() {
	if (!app) {
		std::cout << "init..." << std::endl;
		adw_init();  // Adwaita init 
		app = Gtk::Application::create("org.gtkmm.examples.base");
		app->hold();
	}
}

int GuiHelper::showMainWindow(){
	initialize(); 

	auto mainWindow = std::make_shared<MyWindow>();
	auto controller = std::make_unique<MyWindowController>(mainWindow);

	mainWindow->show();
	app->add_window(*mainWindow);

	return app->run();  // Starts the Event-Loop
}

void GuiHelper::showDifferentWindow() {
	if (!app) throw std::runtime_error("GuiHelper: App has not been initialized!");

	auto mainWindow = std::make_shared<TestWindow>();

	auto currentWindow = app->get_active_window();

	std::cout << "Is Current Window active: " << currentWindow->is_active() << std::endl;

	if(currentWindow) {
		std::cout << "currentWindow is initialized" << std::endl;
	}
	//currentWindow->maximize();
	//app->remove_window(*currentWindow);


	app->add_window(*mainWindow);
	mainWindow->show();
}
