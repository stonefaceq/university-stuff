package database;

import classes.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBManager {

    private ConnectDB connection;

    public DBManager(ConnectDB conn) {
        this.connection = conn;
    }

    public ConnectDB getConnection() {
        return connection;
    }

    public void setConnection(ConnectDB connection) {
        this.connection = connection;
    }



    public void insertNecklace(Necklace necklace) {
        String sql = "INSERT INTO Necklaces (name) VALUES (?)";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {

            stmt.setString(1, necklace.getName());
            stmt.executeUpdate();

            ResultSet generatedKeys = stmt.getGeneratedKeys();
            if (generatedKeys.next()) {
                int generatedID = generatedKeys.getInt(1);
                necklace.setNecklaceID(generatedID);
            }
            System.out.println("Necklace inserted successfully with ID: " + necklace.getNecklaceID());
        } catch (SQLException e) {
            throw new RuntimeException("Error inserting necklace", e);
        }
    }

    public Necklace getNecklaceById(int necklaceID) {
        String sql = "SELECT * FROM Necklaces WHERE necklaceID = ?";
        String sql1 = "SELECT stoneID FROM NecklaceStones WHERE necklaceID = ?";
        Necklace necklace = null;
        List<Stone> stones = new ArrayList<>();

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql);
             PreparedStatement stmt1 = connection.getConnection().prepareStatement(sql1)) {

            stmt.setInt(1, necklaceID);
            stmt1.setInt(1, necklaceID);

            ResultSet rs = stmt.executeQuery();
            ResultSet rs1 = stmt1.executeQuery();


            if (rs.next()) {
                necklace = new Necklace();
                necklace.setNecklaceID(rs.getInt("necklaceID"));
                necklace.setName(rs.getString("name"));


                while (rs1.next()) {
                    int stoneId = rs1.getInt("stoneID");
                    Stone stone = getStoneById(stoneId);
                    if (stone != null) {
                        stones.add(stone);
                    }
                }

                necklace.setStones(stones);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error fetching necklace by ID", e);
        }
        return necklace;
    }

    public boolean doesNecklaceExist(int necklaceID) {
        String sql = "SELECT 1 FROM Necklaces WHERE necklaceID = ?";
        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setInt(1, necklaceID);
            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next(); // Returns true if a record is found
            }
        } catch (SQLException e) {
            System.out.println("Error checking necklace existence: " + e.getMessage());
            return false;
        }
    }

    public boolean doesStoneExist(int stoneID) {
        String sql = "SELECT 1 FROM Stones WHERE stoneID = ?";
        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setInt(1, stoneID);
            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next(); // Returns true if a record is found
            }
        } catch (SQLException e) {
            System.out.println("Error checking stone existence: " + e.getMessage());
            return false;
        }
    }



    public void addStoneToNecklace(int necklaceID, int stoneID) {
        if (!doesNecklaceExist(necklaceID)) {
            System.out.println("Error: Necklace with ID " + necklaceID + " does not exist.");
            return;
        }

        if (!doesStoneExist(stoneID)) {
            System.out.println("Error: Stone with ID " + stoneID + " does not exist.");
            return;
        }

        String sql = "INSERT INTO NecklaceStones (necklaceID, stoneID) VALUES (?, ?)";
        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setInt(1, necklaceID);
            stmt.setInt(2, stoneID);
            stmt.executeUpdate();
            System.out.println("Stone added to necklace successfully.");
        } catch (SQLException e) {
            throw new RuntimeException("Error adding stone to necklace", e);
        }
    }

    public void removeStoneFromNecklace(int necklaceID, int stoneID) {
        if (!doesNecklaceExist(necklaceID)) {
            System.out.println("Error: Necklace with ID " + necklaceID + " does not exist.");
            return;
        }

        if (!doesStoneExist(stoneID)) {
            System.out.println("Error: Stone with ID " + stoneID + " does not exist.");
            return;
        }

        String sql = "DELETE FROM NecklaceStones WHERE necklaceID = ? AND stoneID = ?";
        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setInt(1, necklaceID);
            stmt.setInt(2, stoneID);
            int affectedRows = stmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Stone removed from necklace successfully.");
            } else {
                System.out.println("Stone was not found in the necklace.");
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error removing stone from necklace", e);
        }
    }

    public void viewNecklace(int necklaceId) {
        Necklace nec;
        try {
            nec = getNecklaceById(necklaceId);
            nec.print();
        }
        catch (NullPointerException e) {
            System.out.println("Error outputting necklace: either doesn't exist or it's empty");
        }
    }


    public void insertStone(Stone stone) {
        String sql = "INSERT INTO Stones (valuability, name, carats, cost, transparency) " +
                "VALUES (?, ?, ?, ?, ?)";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {

            stmt.setString(1, stone.getValuability().toString());
            stmt.setString(2, stone.getName());
            stmt.setInt(3, (int) stone.getCarats());
            stmt.setInt(4, (int) stone.getCost());
            stmt.setInt(5, (int) stone.getTransparency());
            stmt.executeUpdate();

            ResultSet generatedKeys = stmt.getGeneratedKeys();
            if (generatedKeys.next()) {
                int generatedID = generatedKeys.getInt(1);
                stone.setStoneID(generatedID); // Встановлюємо ID в об'єкт Stone
            }
            System.out.println("Stone inserted successfully with ID: " + stone.getStoneID());
        } catch (SQLException e) {
            throw new RuntimeException("Error inserting stone", e);
        }
    }


    public Stone getStoneById(int stoneID) {
        String sql = "SELECT * FROM Stones WHERE stoneID = ?";
        Stone stone = null;

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {

            stmt.setInt(1, stoneID);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                stone = new Stone();
                stone.setStoneID(rs.getInt("stoneID"));
                stone.setValuabilityFromText(rs.getString("valuability"));
                stone.setName(rs.getString("name"));
                stone.setCarats(rs.getInt("carats"));
                stone.setCost(rs.getInt("cost"));
                stone.setTransparency(rs.getInt("transparency"));
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error fetching stone by ID", e);
        }
        return stone;
    }


    public void updateStone(Stone stone) {
        String sql = "UPDATE Stones SET valuability = ?, name = ?, carats = ?, cost = ?, transparency = ? WHERE stoneID = ?";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setString(1, stone.getValuability().toString());
            stmt.setString(2, stone.getName());
            stmt.setInt(3, (int) stone.getCarats());
            stmt.setInt(4, (int) stone.getCost());
            stmt.setInt(5, (int) stone.getTransparency());
            stmt.setInt(6, stone.getStoneID());

            int affectedRows = stmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Stone updated successfully.");
            } else {
                System.out.println("No stone found with ID: " + stone.getStoneID());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error updating stone", e);
        }
    }

    public void updateNecklace(Necklace necklace) {
        String sql = "UPDATE Necklaces SET name = ? WHERE necklaceID = ?";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setString(1, necklace.getName());
            stmt.setInt(2, necklace.getNecklaceID());

            int affectedRows = stmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Necklace updated successfully.");
            } else {
                System.out.println("No necklace found with ID: " + necklace.getNecklaceID());
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error updating necklace", e);
        }
    }

    public void deleteStoneById(int stoneID) {
        String sql = "DELETE FROM Stones WHERE stoneID = ?";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {

            stmt.setInt(1, stoneID);
            stmt.executeUpdate();
            System.out.println("Stone deleted successfully.");
        } catch (SQLException e) {
            throw new RuntimeException("Error deleting stone", e);
        }
    }



    private int executeUpdate(Connection conn, String sql, int param) throws SQLException {
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, param);
            return stmt.executeUpdate();
        }
    }

    private void resetAutoCommit() {
        try {
            connection.getConnection().setAutoCommit(true);
        } catch (SQLException e) {
            System.err.println("Error resetting auto-commit: " + e.getMessage());
        }
    }


    public void deleteNecklaceById(int necklaceId) {
        String sql = "DELETE FROM Necklaces WHERE necklaceID = ?";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setInt(1, necklaceId);

            int affectedRows = stmt.executeUpdate();
            if (affectedRows > 0) {
                System.out.println("Necklace deleted successfully.");
            } else {
                System.out.println("No necklace found with ID: " + necklaceId);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error deleting necklace", e);
        }
    }

    public void destroyDatabase() {
        String[] tables = {"Stones", "Necklaces", "NecklaceStones"};

        try {
            try (Statement stmt = connection.getConnection().createStatement()) {
                stmt.execute("PRAGMA foreign_keys = OFF;");
            }

            for (String table : tables) {
                String sql = "DROP TABLE IF EXISTS " + table;
                try (Statement stmt = connection.getConnection().createStatement()) {
                    stmt.execute(sql);
                    System.out.println("Table " + table + " dropped successfully.");
                }
            }

            try (Statement stmt = connection.getConnection().createStatement()) {
                stmt.execute("PRAGMA foreign_keys = ON;");
            }

            System.out.println("Database destroyed successfully.");
        } catch (SQLException e) {
            throw new RuntimeException("Error destroying database", e);
        }
    }

    public void clearDatabase() {
        String[] tables = {"Stones", "Necklaces", "NecklaceStones"};

        try {
            try (Statement stmt = connection.getConnection().createStatement()) {
                stmt.execute("PRAGMA foreign_keys = OFF;");
            }

            for (String table : tables) {
                String sql = "DELETE FROM " + table;
                try (Statement stmt = connection.getConnection().createStatement()) {
                    stmt.execute(sql);
                    System.out.println("Table " + table + " cleared successfully.");
                }
            }

            for (String table : tables) {
                String sql = "DELETE FROM sqlite_sequence WHERE name='" + table + "'";
                try (Statement stmt = connection.getConnection().createStatement()) {
                    stmt.execute(sql);
                }
            }

            try (Statement stmt = connection.getConnection().createStatement()) {
                stmt.execute("PRAGMA foreign_keys = ON;");
            }

            System.out.println("Database cleared successfully.");
        } catch (SQLException e) {
            throw new RuntimeException("Error clearing database", e);
        }
    }

    public void printAllStones() {
        String sql = "SELECT s.stoneID, s.valuability, s.name, s.carats, s.cost, s.transparency " +
                "FROM Stones s";
        try (Statement stmt = connection.getConnection().createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            System.out.println("All Stones:");
            System.out.println("ID | Valuability | Name | Carats | Cost | Transparency");
            System.out.println("---------------------------------------------------------");
            while (rs.next()) {
                int id = rs.getInt("stoneID");
                String valuability = rs.getString("valuability");
                String name = rs.getString("name");
                int carats = rs.getInt("carats");
                int cost = rs.getInt("cost");
                int transparency = rs.getInt("transparency");
                System.out.printf("%d | %s | %s | %d | %d | %d", id, valuability, name, carats, cost, transparency);
                System.out.println();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error printing all stones", e);
        }
    }

    public void printAllNecklaces() {
        String query = "SELECT * FROM Necklaces";
        try (Statement stmt = connection.getConnection().createStatement();
             ResultSet rs = stmt.executeQuery(query)) {

            System.out.println("All Necklaces:");
            while (rs.next()) {
                int id = rs.getInt("necklaceID");
                String name = rs.getString("name");
                int totalCarats = rs.getInt("totalCarats");
                int totalCost = rs.getInt("totalCost");

                System.out.println("ID: " + id + ", Name: " + name +
                        ", Total Carats: " + totalCarats +
                        ", Total Cost: " + totalCost);
            }

        } catch (SQLException e) {
            System.out.println("Error retrieving necklaces: " + e.getMessage());
        }
    }




    public void findStonesByTransparency(int lower, int higher) {
        String sql = "SELECT * FROM Stones WHERE transparency BETWEEN ? AND ? ORDER BY transparency";

        try (PreparedStatement stmt = connection.getConnection().prepareStatement(sql)) {
            stmt.setInt(1, lower);
            stmt.setInt(2, higher);
            ResultSet rs = stmt.executeQuery();

            System.out.println("Stones with Transparency between " + lower + " and " + higher + ":");
            System.out.println("ID | Valuability | Name | Carats | Cost | Transparency");
            System.out.println("---------------------------------------------------------");

            boolean found = false;
            while (rs.next()) {
                int id = rs.getInt("stoneID");
                String valuability = rs.getString("valuability");
                String name = rs.getString("name");
                int carats = rs.getInt("carats");
                int cost = rs.getInt("cost");
                int transparency = rs.getInt("transparency");

                System.out.printf("%d | %s | %s | %d | %d | %d%n", id, valuability, name, carats, cost, transparency);
                found = true;
            }

            if (!found) {
                System.out.println("No stones found within the specified transparency range.");
            }

        } catch (SQLException e) {
            throw new RuntimeException("Error finding stones by transparency", e);
        }
    }

}
