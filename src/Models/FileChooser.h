#pragma once

#include <iostream>
#include <vector>
#include "gtkmm/filechooser.h"
#include "../View/MyWindow.h"

class FileChooser {
	public:
		void openFileDialog(std::shared_ptr<MyWindow> myWindow, std::function<void()> addItem);
		
		std::string folderName;
		std::string absolutePath;
		std::vector<std::string> fonts;
	private:
		void fillFontList();
		bool hasRightExtension(std::string &font);

};
