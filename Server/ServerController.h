#pragma once

#include "ServerSocket.h"

#include <atomic>
#include <memory>

// Alias for a function that will be passed to all incoming client threads
using ClientHandler = std::function<void(ClientSocket&)>;

class ServerController {
private:
	ServerSocket& serverSocket;
	ClientHandler& clientHandler;
	std::atomic<bool> isRunning = false; // Used to moderate the accept loop within the acceptThread
	std::thread acceptThread; // Seperate thread used to listen and accept new clients
	std::vector<std::thread> clientThreads; // A collection of all the active client connections/threads

	void acceptLoop(); // Method to be run within the acceptThread
public:
	ServerController(ServerSocket& socket, ClientHandler& handler) : serverSocket(socket), clientHandler(handler) {}
	~ServerController() { stop(); };

	/**
	 * @brief Starts the server controller.
	 *
	 * Initializes the server loop and spawns a dedicated thread to accept incoming client connections.
	 *
	 * This function is non-blocking; the accept loop runs in a separate thread.
	 */
	void start();
	/**
	 * @brief Stops the server controller.
	 *
	 * Signals the server to stop accepting new connections, closes the server
	 * socket, and joins all running threads (accept thread and client threads).
	 *
	 * This function blocks until all threads have finished execution.
	*/
	void stop();


	/**
	 * @brief Main loop for accepting incoming client connections.
	 *
	 * Continuously listens for new client connections while the server is running.
	 * For each accepted connection:
	 * - Logs the connection event
	 * - Spawns a new thread to handle the client
	 *
	 */
	std::thread& getAcceptThread();
};