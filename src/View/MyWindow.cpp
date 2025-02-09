#include "MyWindow.h"
#include "gtkmm/enums.h"

void MyWindow::addItemToList(const Glib::ustring& text) {
    // Erstelle elemente in einem Item
    auto label = Gtk::make_managed<Gtk::Label>(text);
	label->set_margin(3);
	label->set_hexpand(true); 
	label->set_halign(Gtk::Align::START);

    auto deleteButton = Gtk::make_managed<Gtk::Button>("Remove");
	deleteButton->set_halign(Gtk::Align::END);
	deleteButton->get_style_context()->add_class("custom-button");

	// Die Elemente gruppieren
	auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
	box->append(*label);  // Label hinzufügen
    box->append(*deleteButton);  // Button hinzufügen

	// Die gruppierung einem Zeilenelement zuweisen
	auto row = Gtk::make_managed<Gtk::ListBoxRow>();
	row->set_child(*box);
	//row->get_style_context()->add_class("listbox-item");
	row->set_name("listbox-item");

	// Das Zeilenelement der ListBox hinzufügen
	listBox.append(*row);

	// Button Lambda, um die Zeile löschen zu können.
	deleteButton->signal_clicked().connect([=](){
		this->myWindowListener->onItemDeleteClicked(row);
        // Entferne das aktuelle ListBox-Item
         listBox.remove(*row);
    });

}

void MyWindow::clearListBox() {
	listBox.remove_all();
}

void MyWindow::onButtonClicked() {
	this->myWindowListener->onButtonClicked();
}

void MyWindow::onInstallButtonClicked() {
	this->myWindowListener->onInstallButtonClicked();
}

MyWindow::MyWindow()
    :rootVBox(Gtk::Orientation::VERTICAL, 10),
	inputHBox(Gtk::Orientation::HORIZONTAL, 10),
      addButton("Add!"),
      installButton("Install Font/s")
	{
	set_default_size(200, 200);
    set_title("Font Installer");

	// Css initialisation
	initCssStyleFile();

	// HeaderBar erstellen
	initHeadBar();


	listBox.set_name("listbox");
//inputHBox.set_margin(3);
	rootVBox.set_margin(10);




    // Button in den Box-Container einfügen
    inputHBox.append(addButton);
    inputHBox.append(installButton);

	rootVBox.append(inputHBox);
	rootVBox.append(listBox);
    // Signal-Handler für den Button verbinden
    addButton.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::onButtonClicked));
    installButton.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::onInstallButtonClicked));

    // Haupt-Container setzen
    set_child(rootVBox);
}

void MyWindow::initHeadBar() {
    GtkWidget* header_bar = adw_header_bar_new();
    adw_header_bar_set_show_title(ADW_HEADER_BAR(header_bar), true);
    // Verwende GTK-C++-Wrapper und setze die Header-Bar
    auto header_wrapper = Glib::wrap(header_bar);
    set_titlebar(*header_wrapper);
}

void MyWindow::initCssStyleFile() {
	auto css_provider = Gtk::CssProvider::create();
	css_provider->load_from_path("resources/style.css");
	auto screen = Gdk::Display::get_default()->get_default();

	Gtk::StyleContext::add_provider_for_display(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
}
