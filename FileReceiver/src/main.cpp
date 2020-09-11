#include <iostream>
#include <iomanip>

#include <sockpp/inet_address.h>

#include "../include/file_receiver.hpp"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "[!!!] Error: missing arguments!\n";
        std::cout << "Usage: " << argv[0] << " <port> <output folder>\n";
        std::exit(1);
    }

    std::string output_folder {argv[2]};

    if (!boost::filesystem::exists(output_folder)) {
        std::cerr << "[!!!] Error: could not find directory: " << std::quoted(output_folder) << "\n";
        std::exit(2);
    }

    if (boost::filesystem::status(output_folder).type()
        != boost::filesystem::file_type::directory_file)
    {
        std::cerr << "[!!!] Error: this is not a directory: " << std::quoted(output_folder) << "\n";
        std::exit(3);
    }

    sockpp::tcp_acceptor tcp_acceptor {static_cast<uint16_t>(std::stoi(argv[1])), 1};

    if (!tcp_acceptor || !tcp_acceptor.listen(1)) {
        std::cerr << "[!!!] Error: " << tcp_acceptor.last_error_str() << "\n";
        std::exit(4);
    }

    std::cout << "[***] Waiting for connection...\n";
    sockpp::tcp_socket client {tcp_acceptor.accept()};

    if (!client) {
        std::cerr << "[!!!] Error: " << client.last_error_str() << "\n";
        std::exit(5);
    }

    std::cout << "[***] Client connected: " << client.peer_address().to_string() << "\n";

    uint8_t error_code {};
    client.read_n(&error_code, sizeof(error_code));

    if (error_code != 0) {
        std::cerr << "[!!!] Error: some error has occured on " << client.peer_address().to_string()
                  << ", error code: " << static_cast<uint32_t>(error_code) << "\n";
        std::exit(6);
    }

    if ((*(output_folder.cend() - 1)) != '/') {
        output_folder += '/';
    }

    const std::string filename {file_receiver::receive_filename(client)};

    std::cout << "[***] Receiving bytes from <-- " << client.peer_address().to_string() << "\n";
    const auto [file_data, file_data_size] {file_receiver::receive_file_data(client)};

    std::cout << "[***] Bytes received: " << file_data_size << " (" << file_data_size / 1024 << "." << file_data_size % 1000 << " Kib)\n";

    const std::string final_filename {output_folder + filename};

    file_receiver::write_data_to_file(final_filename, file_data, file_data_size);
    std::cout << "[***] File saved as: " << std::quoted(final_filename) << "\n";

    delete[] file_data;

    client.close();
    tcp_acceptor.close();

    return 0;
}
