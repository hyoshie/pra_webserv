#ifndef ASOCKET_HPP
#define ASOCKET_HPP

class ASocket {
 public:
  ASocket(int fd);
  virtual ~ASocket();
  virtual void notifyFdEvent() = 0;
  int getFd() const;

 protected:
  int fd_;

 private:
  ASocket(const ASocket& other);
  ASocket& operator=(const ASocket& other);
};

#endif /* ASOCKET_HPP */
