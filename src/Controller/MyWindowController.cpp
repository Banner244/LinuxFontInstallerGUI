#include "MyWindowController.h"
#include <iostream>

MyWindowController::MyWindowController(std::shared_ptr<MyWindow> myWindow) { 
	this->myWindow = myWindow;
	this->myWindow->setMyWindowListener(this);
}

void MyWindowController::onButtonClicked() {
	auto refreshItemList( [this](){
		for(std::string &font : filechooser.fonts) {
			myWindow->addItemToList(font);
		}
		std::cout << "Added!" << "\n";
	});

	filechooser.openFileDialog(myWindow, refreshItemList);
}

void MyWindowController::onInstallButtonClicked() {
	if(filechooser.fonts.empty()) {
		openInfoDialog("No Fonts added");
		return;
	}

	std::string exeCoommandStr = ("mkdir -p ~/.fonts/" + filechooser.folderName);
	std::string output = execCommand(exeCoommandStr.c_str()); 

	for(std::string &font : filechooser.fonts){
		std::string execStr = "cp " + filechooser.absolutePath + "/" + font + " ~/.fonts/"+filechooser.folderName+"/";
		output = execCommand(execStr.c_str());
	}
	output = execCommand("fc-cache -fv");

	clearItems();	

	openInfoDialog("Success!\n\nFonts are stored in ~/.fonts/");
}

void MyWindowController::onItemDeleteClicked(Gtk::ListBoxRow *row) {
	std::cout << "Clicked on Delete! " << row->get_index() << std::endl;
	filechooser.fonts.erase(filechooser.fonts.begin() + row->get_index());
}

void MyWindowController::clearItems() {
	myWindow->clearListBox();
	filechooser.reset();
}

std::string MyWindowController::execCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    
    // opens a pipe-stream to read to output of the cmd
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() fehlgeschlagen!");
    }

    // reads the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}

void MyWindowController::openInfoDialog(std::string info){
	auto dialog = std::make_shared<Gtk::MessageDialog>(*myWindow, info,
                                                       false, Gtk::MessageType::INFO, Gtk::ButtonsType::OK);
    
    dialog->signal_response().connect([dialog](int response) {
		// okay click action here
        dialog->hide();
    });

    dialog->present(); 
}
