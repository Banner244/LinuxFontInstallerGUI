#pragma once

#include <iostream>
#include <vector>
#include "gtkmm/filechooser.h"
#include "../View/MyWindow.h"

class FileChooser {
	public:
		std::string folderName;
		std::string absolutePath;
		std::vector<std::string> fonts;

		void openFileDialog(std::shared_ptr<MyWindow> myWindow, std::function<void()> addItem);
		void reset();

	private:
		void fillFontList();
		bool hasRightExtension(std::string &font);

};
