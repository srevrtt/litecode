#[cfg(unix)]
use crate::platform::linux::LinuxWindow;

// A struct representing a cross platform window object
pub struct Window {
  #[cfg(unix)]
  window: LinuxWindow
}

impl Window {
  // Creates a new cross platform window
  pub fn create() -> Self {
    let window = LinuxWindow::new();
    Self { window }
  }

  // Runs the created window
  pub fn run(&self) {
    self.window.run();
  }
}
