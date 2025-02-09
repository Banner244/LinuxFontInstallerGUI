#include "FileChooser.h"

void FileChooser::openFileDialog(std::shared_ptr<MyWindow> myWindow, std::function<void()> addItem) {
	auto dialog = std::make_shared<Gtk::FileChooserDialog>(
            *myWindow, "Please select the Folder with the Fonts", 
            Gtk::FileChooser::Action::SELECT_FOLDER);

    dialog->add_button("Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("OK", Gtk::ResponseType::OK);

    dialog->signal_response().connect(
			[dialog, this, addItem](int response_id) {
                if (response_id == Gtk::ResponseType::OK) {
                    auto folder = dialog->get_file(); 
                    if (folder) {
                        std::cout << "Ausgewählter Ordner: " 
                                  << folder->get_basename() << std::endl;

						this->folderName = folder->get_basename();
						this->absolutePath = folder->get_path();
						fillFontList();
						addItem();
                    }
                } else {
                    std::cout << "Abgebrochen." << std::endl;
                }
                dialog->hide();  // closes the dialog window 
    });

    dialog->present();  // Zeigt den Dialog an
}

void FileChooser::fillFontList() {
    auto folder = Gio::File::create_for_path(absolutePath);
    
    try {
        Glib::RefPtr<Gio::FileEnumerator> enumerator = folder->enumerate_children(
            G_FILE_ATTRIBUTE_STANDARD_NAME, // Hier ist die Korrektur!
            Gio::FileQueryInfoFlags::NONE);

        Glib::RefPtr<Gio::FileInfo> fileInfo;
        while ((fileInfo = enumerator->next_file())) {
			std::string fileName = fileInfo->get_name();
			if(hasRightExtension(fileName)) {
				fonts.push_back(fileName);
				std::cout << "These: " << fileInfo->get_name() << std::endl;
			}
        }
    } catch (const Glib::Error& e) {
        std::cerr << "Could not read the directory: " << e.what() << std::endl;
    }
}

bool FileChooser::hasRightExtension(std::string &font) {
	std::string extension = ".ttf";
	return font.size() >= extension.size() && font.compare(font.size() - extension.size(), extension.size(), extension) == 0;
}
