
#include "ServerController.h"
#include "InvalidConnectionState.h"

#include <iostream>
#include <syncstream>
#include <algorithm>

void ServerController::start() {
	isRunning = true; // Set loop flag

	// Create accept thread and pass it loop to begin accepting clients
	acceptThread = std::thread(&ServerController::acceptLoop, this);
}

void ServerController::stop() {
	isRunning = false;

	serverSocket.close();

	if (acceptThread.joinable()) acceptThread.join();

	for (auto& client : clientThreads)
		if (client.joinable()) client.join();
}

void ServerController::acceptLoop() {
	while (isRunning) {
		try {
			// Block until a client connects
			ClientSocket client = serverSocket.acceptConnection();

			std::osyncstream(std::cout) << "New client connected" << std::endl;

			// Pass client into its own thread
			clientThreads.emplace_back([this, client = std::move(client)]() mutable {
				clientHandler(client);
			});
		}
		catch (InvalidConnectionStateException& e) {
			std::cerr << "Exception caught during accept loop:" << e.what() << std::endl;
		}
		
	}
}

std::thread& ServerController::getAcceptThread() {
	return acceptThread;
}