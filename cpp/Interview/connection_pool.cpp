#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <vector>

// 模拟数据库连接类
class Connection {
  public:
    Connection(int id) : m_id(id) {
        std::cout << "Connection " << m_id << " created." << std::endl;
    }

    ~Connection() {
        std::cout << "Connection " << m_id << " destroyed." << std::endl;
    }

    void query(const std::string& sql) {
        std::cout << "Connection " << m_id << " executing query: " << sql
                  << std::endl;
    }

  private:
    int m_id;
};

class ConnectionPool {
  public:
    ConnectionPool(int poolSize) : m_poolSize(poolSize) {
        for (int i = 0; i < m_poolSize; ++i) {
            m_connections.push_back(std::make_shared<Connection>(i));
        }
    }

    std::shared_ptr<Connection> getConnection() {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_connections.empty()) {
            throw std::runtime_error("No available connections");
        }

        auto conn = m_connections.back();
        m_connections.pop_back();
        return conn;
    }

    void releaseConnection(std::shared_ptr<Connection> conn) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_connections.push_back(conn);
    }

    int availableConnections() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_connections.size();
    }

  private:
    std::vector<std::shared_ptr<Connection>> m_connections;
    int m_poolSize;
    mutable std::mutex m_mutex;
};

int main() {
    ConnectionPool pool(5);

    try {
        auto conn1 = pool.getConnection();
        std::cout << "Available connections: " << pool.availableConnections()
                  << std::endl;

        conn1->query("SELECT * FROM users");

        auto conn2 = pool.getConnection();
        std::cout << "Available connections: " << pool.availableConnections()
                  << std::endl;

        conn2->query("INSERT INTO users (name, age) VALUES ('John', 30)");

        pool.releaseConnection(conn1);
        std::cout << "Available connections: " << pool.availableConnections()
                  << std::endl;

        pool.releaseConnection(conn2);
        std::cout << "Available connections: " << pool.availableConnections()
                  << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}