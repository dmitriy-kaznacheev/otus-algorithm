#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <regex>
#include <sstream>

namespace fs = std::filesystem;

std::vector<std::pair<std::string, std::string>>
find_test_files(const std::string &task_dir) {
  std::vector<std::pair<std::string, std::string>> result;
  std::map<int, std::string> inputs, outputs;

  std::regex pattern(R"(test\.(\d+)\.(in|out))");

  for (const auto &entry : fs::directory_iterator(task_dir)) {
    std::string name = entry.path().filename().string();
    std::smatch match;

    if (std::regex_search(name, match, pattern)) {
      int num = std::stoi(match[1]);
      if (match[2] == "in")
        inputs[num] = entry.path().string();
      else
        outputs[num] = entry.path().string();
    }
  }

  for (auto &[num, in] : inputs)
    if (outputs.count(num))
      result.push_back({in, outputs[num]});

  return result;
}

std::string read_file(const std::string &path) {
  std::ifstream f(path);
  std::stringstream ss;
  ss << f.rdbuf();
  return std::regex_replace(ss.str(), std::regex("\\r|\\n$"), "");
}

#endif