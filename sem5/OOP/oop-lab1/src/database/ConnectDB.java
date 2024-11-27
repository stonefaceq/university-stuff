package database;

import java.sql.*;

public class ConnectDB {
    private Connection connection;

    public ConnectDB() {
        initiateConnection();
    }

    public void initiateConnection() {
        String url = "jdbc:sqlite:jewelry.db";

        try {
            // create a connection to the database
            connection = DriverManager.getConnection(url);

            System.out.println("Connection to local DB established.");

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void closeConnection() {
        try {
            if (connection != null) {
                connection.close();
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public Connection getConnection() throws SQLException {
        if (connection == null  || connection.isClosed()) {
            System.out.println("Connection is null, initializing.");
            initiateConnection();
        }
        return connection;
    }
}
