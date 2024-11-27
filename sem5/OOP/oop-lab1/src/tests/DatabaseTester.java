package tests;

import classes.*;
import database.*;
import org.junit.jupiter.api.*;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

@TestInstance(TestInstance.Lifecycle.PER_CLASS)
public class DatabaseTester {

    private ConnectDB connection;
    private DBManager dbManager;

    @BeforeAll
    public void initializeDatabase() throws SQLException {
        try {
            Class.forName("org.sqlite.JDBC");
        } catch (ClassNotFoundException e) {
            fail("SQLite JDBC Driver not found.");
        }

        connection = new ConnectDB();
        dbManager = new DBManager(connection);
        DB_Initializer initializer = new DB_Initializer(connection.getConnection());
        initializer.createTables();
        System.out.println("Database initialized.");
    }

    @Test
    public void testStone() {
        System.out.println("\nTesting Stone...");
        Valuability[] valArr = {Valuability.PRECIOUS, Valuability.PRECIOUS, Valuability.PRECIOUS, Valuability.SEMIPRECIOUS, Valuability.SEMIPRECIOUS};
        String[] stoneNames = {"Diamond", "Ruby", "Sapphire", "Topaz", "Peridot"};
        int[][] values = {{1, 200, 50}, {2, 500, 20}, {3, 400, 90}, {2, 150, 80}, {3, 250, 59}};

        for (int i = 0; i < stoneNames.length - 1; i++) {
            Stone stone = new Stone(valArr[i], stoneNames[i], values[i][0], values[i][1], values[i][2]);
            dbManager.insertStone(stone);

            Stone insertedStone = dbManager.getStoneById(stone.getStoneID());
            assertNotNull(insertedStone, "Inserted stone should not be null");
            assertEquals(stone.getName(), insertedStone.getName(), "Stone names should match");

            stone.setName(stoneNames[i] + " (Fake)");
            stone.setCarats(values[i][0] + 1);
            dbManager.updateStone(stone);

            Stone updatedStone = dbManager.getStoneById(stone.getStoneID());
            assertNotNull(updatedStone, "Updated stone should not be null");
            assertEquals(stone.getName(), updatedStone.getName(), "Updated stone names should match");
        }

        dbManager.deleteStoneById(stoneNames.length);
        Stone deletedStone = dbManager.getStoneById(stoneNames.length);
        assertNull(deletedStone, "Deleted stone should be null");
    }

    @Test
    public void testNecklace() {
        System.out.println("\nTesting Necklace...");
        List<Stone> stones = new ArrayList<>();
        Necklace initNecklace = new Necklace("test", stones);
        dbManager.insertNecklace(initNecklace);

        for (int i = 1; i <= 5; i++) {
            Stone stone = dbManager.getStoneById(i);
            if (stone != null) {
                stones.add(stone);
                dbManager.addStoneToNecklace(1, stone.getStoneID());
            }
        }

        Necklace necklace = new Necklace("Super luxury artifact", stones);
        dbManager.insertNecklace(necklace);

        Necklace retrievedNecklace = dbManager.getNecklaceById(necklace.getNecklaceID());
        assertNotNull(retrievedNecklace, "Retrieved necklace should not be null");
        assertEquals(necklace.getName(), retrievedNecklace.getName(), "Necklace names should match");

        necklace.setName("Cheap fake garbage");
        dbManager.updateNecklace(necklace);

        Necklace updatedNecklace = dbManager.getNecklaceById(necklace.getNecklaceID());
        assertNotNull(updatedNecklace, "Updated necklace should not be null");
        assertEquals("Cheap fake garbage", updatedNecklace.getName(), "Updated necklace name should match");
    }

    @AfterAll
    public void closeConnection() {
        connection.closeConnection();
        System.out.println("\nDatabase connection closed.");
    }
}
