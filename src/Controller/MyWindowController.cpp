#include "MyWindowController.h"
#include <iostream>
#include "../App/GuiHelper.h"

MyWindowController::MyWindowController(std::shared_ptr<MyWindow> myWindow) { 
	this->myWindow = myWindow;
	this->myWindow->setMyWindowListener(this);
}

void MyWindowController::onButtonClicked() {
	std::cout << "Clicked on Button with Interface" << std::endl;
	
	auto refreshItemList( [this](){
		for(std::string &font : filechooser.fonts) {
			myWindow->addItemToList(font);
		}
		std::cout << "Added!" << "\n";
	});

	filechooser.openFileDialog(myWindow, refreshItemList);
}

void MyWindowController::onInstallButtonClicked() {
	std::cout << "Got: " << filechooser.folderName << ", and: " << filechooser.absolutePath << "\n";

	for(std::string &font : filechooser.fonts) {
		std::cout << font << "\n";
	}
	std::string exeCoommandStr = ("mkdir -p ~/.fonts/" + filechooser.folderName);
	std::cout << "exe: " << exeCoommandStr+"\n";
	std::string output = execCommand(exeCoommandStr.c_str()); // Oder "dir" für Windows
    std::cout << "Befehlsausgabe:\n" << output;

	for(std::string &font : filechooser.fonts){
		std::string execStr = "cp " + filechooser.absolutePath + "/" + font + " ~/.fonts/"+filechooser.folderName+"/";
		output = execCommand(execStr.c_str());
	}
	output = execCommand("fc-cache -fv");
}

void MyWindowController::onItemDeleteClicked(Gtk::ListBoxRow *row) {
	std::cout << "Clicked on Delete! " << row->get_index() << std::endl;
	filechooser.fonts.erase(filechooser.fonts.begin() + row->get_index());
	for(std::string &font : filechooser.fonts) {
		std::cout << font << "\n";
	}
}

std::string MyWindowController::execCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    
    // Öffnet ein Pipe-Stream zum Lesen der Ausgabe
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() fehlgeschlagen!");
    }

    // Liest die Ausgabe des Befehls
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}
