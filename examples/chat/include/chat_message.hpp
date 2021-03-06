
#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <iostream>
#include <vector>

class chat_message
{
public:
  static int const kHeaderLength = sizeof(int);
  static int const kMaxBodyLength = 512;

  chat_message() {}

  const char* data() const {
    return this->data_.data();
  }

  std::vector<char>& data() {
    this->data_.resize(kMaxBodyLength);
    return this->data_;
  }

  std::size_t length() const {
    return this->data_.size();
  }

  const char* body() const {
    return this->data_.data() + kHeaderLength;
  }

  template <typename T>
  void assign(T src) {
    int new_length = src.size() + kHeaderLength;
    this->data_.resize(new_length);
    std::copy(src.begin(), src.end(), this->data_.begin()+kHeaderLength);
    this->set_header();
  }

  std::size_t body_length() const {
    return this->data_.size() - kHeaderLength;
  }

  void body_length(std::size_t new_length) {
    this->data_.resize(new_length);
  }

  bool check_header() {
    int* val = reinterpret_cast<int*>(this->data_.data());
    int body_length = *val;
    if (body_length > kMaxBodyLength) {
      return false;
    }
    return true;
  }

  void set_header() {
    std::vector<int>* idata = reinterpret_cast<std::vector<int>*>(&this->data_);
    int body_size = static_cast<int>(this->data_.size() - kHeaderLength);
    auto it = idata->begin();
    *it = body_size;
  }

private:
  std::vector<char> data_;
};

#endif // CHAT_MESSAGE_HPP
