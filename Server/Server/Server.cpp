#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <thread>
#include <unordered_map>
#include <string>
#include <mutex>
//#include <openssl/sha.h> // For SHA-256;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")


using namespace std;

#pragma comment(lib, "ws2_32.lib")

// chat_sql_connector.h
// A basic SQL connector class for user login, registration, and message saving

#pragma once
#define NOMINMAX

#include <windows.h>
#include <sqlext.h>
#include <vector>


class SqlManager {
private:
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

public:
    SqlManager() {
        SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
        SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
        SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

        SQLCHAR connStr[] = "Driver={ODBC Driver 18 for SQL Server};Server=localhost;Database=YAPP;Trusted_Connection=yes;";
        SQLCHAR outConnStr[1024];
        SQLSMALLINT outConnStrLen;

        ret = SQLDriverConnectA(hDbc, NULL, connStr, SQL_NTS, outConnStr, sizeof(outConnStr), &outConnStrLen, SQL_DRIVER_NOPROMPT);
        if (!SQL_SUCCEEDED(ret)) {
            std::cerr << "❌ Failed to connect to SQL Server." << std::endl;
        }
        else {
            std::cout << "✅ Connected to SQL Server!" << std::endl;
        }
    }

    ~SqlManager() {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    }

    bool AuthenticateUser(const std::string& username, const std::string& passwordHash) {
        SQLHSTMT hStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        std::string query = "SELECT COUNT(*) FROM Users WHERE Username = ? AND PasswordHash = ?";
        SQLPrepareA(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)passwordHash.c_str(), 0, NULL);

        SQLINTEGER count = 0;
        SQLBindCol(hStmt, 1, SQL_C_LONG, &count, 0, NULL);
        SQLExecute(hStmt);
        SQLFetch(hStmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return count > 0;
    }

    bool RegisterUser(const std::string& username, const std::string& passwordHash) {
        SQLHSTMT hStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        std::string query = "INSERT INTO Users (Username, PasswordHash) VALUES (?, ?)";
        SQLPrepareA(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)passwordHash.c_str(), 0, NULL);

        ret = SQLExecute(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return SQL_SUCCEEDED(ret);
    }

    bool SaveMessage(int conversationId, int senderId, const std::string& messageText) {
        SQLHSTMT hStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        std::string query = "INSERT INTO Messages (ConversationID, SenderID, MessageText) VALUES (?, ?, ?)";
        SQLPrepareA(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &conversationId, 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &senderId, 0, NULL);
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)messageText.c_str(), 0, NULL);

        ret = SQLExecute(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return SQL_SUCCEEDED(ret);
    }

    int GetUserId(const std::string& username) {
        SQLHSTMT hStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        int userId = -1;
        std::string query = "SELECT UserID FROM Users WHERE Username = ?";
        SQLPrepareA(hStmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindCol(hStmt, 1, SQL_C_LONG, &userId, 0, NULL);

        SQLExecute(hStmt);
        SQLFetch(hStmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return userId;
    }

    int GetConversationId(int user1Id, int user2Id) {
        SQLHSTMT hStmt;
        SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

        // Sort users to ensure consistency
        int lowId = (std::min)(user1Id, user2Id);
        int highId = (std::max)(user1Id, user2Id);

        int convId = -1;
        std::string selectQuery = "SELECT ConversationID FROM Conversations WHERE User1ID = ? AND User2ID = ?";
        SQLPrepareA(hStmt, (SQLCHAR*)selectQuery.c_str(), SQL_NTS);
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &lowId, 0, NULL);
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &highId, 0, NULL);
        SQLBindCol(hStmt, 1, SQL_C_LONG, &convId, 0, NULL);

        SQLExecute(hStmt);
        if (SQLFetch(hStmt) == SQL_NO_DATA) {
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
            SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

            std::string insertQuery = "INSERT INTO Conversations (User1ID, User2ID) VALUES (?, ?)";
            SQLPrepareA(hStmt, (SQLCHAR*)insertQuery.c_str(), SQL_NTS);
            SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &lowId, 0, NULL);
            SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &highId, 0, NULL);
            SQLExecute(hStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

            return GetConversationId(user1Id, user2Id);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return convId;
    }
};



class Server {
protected:
    int port;
    SOCKET listenSocket;
    unordered_map<string, SOCKET> clients;  // map UID -> client socket
    SqlManager db; // Add this in Server class as a member
    mutex clientsMutex;  // protect clients map for thread safety

public:
    Server(int port) : port(port), listenSocket(INVALID_SOCKET) {
        if (!Initialize()) {
            cerr << "Winsock initialization failed" << endl;
            exit(1);
        }
    }

    ~Server() {
        Cleanup();
    }

    void Start() {
        CreateSocket();
        BindSocket();
        ListenOnSocket();
        AcceptClients();
    }

    bool Initialize() {
        WSADATA data;
        return WSAStartup(MAKEWORD(2, 2), &data) == 0;
    }

    void Cleanup() {
        if (listenSocket != INVALID_SOCKET) {
            closesocket(listenSocket);
        }
        WSACleanup();
    }

    void CreateSocket() {
        listenSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (listenSocket == INVALID_SOCKET) {
            cerr << "Socket creation failed" << endl;
            Cleanup();
            exit(1);
        }
    }

    void BindSocket() {
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);

        if (InetPton(AF_INET, _T("0.0.0.0"), &serverAddr.sin_addr) != 1) {
            cerr << "Setting address structure failed" << endl;
            Cleanup();
            exit(1);
        }

        if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
            cerr << "Bind failed" << endl;
            Cleanup();
            exit(1);
        }
    }

    void ListenOnSocket() {
        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
            cerr << "Listen failed" << endl;
            Cleanup();
            exit(1);
        }
        cout << "Server has started listening on port: " << port << endl;
    }

    void AcceptClients() {
        while (true) {
            SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
            if (clientSocket == INVALID_SOCKET) {
                cerr << "Invalid client socket" << endl;
                continue;
            }
            thread t(&Server::InteractWithClient, this, clientSocket);
            t.detach();
        }
    }

    void InteractWithClient(SOCKET clientSocket) {
        char buffer[4096];

        // Step 1: Receive command ("login" or "register")
        int cmdLen = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (cmdLen <= 0) {
            closesocket(clientSocket);
            return;
        }
        std::string command(buffer, cmdLen);

        // Step 2: Receive username
        int uidLen = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (uidLen <= 0) {
            closesocket(clientSocket);
            return;
        }
        std::string username(buffer, uidLen);

        // Step 3: Receive password hash
        int pwdLen = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (pwdLen <= 0) {
            closesocket(clientSocket);
            return;
        }
        std::string passwordHash(buffer, pwdLen);

        // Auth or register logic
        bool authenticated = false;
        if (command == "register") {
            authenticated = db.RegisterUser(username, passwordHash);
        }
        else if (command == "login") {
            authenticated = db.AuthenticateUser(username, passwordHash);
        }

        if (!authenticated) {
            std::string failMsg = "auth_failed";
            send(clientSocket, failMsg.c_str(), (int)failMsg.length(), 0);
            closesocket(clientSocket);
            return;
        }

        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients[username] = clientSocket;
        }

        std::string successMsg = "auth_success";
        send(clientSocket, successMsg.c_str(), (int)successMsg.length(), 0);
        std::cout << "✅ " << username << " authenticated and connected.\n";

        // Start message loop
        while (true) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) {
                std::cout << username << " disconnected.\n";
                break;
            }

            std::string fullMsg(buffer, bytesReceived);
            size_t sep = fullMsg.find('|');
            if (sep == std::string::npos) continue;

            std::string toUser = fullMsg.substr(0, sep);
            std::string messageText = fullMsg.substr(sep + 1);

            int senderId = db.GetUserId(username);
            int recipientId = db.GetUserId(toUser);
            int convId = db.GetConversationId(senderId, recipientId);
            db.SaveMessage(convId, senderId, messageText);

            std::lock_guard<std::mutex> lock(clientsMutex);
            if (clients.count(toUser)) {
                std::string routed = username + "|" + messageText;
                send(clients[toUser], routed.c_str(), (int)routed.length(), 0);
            }
        }

        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.erase(username);
        closesocket(clientSocket);
    }


    void RemoveClient(const string& uid) {
        lock_guard<mutex> lock(clientsMutex);
        auto it = clients.find(uid);
        if (it != clients.end()) {
            closesocket(it->second);
            clients.erase(it);
        }
    }
};

int main() {
    Server server(55555);
    server.Start();
    return 0;
}
