#include <iostream>
#include <string>
#include <iomanip>

#include <sockpp/inet_address.h>

#include "../include/file_sender.hpp"

int main(int argc, char** argv)
{
    if (argc < 4) {
        std::cerr << "[!!!] Error: missing arguments!\n";
        std::cout << "Usage: " << argv[0] << " <dest addr> <dest port> <filename>\n";
        std::exit(1);
    }

    if (!boost::filesystem::exists(argv[3])) {
        std::cerr << "[!!!] Error: could not find file: " << std::quoted(argv[3]) << "\n";
        std::exit(2);
    }

    const sockpp::inet_address destination_endpoint {argv[1], static_cast<uint16_t>(std::stoi(argv[2]))};
    sockpp::tcp_connector tcp_connector {};

    if (!tcp_connector.connect(destination_endpoint)) {
        std::cerr << "[!!!] Error: " << tcp_connector.last_error_str() << "\n";
        std::exit(3);
    }

    const boost::filesystem::path file_path {argv[3]};

    if (!file_sender::check_file_type(file_path)) {
        std::cerr << "[!!!] Error: unsupported file type: " << std::quoted(file_path.string()) << "\n";
        file_sender::send_error_code_and_close_connection(tcp_connector, 4);
        std::exit(4);
    }

    std::cout << "[***] Connected with: " << destination_endpoint << "\n";

    std::FILE* file = std::fopen(file_path.c_str(), "rb");

    if (file == NULL) {
        std::cerr << "[!!!] Error: could not open file: " << std::quoted(file_path.string()) << "\n";
        file_sender::send_error_code_and_close_connection(tcp_connector, 5);
        std::exit(5);
    }

    file_sender::send_error_code(tcp_connector, 0);

    file_sender::send_filename(tcp_connector, file_path.filename().string());

    std::cout << "[***] Reading file: " << std::quoted(file_path.filename().string()) << "...\n";
    const std::string file_data {file_sender::read_file(file)};

    std::cout << "[***] Sending bytes to --> " << destination_endpoint << "\n";
    const ssize_t bytes_sent {file_sender::send_file_data(tcp_connector, file_data)};

    std::cout << "[***] Bytes sent: " << bytes_sent << " (" << bytes_sent / 1024 << "." << bytes_sent % 1000 << " Kib)\n";

    std::fclose(file);
    tcp_connector.close();

    return 0;
}
