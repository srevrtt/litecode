#include <iostream>
#include <string>
#include <fstream>

#include "include/fs.hpp"

// Reads a shader source file and displays it as a string
std::string Filesystem::readShaderFile(std::string filepath)
{
  std::string line, contents;
  std::ifstream file(filepath);

  // error handling
  if (file.is_open())
  {
    // read the file
    while (std::getline(file, line))
    {
      contents += line + '\n';
    }
  }
  else
  {
    std::cout << "Error: Failed to read shader source file \"" << filepath << "\".\n";
    exit(1);
  }

  return contents;
}
