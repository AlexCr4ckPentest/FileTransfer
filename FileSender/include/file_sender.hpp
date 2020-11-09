#include <sockpp/tcp_connector.h>

#ifndef __FILE_SENDER_HPP__
#define __FILE_SENDER_HPP__

namespace file_sender
{
    void send_error_code(sockpp::tcp_connector& sock, const uint8_t code) noexcept;
    void send_error_code_and_close_connection(sockpp::tcp_connector& sock, const uint8_t code) noexcept;
    std::string read_file(std::FILE* file) noexcept;
    ssize_t send_filename(sockpp::tcp_connector& sock, const std::string& filename) noexcept;
    ssize_t send_file_data(sockpp::tcp_connector& sock, const std::string& file_data) noexcept;
} // namespace file_sender

#endif // __FILE_SENDER_HPP__
