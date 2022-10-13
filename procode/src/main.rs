#[cfg(unix)]
extern crate gtk;
extern crate x11;

extern crate image;
extern crate gl;
extern crate glam;
extern crate ttf_parser;

mod platform;
mod gui;

fn main() {
  let window = gui::Window::create();
  window.run();
}