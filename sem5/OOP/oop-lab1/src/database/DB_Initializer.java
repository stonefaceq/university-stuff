package database;

import java.sql.*;


public class DB_Initializer {

    private Connection connection;

    public DB_Initializer() {}

    public DB_Initializer(Connection connection) {
        this.connection = connection;
    }

    public void createTables() {
        try (Statement stmt = connection.createStatement()) {

            String stoneTable = "CREATE TABLE IF NOT EXISTS Stones ("
                    + "stoneID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + "valuability TEXT NOT NULL,"
                    + "name TEXT NOT NULL,"
                    + "carats REAL DEFAULT 0,"
                    + "cost REAL DEFAULT 0,"
                    + "transparency REAL DEFAULT 0"
                    + ");";
            stmt.execute(stoneTable);

            String necklaceTable = "CREATE TABLE IF NOT EXISTS Necklaces ("
                    + "necklaceID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + "name TEXT NOT NULL"
                    + ");";
            stmt.execute(necklaceTable);

            String necklaceStonesTable = "CREATE TABLE IF NOT EXISTS NecklaceStones ("
                    + "necklaceID INTEGER,"
                    + "stoneID INTEGER,"
                    + "FOREIGN KEY (necklaceID) REFERENCES Necklaces(necklaceID),"
                    + "FOREIGN KEY (stoneID) REFERENCES Stones(stoneID),"
                    + "PRIMARY KEY (necklaceID, stoneID)"
                    + ");";
            stmt.execute(necklaceStonesTable);

            System.out.println("Tables created successfully.");

        } catch (SQLException e) {
            System.out.println("Error while creating tables: " + e.getMessage());
        }
    }
}

