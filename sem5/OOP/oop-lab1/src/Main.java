import menu.*;
import tests.DatabaseTester;

import java.sql.SQLException;


public class Main {

    public static void main(String[] args) throws SQLException {

        try {
            Class.forName("org.sqlite.JDBC");
        } catch (ClassNotFoundException e) {
            System.out.print("");
        }

        MainMenu.startMenu();
        DatabaseTester tester = new DatabaseTester();
        //tester.test();
    }
}