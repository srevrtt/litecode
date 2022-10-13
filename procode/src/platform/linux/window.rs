use gtk::prelude::*;

// A struct representing a GTK window
#[derive(Debug, PartialEq, Clone)]
pub struct LinuxWindow {
  app: gtk::Application
}

impl LinuxWindow {
  // GTK on window create
  fn on_create(app: &gtk::Application) {
    let window = gtk::ApplicationWindow::new(app);

    window.set_default_size(1280, 720);
    window.set_title("Procode");
    window.present();
  }

  // Creates a new GTK window
  // with the specified width, height, and title
  pub fn new() -> Self {
    let app = gtk::Application::builder()
      .application_id("com.srevrtt.procode")
      .build();

    Self {
      app
    }
  }

  // Runs the Linux window
  pub fn run(&self) {
    self.app.connect_activate(Self::on_create);
    self.app.run();
  }
}
